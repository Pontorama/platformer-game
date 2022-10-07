#ifndef WindowManager_h
#define WindowManager_h

#include <string>
#include <exception>
#include "SDL2/SDL.h"

using namespace std;

/*
 * Class responsible for creating and freeing window and renderer.
 * To be accessed via service manager
 * */
class WindowManager {
    public:
        WindowManager(int height, int width, int posX, int posY, bool fullscreen, string title);
        ~WindowManager();

        SDL_Renderer* getRenderer();
        int getWindowWidth();
        int getWindowHeight();
    private:
        SDL_Renderer* _renderer;
        SDL_Window* _window;
        bool _fullscreen;
        int _height;
        int _width;
};

class WindowInitializationException : exception {
    public:
        char* what(){
          return "Window could not be initialized.";
        }
};

#endif
