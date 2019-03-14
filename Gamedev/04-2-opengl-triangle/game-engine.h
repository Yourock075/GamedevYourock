#pragma once
#include "SDL2/SDL.h"
#include <cstdlib>
#include <iostream>

#include <algorithm>
#include <array>
#include <cassert>
#include <exception>
#include <memory>
#include <stdexcept>
#include <string_view>
#include <vector>

struct vertex
{
    float x = 0.f;
    float y = 0.f;
    float z = 0.f;
    float r = 0.f;
    float g = 0.f;
    float b = 0.f;
};

class Game
{

public:
    Game();
    ~Game();
    bool init(const char* title, int xpos, int ypos, int width, int height,
              bool fullscreen);
    std::string initGL();
    void        StartGameLoop();
    void        clean();
    bool        mouse();
    void        render();
    void        update();
    void        swap_buffers();

private:
    struct game_impl;
    std::unique_ptr<game_impl> pimpl;
};
