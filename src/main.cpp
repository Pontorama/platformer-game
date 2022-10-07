#include "Game.h"
#include "Constants.h"
#include "ServiceLocator.h"
#include "SDL2/SDL_ttf.h"

using namespace std;
// Service locator is used for global access to things

int main(int argc, char* args[]){
    Services::locator = new ServiceLocator();
    // Initialize objects to be added to service locator in the right order first
    // Settings always initialized first
    SettingsManager* settingsManager = new SettingsManager(ASSETS_PATH + "Settings.json");
    Services::locator->provide(settingsManager);
    // Init window
    int windowSizeX = settingsManager->getSettingValue<int>("window_size_x");
    int windowSizeY = settingsManager->getSettingValue<int>("window_size_y");
    bool fullscreen = settingsManager->getSettingValue<bool>("fullscreen");
    WindowManager* windowManager = new WindowManager(windowSizeY, windowSizeX, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, fullscreen, "Monke time");
    Services::locator->provide(windowManager);
    // Init ui master
    SDL_Renderer* renderer = windowManager->getRenderer();
    UIMaster* uiMaster = new UIMaster(renderer);
    Services::locator->provide(uiMaster);
    // Init debug logger
    string fontPath = settingsManager->getSettingValue<string>("default_font_path");
    int fontSize = settingsManager->getSettingValue<int>("default_font_size");
    DebugLogger* debugLogger = new DebugLogger(0, renderer, TTF_OpenFont(fontPath.c_str(), fontSize));
    Services::locator->provide(debugLogger);
    // Set FPS so game doesn't run based on processor clock speed
    int framerate = settingsManager->getSettingValue<int>("framerate");
    const float frameDelay = 1000 / (framerate*1.f);

    Uint32 framestart;
    int frametime;

    Game game = Game();

    game.init(windowManager->getRenderer());

    while(game.running()){
        // Do game loop
        framestart = SDL_GetTicks();

        game.handleEvents();
        game.handleInput();
        game.update();
        game.render();
        //render UI

        frametime = SDL_GetTicks() - framestart;

        if(frameDelay > frametime){
            // Running faster than wanted, delay
            SDL_Delay(frameDelay - frametime);
        }
    }

    game.clean();
    return 0;
}
