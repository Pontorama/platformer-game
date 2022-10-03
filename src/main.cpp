#include "Game.h"
#include "Constants.h"

using namespace std;

int main(int argc, char* args[]){

    // Set FPS so game doesn't run based on processor clock speed
    const float frameDelay = 1000 / (FRAMERATE*1.f);

    Uint32 framestart;
    int frametime;

    Game game = Game();

    game.init("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    while(game.running()){
        // Do game loop
        framestart = SDL_GetTicks();

        game.handleEvents();
        game.handleInput();
        game.update();
        game.render();
        frametime = SDL_GetTicks() - framestart;

        if(frameDelay > frametime){
            // Running faster than wanted, delay
            SDL_Delay(frameDelay - frametime);
        }
    }

    game.clean();
    return 0;
}
