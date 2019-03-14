#include "game-engine.h"

#include <algorithm>
#include <array>
#include <cassert>
#include <exception>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string_view>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_opengl_glext.h>

PFNGLCREATESHADERPROC            glCreateShader            = nullptr;
PFNGLSHADERSOURCEPROC            glShaderSource            = nullptr;
PFNGLCOMPILESHADERPROC           glCompileShader           = nullptr;
PFNGLGETSHADERIVPROC             glGetShaderiv             = nullptr;
PFNGLGETSHADERINFOLOGPROC        glGetShaderInfoLog        = nullptr;
PFNGLDELETESHADERPROC            glDeleteShader            = nullptr;
PFNGLCREATEPROGRAMPROC           glCreateProgram           = nullptr;
PFNGLATTACHSHADERPROC            glAttachShader            = nullptr;
PFNGLBINDATTRIBLOCATIONPROC      glBindAttribLocation      = nullptr;
PFNGLGETATTRIBLOCATIONPROC       glGetAttribLocation       = nullptr;
PFNGLLINKPROGRAMPROC             glLinkProgram             = nullptr;
PFNGLGETPROGRAMIVPROC            glGetProgramiv            = nullptr;
PFNGLGETPROGRAMINFOLOGPROC       glGetProgramInfoLog       = nullptr;
PFNGLDELETEPROGRAMPROC           glDeleteProgram           = nullptr;
PFNGLUSEPROGRAMPROC              glUseProgram              = nullptr;
PFNGLVERTEXATTRIBPOINTERPROC     glVertexAttribPointer     = nullptr;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = nullptr;
PFNGLVALIDATEPROGRAMPROC         glValidateProgram         = nullptr;
PFNGLBINDBUFFERPROC              glBindBuffer              = nullptr;
PFNGLGENBUFFERSPROC              glGenBuffers              = nullptr;
PFNGLGENVERTEXARRAYSPROC         glGenVertexArrays         = nullptr;
PFNGLBINDVERTEXARRAYPROC         glBindVertexArray         = nullptr;
PFNGLBUFFERDATAPROC              glBufferData              = nullptr;

template <typename T>
static void load_gl_func(const char* func_name, T& result)
{
    void* gl_pointer = SDL_GL_GetProcAddress(func_name);
    if (nullptr == gl_pointer)
    {
        throw std::runtime_error(std::string("can't load GL function") +
                                 func_name);
    }
    result = reinterpret_cast<T>(gl_pointer);
}

#define ERROR_GL_CHECK()                                                       \
    {                                                                          \
        const GLenum err = glGetError();                                       \
        if (err != GL_NO_ERROR)                                                \
        {                                                                      \
            switch (err)                                                       \
            {                                                                  \
                case GL_INVALID_ENUM:                                          \
                    std::cerr << "GL_INVALID_ENUM" << std::endl;               \
                    break;                                                     \
                case GL_INVALID_VALUE:                                         \
                    std::cerr << "GL_INVALID_VALUE" << std::endl;              \
                    break;                                                     \
                case GL_INVALID_OPERATION:                                     \
                    std::cerr << "GL_INVALID_OPERATION" << std::endl;          \
                    break;                                                     \
                case GL_INVALID_FRAMEBUFFER_OPERATION:                         \
                    std::cerr << "GL_INVALID_FRAMEBUFFER_OPERATION"            \
                              << std::endl;                                    \
                    break;                                                     \
                case GL_OUT_OF_MEMORY:                                         \
                    std::cerr << "GL_OUT_OF_MEMORY" << std::endl;              \
                    break;                                                     \
            }                                                                  \
            std::cerr << __FILE__ << ':' << __LINE__ << '(' << __FUNCTION__    \
                      << ')' << std::endl;                                     \
            assert(false);                                                     \
        }                                                                      \
    }

struct Game::game_impl
{

    SDL_Window*   window     = nullptr;
    SDL_GLContext gl_context = nullptr;
    GLuint        gProgramID = 0;
};
Game::Game()
    : pimpl(std::make_unique<game_impl>())
{
}

