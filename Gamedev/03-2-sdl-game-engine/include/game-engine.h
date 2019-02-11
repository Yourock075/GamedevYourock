#pragma once
#include "SDL2/SDL.h"
#include <iostream>
#include <cstdlib>

using namespace std;

class Game
{

public:
Game();
~Game();

int init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

void handleEvent();
void clean();
int mouse();

bool gameloop()
{
return continue_loop;
}


private:
bool continue_loop;
SDL_Window *window;

};

