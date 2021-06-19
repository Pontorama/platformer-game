#include "Game.h"

using namespace std;
Game* game = nullptr;

int main(int argc, char* args[]){
    game = new Game();

    game->init("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

    while(game->running()){
        game->handleEvents();
        game->update();
        game->render();
    }

    game->clean();
    return 0;
}