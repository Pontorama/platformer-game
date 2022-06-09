#ifndef Debugger_h
#define Debugger_h

#include "Vector2.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"


class Debug{
    // TODO add list of logs
    public:
        // Constructors
        Debug();
        Debug(SDL_Renderer* renderer);
        Debug(SDL_Renderer* renderer, Vector2 pos);

        // Desctructor
        virtual ~Debug();

        void Log();
        void removeLog();
    private:
        Vector2 _logsPos;
        TTF_Font* _font;
        SDL_Color _fontColor;
        SDL_Renderer* _renderer;

};

#endif /* Debugger.h */