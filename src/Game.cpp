#include "Game.h"

// TODO Player and platform not showing up after rescale in GameObject.cpp

Game::Game(){
}

Game::~Game(){

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen){
    // Initialize SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        // Successfully initialized

        // Fullscreen?
        int flags = 0;
        if(fullscreen){
            flags = SDL_WINDOW_FULLSCREEN;
        }

        std::cout << "SDL subsystems initialized successfully!" << std::endl;

        // Create window
        _window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if(_window){
            std::cout << "Window created!" << std::endl;
        }

        // Create renderer
        _renderer = SDL_CreateRenderer(_window, -1, 0);
        if(_renderer){
            SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
            std::cout << "Renderer Created!" << std::endl;
        }

        _isRunning = true;

        // Initialize gameobjects
        _player = new Player("assets/images/Dude.png", _renderer);

        _gameObjects = std::vector<GameObject*>();

        _gameObjects.push_back(new Platform("assets/images/Platform.png", _renderer, Vector2(10,20)));
    }
    else{
        std::cout << "SDL could not initialize!" << std::endl;
        _isRunning = false;
    }

}

void Game::handleEvents(){
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type){
        case SDL_QUIT:
            _isRunning = false;
            break;
        default:
            _player->handleEvents(event);
            break;
    }
}

void Game::update(){
    _player->update();

    for(int i = 0; i< _gameObjects.size(); i++){
        _gameObjects[i]->update();
    }
}   

void Game::render(){
    // Clear old stuff that shouldn't be rendered
    SDL_RenderClear(_renderer);
    // Add stuff to render here
    // The last thing painted is the foremost in the image
    _player->render();
    // ------------------------
    SDL_RenderPresent(_renderer);
}

void Game::clean(){
    // Clean up resources
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_renderer);
    SDL_Quit();
    std::cout << "Game cleaned." << std::endl;
}

bool Game::running(){ return _isRunning;}