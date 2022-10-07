#include "WindowManager.h"

WindowManager::WindowManager(int height, int width, int posX, int posY, bool fullscreen, string title){
    _height = height;
    _width = width;
    _fullscreen = fullscreen;

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        // SDL initialized
        int flags = 0;
        if(_fullscreen){
            flags = SDL_WINDOW_FULLSCREEN;
        }
        // Create window
        _window = SDL_CreateWindow(title.c_str(), posX, posY, _width, _height, flags);
        // Create renderer
        _renderer = SDL_CreateRenderer(_window, -1, 0);

    }else{
        throw WindowInitializationException();
    }
}

WindowManager::~WindowManager(){
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
}

SDL_Renderer* WindowManager::getRenderer(){
    return _renderer;
}

int WindowManager::getWindowWidth(){
    return _width;
}

int WindowManager::getWindowHeight(){
    return _height;
}