Game::~Game() = default;

#define window pimpl->window
#define gProgramID pimpl->gProgramID
#define gl_context pimpl->gl_context

void Game::update() {}

bool Game::init(const char* title, int xpos, int ypos, int width, int height,
                bool fullscreen)
{
    int flags = 0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    const int init_result = SDL_Init(SDL_INIT_EVERYTHING);
    if (init_result != 0)
    {
        const char* err_message = SDL_GetError();
        std::cerr << "error: failed call SDL_Init: " << err_message
                  << std::endl;
        return EXIT_FAILURE;
    }

    window =
        SDL_CreateWindow(title, xpos, ypos, width, height, ::SDL_WINDOW_OPENGL);
    if (window == nullptr)
    {
        const char* err_message = SDL_GetError();
        std::cerr << "error: failed call SDL_CreateWindow: " << err_message
                  << std::endl;
        SDL_Quit();
        return EXIT_FAILURE;
    }
    gl_context = SDL_GL_CreateContext(window);
    if (gl_context == nullptr)
    {
        std::clog << "bad context opengl '\n'"
                  << "need openg version at least: 2.1\n"
                  << std::flush;
        throw std::runtime_error("invalid gl context");
    }

    int gl_major_ver = 0;
    int result =
        SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &gl_major_ver);
    SDL_assert(result == 0);
    int gl_minor_ver = 0;
    result = SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &gl_minor_ver);
    SDL_assert(result == 0);

    if (gl_major_ver <= 2 && gl_minor_ver < 1)
    {
        std::clog << "current context opengl version: " << gl_major_ver << '.'
                  << gl_minor_ver << '\n'
                  << "need openg version at least: 2.1\n"
                  << std::flush;
        throw std::runtime_error("opengl version too low");
    }

    try
    {
        load_gl_func("glCreateShader", glCreateShader);
        load_gl_func("glShaderSource", glShaderSource);
        load_gl_func("glCompileShader", glCompileShader);
        load_gl_func("glGetShaderiv", glGetShaderiv);
        load_gl_func("glGetShaderInfoLog", glGetShaderInfoLog);
        load_gl_func("glDeleteShader", glDeleteShader);
        load_gl_func("glCreateProgram", glCreateProgram);
        load_gl_func("glAttachShader", glAttachShader);
        load_gl_func("glBindAttribLocation", glBindAttribLocation);
        load_gl_func("glGetAttribLocation", glGetAttribLocation);
        load_gl_func("glLinkProgram", glLinkProgram);
        load_gl_func("glGetProgramiv", glGetProgramiv);
        load_gl_func("glGetProgramInfoLog", glGetProgramInfoLog);
        load_gl_func("glDeleteProgram", glDeleteProgram);
        load_gl_func("glUseProgram", glUseProgram);
        load_gl_func("glVertexAttribPointer", glVertexAttribPointer);
        load_gl_func("glEnableVertexAttribArray", glEnableVertexAttribArray);
        load_gl_func("glValidateProgram", glValidateProgram);
        ////////////////////////////////////////////////////////////////////
        load_gl_func("glBindBuffer", glBindBuffer);
        load_gl_func("glGenBuffers", glGenBuffers);
        load_gl_func("glGenVertexArrays", glGenVertexArrays);
        load_gl_func("glBindVertexArray", glBindVertexArray);
        load_gl_func("glBufferData", glBufferData);
    }
    catch (std::exception& ex)
    {
        return *ex.what();
    }

    return EXIT_SUCCESS;
}

