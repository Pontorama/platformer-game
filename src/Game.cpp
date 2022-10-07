#include "Game.h"
#include "DebugLogger.h"

using namespace std;

Game::Game(){
}

Game::~Game(){
    // Clean up UI things
    delete _debug;
    delete _uimaster;
    delete _settingsManager;
    delete _camera;
    // Clean gameobjects
    for(int i = 0; i < _gameObjects.size(); i++){
        delete _gameObjects[i];
    }
    _gameObjects.clear();
    SDL_DestroyTexture(Texture::DEFAULT_PINK_TEXTURE);
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void Game::init(SDL_Renderer* renderer){
    // Initialize settings manager
    _isRunning = true;
    _renderer = renderer;
        // Initialize gameobjects
    _gameObjects = LevelLoader::loadLevelFromFile(ASSETS_PATH + "levels/Test_with_animations.json", renderer);
    _player = (Player*)_gameObjects[2];
    cout << "Game objects initialized! Loaded " << _gameObjects.size() << " Objects!" << endl;
    // Load default image
    Texture::DEFAULT_PINK_TEXTURE = IMG_LoadTexture(_renderer, DEFAULT_PINK_IMAGE.c_str());

    // STRETCH: Multiple cameras
    _camera = new Camera(renderer); 
    _camera->setObjectToFollow(_player);
    _camera->setFollowMode(true);
    cout << "Camera initialized!" << endl;
}

void Game::handleEvents(){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
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
}

/*!
 * Handle keyboard input for player etc.
 * */
void Game::handleInput(){
    const uint8_t* state = SDL_GetKeyboardState(nullptr);
    // Send inputs to game objects
    for(int i = 0; i < _gameObjects.size(); i++){
       _gameObjects[i]->handleInput(state); 
    }
}

void Game::update(){
    hitboxProximityUpdate();
    for(int i = 0; i< _gameObjects.size(); i++){
        _gameObjects[i]->update();
    }
    // Update camera
    _camera->update();
}

void Game::render(){
    // Prepare rendering of game objects
    _camera->renderGameObjects(_gameObjects);
    if(DEBUG_MODE){
        _camera->renderDebug(_gameObjects);
    }
    SDL_RenderPresent(_renderer);
}

void Game::clean(){

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

/*!
    Update the list of nearby hitboxes for all gameobjects
*/
void Game::hitboxProximityUpdate(){
    for(int i = 0; i < _gameObjects.size(); i++){
        _gameObjects[i]->clearNearbyHitboxes();
        for(int j = 0; j < _gameObjects.size(); j++){
            // Check if gameobjects are close to each other
            if(Vector::getDistance(_gameObjects[i]->getPos(), _gameObjects[j]->getPos()) < HITBOX_SCAN_RADIUS){
                if(i != j){
                    _gameObjects[i]->addNearbyHitboxes(_gameObjects[j]->getHitboxes());
                }
            }
        }
    }
}

/*!
 * Get a game object by name
 * The return value needs to be null checked
 * @param[in] name The name of the game object to get
 * @return The game object if found, nullptr if not
 * */
GameObject* Game::getGameObject(string name){
    for(auto& go : _gameObjects){
        if(go->getName() == name){
            return go;
        }
    }
    return nullptr;
}

GameObject* Game::getGameObject(int id){
    for(auto& go : _gameObjects){
        if(go->getID() == id){
            return go;
        }
    }
    return nullptr;
}
