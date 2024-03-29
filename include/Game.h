#ifndef Game_h
#define Game_h

#include <stdio.h>
#include <iostream>

#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"

#include "GameManager.h"
#include "Vector2.h"
#include "Constants.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "Player.h"
#include "Platform.h"
#include "LevelLoader.h"
#include "UIMaster.h"
#include "Camera.h"
#include "SettingsManager.h"


class Game : public GameManager {
    public:
        Game();
        ~Game();

        void init(SDL_Renderer* renderer);

        void handleEvents(); // Input, other window events etc
        void handleInput();
        void update(); // Update all gameobjects
        void render(); // Render gameobjects & other things to screen
        void clean();
        void checkForCollisions();
        void hitboxProximityUpdate();
        bool running();

        GameObject* getGameObject(string name);
        GameObject* getGameObject(int id);

    private:
        bool _isRunning;
        SDL_Window* _window;
        SDL_Renderer* _renderer;
        Camera* _camera;
        Player* _player;
        std::vector<GameObject*> _gameObjects; // Potential FIXME , might not be how to handle lists in this case
        UIMaster* _uimaster;
        DebugLogger* _debug;
        SettingsManager* _settingsManager;
        const float HITBOX_SCAN_RADIUS = 2000; // FIXME: Test for good value. Should prob be size of screen
};


#endif /* Game_h */
