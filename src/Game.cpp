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

        _gameObjects.push_back(_player);
        _gameObjects.push_back(new Platform("assets/images/Platform.png", _renderer, Vector2(200,20)));

        std::cout << "Game objects initialized!" << std::endl;
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
            for(int i = 0; i < _gameObjects.size(); i++){
                _gameObjects[i]->handleEvents(event);
            }
            break;
    }
}

void Game::update(){
    for(int i = 0; i< _gameObjects.size(); i++){
        _gameObjects[i]->update();
    }
}

void Game::render(){
    // Clear old stuff that shouldn't be rendered
    SDL_RenderClear(_renderer);
    // Add stuff to render here
    // The last thing painted is the foremost in the image
    for(int i = 0; i < _gameObjects.size(); i++){
        _gameObjects[i]->render();
    }
    // ------------------------
    SDL_RenderPresent(_renderer);
}

void Game::clean(){
    // Make sure to deconstruct all gameobjects    
    for(int i = 0; i < _gameObjects.size(); i++){
        _gameObjects[i]->~GameObject();
    }
    // Clean up resources
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_renderer);
    SDL_Quit();

    std::cout << "Game cleaned." << std::endl;
}

void Game::checkForCollisions(){
    for(int i = 0; i < _gameObjects.size(); i++){
        for(int j = i+1; j < _gameObjects.size(); j++){
            GameObject* result = _gameObjects[i]->isColliding(_gameObjects[j]);
            if(result != nullptr){
                // Act on collision
                std::cout << "Debug: Collision detected!" << std::endl;
                _gameObjects[i]->actOnCollision(result);
                result->actOnCollision(_gameObjects[i]);
            }
        }
    }
}

bool Game::running(){ return _isRunning;}