#include "DebugLogger.h"
#include "TextBox.h"

DebugLogger::DebugLogger(int id, SDL_Renderer* renderer, TTF_Font* font) : TextBox(id, renderer, font){
    _show = false;
    _color = {0,0,0};
    setText("DebuggLogger test");
    setVisible(true);

    // Get font height
    TTF_SizeText(_font, "Test", nullptr, &_fontSize);

    _borderBox = {0, 0, 180, _fontSize*MAX_N_LINES};
}

DebugLogger::~DebugLogger(){

}

void DebugLogger::setVisible(bool visible){
    _show = visible;
}

void DebugLogger::render(){
    if(!_show){
      return;
    }    
    
    SDL_Surface* surf;
    SDL_Texture* textTexture;

    SDL_Rect textBbox;

    textBbox.h = _fontSize;
    textBbox.w = _borderBox.w;
    textBbox.x = _borderBox.x;
    textBbox.y = _borderBox.y;

    int widest = 0; 
    for(int i = 0; i < _lines.size(); i++){
        surf = TTF_RenderText_Solid(_font, _lines[i].c_str(), _color);
        textTexture = SDL_CreateTextureFromSurface(_ren, surf);
        TTF_SizeText(_font, _lines[i].c_str(), &textBbox.w, nullptr);
        if(textBbox.w > widest){
            widest = textBbox.w;
        }
        SDL_RenderCopy(_ren, textTexture, NULL, &textBbox);
        textBbox.y += _fontSize;
    }
    _borderBox.w = widest; 

    SDL_SetRenderDrawBlendMode(_ren, SDL_BLENDMODE_BLEND);
    // Draw transparent background
    SDL_SetRenderDrawColor(_ren, _backgroundColor.r, _backgroundColor.g, _backgroundColor.b, _backgroundColor.a);
    SDL_RenderFillRect(_ren, &_borderBox); 
    SDL_SetRenderDrawBlendMode(_ren, SDL_BLENDMODE_NONE);
}

void DebugLogger::toggleVisible(){
    _show = !_show;
}

void DebugLogger::log(string logText){
    _lines.push_back(logText);
    if(_lines.size() > MAX_N_LINES){
        _lines.erase(_lines.begin());
    }
}

DebugLogger* Debug::debugLogger;
