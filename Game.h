#ifndef Game_h
#define Game_h

#include "SDL2/SDL.h"
#include <stdio.h>
#include <iostream>

class Game{
    public:
        Game();
        ~Game();

        void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen); // Function to initialize the game window

        void handleEvents(); // Input, other window events etc
        void update(); // Update all gameobjects
        void render(); // Render gameobjects & other things to screen
        void clean();

        bool running();

    private:
        bool isRunning;
        SDL_Window* window;
        SDL_Renderer* renderer;
};


#endif /* Game_h */