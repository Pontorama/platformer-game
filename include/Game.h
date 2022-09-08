#ifndef Game_h
#define Game_h

#include <stdio.h>
#include <iostream>

#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"

#include "Vector2.h"
#include "Constants.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "Player.h"
#include "Platform.h"
#include "LevelLoader.h"
#include "UIMaster.h"

class Game{
    public:
        Game();
        ~Game();

        void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen); // Function to initialize the game window

        void handleEvents(); // Input, other window events etc
        void update(); // Update all gameobjects
        void render(); // Render gameobjects & other things to screen
        void clean();
        void checkForCollisions();
        void hitboxProximityUpdate();
        bool running();

    private:
        bool _isRunning;
        SDL_Window* _window;
        SDL_Renderer* _renderer;
        Player* _player;
        std::vector<GameObject*> _gameObjects; // Potential FIXME , might not be how to handle lists in this case
        UIMaster* _uimaster;
        const float HITBOX_SCAN_RADIUS = 10; // FIXME: Test for good value
};


#endif /* Game_h */