void Game::render()
{
    // VAO
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    };

    // Это будет идентификатором нашего буфера вершин
    GLuint vertexbuffer;

    // Создадим 1 буфер и поместим в переменную vertexbuffer его идентификатор
    glGenBuffers(1, &vertexbuffer);

    // Сделаем только что созданный буфер текущим
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

    // Передадим информацию о вершинах в OpenGL
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data),
                 g_vertex_buffer_data, GL_STATIC_DRAW);
    // Указываем, что первым буфером атрибутов будут вершины
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(0,        // Атрибут.
                          3,        // Размер
                          GL_FLOAT, // Тип
                          GL_FALSE, // Указывает, что значения не нормализованы
                          0,       // Шаг
                          (void*)0 // Смещение массива в буфере
    );
    static const GLfloat g_color_buffer_data[] = { 0.2f,  0.9f,  0.4f,
                                                   0.9f,  -0.5f, 0.1f,
                                                   -0.5f, -0.6f, 0.4f };

    GLuint colorbuffer;
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data),
                 g_color_buffer_data, GL_STATIC_DRAW);

    // Второй буфер атрибутов - цвета
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glVertexAttribPointer(1,        // Атрибут.
                          3,        // Размер
                          GL_FLOAT, // Тип
                          GL_FALSE, // Нормализован?
                          0,        // Шаг
                          (void*)0  // Смещение

    );

    // glDisableVertexAttribArray(0);

    // Создаем шейдеры
    GLuint vertex_shader   = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    std::string_view vertex_shader_src = R"(
                                       attribute vec3 vertices;
                                       attribute vec3 a_color;
                                       varying vec4 v_position;
                                       varying vec3 v_color;
                                       void main()
                                       {
                                           v_position = vec4(vertices, 1.0);
                                           v_color = a_color;
                                           gl_Position = v_position;
                                       }
                                       )";
    const char*      source            = vertex_shader_src.data();
    glShaderSource(vertex_shader, 1, &source, nullptr);
    ERROR_GL_CHECK();

    ERROR_GL_CHECK();
    std::string_view fragment_shader_src = R"(
                                            varying vec4 v_position;
                                            varying vec3 v_color;
                                            void main()
                                            {
                                                gl_FragColor =
                                                vec4(v_color, 1.0);
                                            }
                                            )";
    source                               = fragment_shader_src.data();
    glShaderSource(fragment_shader, 1, &source, nullptr);
    ERROR_GL_CHECK();

    // Компилируем Вершинный шейдер
    glCompileShader(vertex_shader);

    // Компилируем Фрагментный шейдер
    glCompileShader(fragment_shader);

    // Создаем шейдерную программу и привязываем шейдеры к ней
    gProgramID = glCreateProgram();
    glAttachShader(gProgramID, vertex_shader);
    glAttachShader(gProgramID, fragment_shader);
    glLinkProgram(gProgramID);

    // Устанавливаем наш шейдер текущим
    glUseProgram(gProgramID);
    // Вывести треугольник!
    glDrawArrays(GL_TRIANGLES, 0,
                 3); // Начиная с вершины 0, всего 3 вершины -> один треугольник
}

void Game::swap_buffers()
{
    SDL_GL_SwapWindow(window);

    glClearColor(0.f, 0.f, 0.4f, 0.0f);
    ERROR_GL_CHECK();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ERROR_GL_CHECK();
}

bool Game::mouse()
{
    int         mouseX, mouseY;
    SDL_Cursor* cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
    SDL_SetCursor(cursor);
    SDL_GetMouseState(&mouseX, &mouseY);
    if (cursor == nullptr)
    {
        const char* err_message = SDL_GetError();
        std::cerr << "error: failed call SDL_Cursor: " << err_message
                  << std::endl;
        SDL_Quit();
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
void Game::StartGameLoop()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    bool continue_loop = true;
    while (continue_loop)
    {
        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            continue_loop = false;
                            break;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    std::cout << event.motion.x << "." << event.motion.y
                              << std::endl;

                    break;
                case SDL_MOUSEBUTTONDOWN:
                    switch (event.button.button)
                    {
                        case SDL_BUTTON_LEFT:
                            std::cout << "left mouse button clicked!"
                                      << std::endl;
                            break;
                        case SDL_BUTTON_RIGHT:
                            std::cout << "right mouse button clicked!"
                                      << std::endl;
                            break;
                    }

                    break;

                case SDL_QUIT:
                    continue_loop = false;
                    break;
            }
        }
    }
}

void Game::clean()
{
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
