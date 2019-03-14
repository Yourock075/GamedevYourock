#include "game-engine.h"

int main(int argc, const char* argv[])
{

    Game* game = new Game();

    game->init("GameEngine", 0, 0, 800, 600, true);
    // game->initGL();
    game->render();

    game->mouse();

    game->swap_buffers();
    game->StartGameLoop();
    game->clean();

    return 0;
}
