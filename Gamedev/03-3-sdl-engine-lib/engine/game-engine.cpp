#include "game-engine.h"

    Game::Game()
    {}
    Game::~Game()
    {}

    using namespace std;
    int Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen )
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
               cerr << "error: failed call SDL_Init: " << err_message << endl;
               return EXIT_FAILURE;
           }

            window = SDL_CreateWindow(title, xpos, ypos, width, height, ::SDL_WINDOW_OPENGL);
            if (window == nullptr)
            {
                const char* err_message = SDL_GetError();
                cerr << "error: failed call SDL_CreateWindow: " << err_message << endl;
                SDL_Quit();
                return EXIT_FAILURE;
            }
            SDL_Renderer* const renderer = SDL_CreateRenderer(window, -1, 0);

            if(renderer == nullptr)
            {
                const char* err_message = SDL_GetError();
                cerr << "error: failed call SDL_Renderer: " << err_message << endl;
                SDL_Quit();
                return EXIT_FAILURE;
            }
	return EXIT_SUCCESS;

    }

    int Game::mouse()
    {
        int mouseX, mouseY;
        SDL_Cursor * cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
        SDL_SetCursor(cursor);
        SDL_GetMouseState(&mouseX, &mouseY);
            if(cursor == nullptr)
            {
                const char* err_message = SDL_GetError();
                cerr << "error: failed call SDL_Cursor: " << err_message << endl;
                SDL_Quit();
                return EXIT_FAILURE;
            }
	return EXIT_SUCCESS;
    }
    void Game::handleEvent()
    {
    SDL_Event event;
    SDL_PollEvent(&event);
    bool continue_loop = true;
    while (continue_loop)
    {
        if(SDL_PollEvent(&event))
        {
            switch(event.type)
                {
                    case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            continue_loop = false;
                            break;
                    }
                        break;
                    case SDL_MOUSEMOTION:
                        cout << event.motion.x << "." << event.motion.y << endl;

                        break;
                    case SDL_MOUSEBUTTONDOWN:
                            switch (event.button.button)
                            {
                            case SDL_BUTTON_LEFT:
                                cout << "left mouse button clicked!" << endl;
                                break;
                            case SDL_BUTTON_RIGHT:
                                cout << "right mouse button clicked!" << endl;
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
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

