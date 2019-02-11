#include <game-engine.h>

Game *game = nullptr;

int main(int argc, const char * argv[])
{
    game = new Game();

    game->init("GameEngine", SDL_WINDOWPOS_CENTERED, 
                             SDL_WINDOWPOS_CENTERED, 800 ,600, true);

    game->handleEvent();

    game->clean();

    return 0;
}
