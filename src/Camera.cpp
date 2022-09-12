#include "Camera.h"

Camera::Camera(SDL_Renderer* renderer){
    _renderer = renderer;
    init();
}

Camera::~Camera(){

}

/*!
 * Initialize values not specific to constructors
 * */
void Camera::init(){
    // TODO: Test these values
    _scrollSpeedX = 0.05;
    _scrollSpeedY = 0.05;
    _zoomLevel = 1;

    _viewSize = {DEFAULT_WINDOW_HEIGHT, DEFAULT_WINDOW_HEIGHT};

    _focusZone = {(int)(_viewSize.x / 2) - 100, (int)(_viewSize.y / 2) - 100, 200, 200};

    _pos = {0, 0};
}

/*!
 * Render objects to screen
 * */
void Camera::renderGameObjects(vector<GameObject*> objectsToRender){
    // Clear any residue objects from last frame
    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
    SDL_RenderClear(_renderer);
    // Render game objects
    for(auto obj : objectsToRender){
        renderObject(obj);
    }
    SDL_RenderPresent(_renderer);
}

/*!
 * Move the camera in world coordinate system
 * */
void Camera::move(){
    if(_followMode && _objToFollow != nullptr){
        // Check if object to follow is outside focus zone
        SDL_Rect focusInWorld = translateScreenToWorld(_focusZone);
        if(!CameraUtils::boxInsideBox(*_objToFollow->getDestRect(), focusInWorld)){
            // Move camera to follow
            _dir = _objToFollow->getPos() + Vector2(focusInWorld.x, focusInWorld.y)*(-1.f);
            _dir.normalise();
        }
    }else{
        _dir = {0, 0};
    }

    _pos.x += _dir.x * _scrollSpeedX * TIME_PER_FRAME;
    _pos.y += _dir.y * _scrollSpeedY * TIME_PER_FRAME;
}


/*!
 * Update camera position etc
 * Called as part of the games main update loop
 * */
void Camera::update(){
    move();
}

/*!
 * Translate a point in screen coordinates (pixels) to world coordinates
 * */
Vector2 Camera::translateScreenToWorld(Vector2 screenPos){
    Vector2 worldPos = screenPos*(1/_zoomLevel);
    return worldPos + _pos;
}

SDL_Rect Camera::translateScreenToWorld(SDL_Rect screenRect){
    SDL_Rect worldRect;
    worldRect.x = (screenRect.x / _zoomLevel) + _pos.x;
    worldRect.y = (screenRect.y / _zoomLevel) + _pos.y;
    worldRect.w = screenRect.w / _zoomLevel;
    worldRect.h = screenRect.h / _zoomLevel;

    return worldRect;
}

/*!
 * Translate a point in the game world to screen coordinates (pixels)
 * */
Vector2 Camera::translateWorldToScreen(Vector2 worldPos){
    Vector2 screenPos = worldPos +  _pos*(-1);
    // Apply zoom
    return screenPos * _zoomLevel;
}

SDL_Rect Camera::translateWorldToScreen(SDL_Rect worldRect){
    SDL_Rect screenRect;
    screenRect.x = (worldRect.x - _pos.x) * _zoomLevel;
    screenRect.y = (worldRect.y - _pos.y) * _zoomLevel;
    screenRect.w = worldRect.w * _zoomLevel;
    screenRect.h = worldRect.h * _zoomLevel;

    return screenRect;
}

/*!
 * Add an object to the renderer to be rendered
 * TODO: Support for multiple textures per object?
 * */
void Camera::renderObject(GameObject* go){
    // Translate world units to screen units
    SDL_Rect destRect = translateWorldToScreen(*go->getDestRect());
    // Add to render stack
    SDL_RenderCopy(_renderer, go->getTexture(), go->getSrcRect(), &destRect);
}

/*!
 * Render debug-related things
 * e.g. hitbox outlines
 * TODO: Decide what parameters should go here
 * Under construction
 * */
void Camera::renderDebug(){

}

/*!
 * Set wether the camera should follow a game object or not.
 * The game object to follow is set with setObjectToFollow.
 * */
void Camera::setFollowMode(bool follow){
    _followMode = follow;
}

/*!
 * Set game object to follow.
 * Camera only follows this object if _followMode = true
 * */
void Camera::setObjectToFollow(GameObject* objToFollow){
    _objToFollow = objToFollow;
}

/*!*/
void Camera::clearObjectToFollow(){
    _objToFollow = nullptr;
}
