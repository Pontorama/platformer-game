#ifndef DebugLogger_h
#define DebugLogger_h

#include <vector>

#include "Vector2.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "TextBox.h"
#include "Constants.h"


class DebugLogger : public TextBox{
    // TODO add list of logs
    public:
        // Constructors
        DebugLogger(int id, SDL_Renderer* renderer, TTF_Font* font);

        // Desctructor
        ~DebugLogger();
        
        // Public functions
        void render();
        void toggleVisible();
        void setVisible(bool visible);
        void log(string logText);
    private:
        bool _show;
        SDL_Color _backgroundColor = {43, 43, 43, 128}; // Standard bcolor, 50% opaque
        string _fontpath;
        int _fontSize;
        int _nLines; // Number of lines currently drawn to screen
        vector<string> _lines;
        const int MAX_N_LINES = 5;
        SDL_Rect _borderBox;
};

#endif /* Debugger.h */
