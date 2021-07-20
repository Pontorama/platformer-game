#include "./src/Game.h"
#include "./src/Constants.h"

using namespace std;
Game* game = nullptr;

int main(int argc, char* args[]){

    // Set FPS so game doesn't run based on processor clock speed
    const float frameDelay = 1000 / FRAMERATE;

    Uint32 framestart;
    int frametime;

    game = new Game();

    game->init("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, false);

    while(game->running()){
        // Do game loop
        framestart = SDL_GetTicks();

        game->handleEvents(); // Events might need to be handled in separate loop
        game->update();
        game->checkForCollisions();
        game->render();

        frametime = SDL_GetTicks() - framestart;

        if(frameDelay > frametime){
            // Running faster than wanted, delay
            SDL_Delay(frameDelay - frametime);
        }
    }

    game->clean();
    return 0;
}