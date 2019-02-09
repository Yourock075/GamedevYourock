#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <string_view>

#include <SDL2/SDL.h>
#include <SDL2/SDL_version.h>



int main(int argc, char* argv [])
{
    using namespace std;

     const int init_result = SDL_Init(SDL_INIT_EVERYTHING);
    if (init_result != 0)
    {
        const char* err_message = SDL_GetError();
        cerr << "error: failed call SDL_Init: " << err_message << endl;
        return EXIT_FAILURE;
    }

     SDL_Window* const window = SDL_CreateWindow("MyGame", SDL_WINDOWPOS_CENTERED,
                                                  SDL_WINDOWPOS_CENTERED, 640, 480, ::SDL_WINDOW_OPENGL);
     if (window == nullptr)
     {
         const char* err_message = SDL_GetError();
         cerr << "error: failed call SDL_CreateWindow: " << err_message << endl;
         SDL_Quit();
         return EXIT_FAILURE;
     }

    SDL_Renderer* const renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 125, 125, 125, 255);
    SDL_RenderClear(renderer);
    SDL_Rect rect;
    rect.w = 120;
    rect.h = 120;
    rect.x = SDL_WINDOWPOS_CENTERED;
    rect.y = SDL_WINDOWPOS_CENTERED;
    SDL_SetRenderDrawColor(renderer, 225, 225, 125, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);
    if(renderer == nullptr)
    {
        const char* err_message = SDL_GetError();
        cerr << "error: failed call SDL_Renderer: " << err_message << endl;
        SDL_Quit();
        return EXIT_FAILURE;
    }
        int mouseX, mouseY;
    //SDL_GetMouseState(&mouseX, &mouseY);


    //int SDL_CaptureMouse(SDL_bool enabled);
    SDL_Cursor * cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
    SDL_SetCursor(cursor);
    SDL_GetMouseState(&mouseX, &mouseY);
    //SDL_ShowCursor(enabled);
    if(cursor == nullptr)
    {
        const char* err_message = SDL_GetError();
        cerr << "error: failed call SDL_Cursor: " << err_message << endl;
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_Event event;
//    SDL_PollEvent(&event);
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

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);


    SDL_Quit();

    return EXIT_SUCCESS;
}
