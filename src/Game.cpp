#include "Game.h"

using namespace std;

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
        LevelLoader levelLoader(_renderer);
        _gameObjects = levelLoader.loadLevelFromFile(ASSETS_PATH + "levels/Test.json");
        cout << "Game objects initialized! Loaded " << _gameObjects.size() << " Objects!" << endl;
    }
    else{
        cout << "SDL could not initialize!" << endl;
        _isRunning = false;
    }

    // Init UI
    _uimaster = new UIMaster(_renderer);

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
    // Do collision detection
    checkForCollisions();
    // Do other updates
    for(int i = 0; i< _gameObjects.size(); i++){
        _gameObjects[i]->update();
    }
}

void Game::render(){
    // Clear old stuff that shouldn't be rendered
    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
    SDL_RenderClear(_renderer);
    // Add stuff to render here
    // The last thing painted is the foremost in the image
    for(int i = 0; i < _gameObjects.size(); i++){
        _gameObjects[i]->render();
    }
    // Render UI elements last so they show up on top
    _uimaster->renderAllElements();
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

    cout << "Game cleaned." << endl;
}

void Game::checkForCollisions(){
    for(int i = 0; i < _gameObjects.size(); i++){
        for(int j = i+1; j < _gameObjects.size(); j++){
            tuple<Hitbox*, Hitbox*> result = _gameObjects[i]->isColliding(_gameObjects[j]);
            Hitbox* other_hitbox = get<0>(result);
            Hitbox* this_hitbox = get<1>(result);
            if(other_hitbox != nullptr && this_hitbox != nullptr){
                // Act on collision
                _gameObjects[i]->actOnCollision(this_hitbox, other_hitbox);
                _gameObjects[j]->actOnCollision(other_hitbox, this_hitbox);
            }
        }
    }
}

bool Game::running(){ 
    return _isRunning;
}