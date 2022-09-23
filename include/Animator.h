#ifndef Animator_h
#define Animator_h

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Constants.h"
#include "json.hpp"
#include "TextureManager.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <map>

/*!
 * Frames have an image to display and a duration
 * Duration = number of frames the image should be visible
 * before the next image in the sequence is to be shown
 * */
class Frame {
    public:
        Frame(Frame* f);
        Frame(SDL_Texture* texure, SDL_Rect srcRect, uint duration);
        ~Frame();

        SDL_Texture* getImage();
        SDL_Rect getSrcRect();
        uint getDuration();
    private:
        SDL_Texture* _image; // Original image, may (and should) be a sprite sheet
        SDL_Rect _srcRect; // Part of sprite sheet to display
        uint _duration; // in screen frames
        uint* _imageAccessCount;
};

/*!
 * Sequences are used to handle an animation sequence
 * Every frame has an image and a duration
 * When all frames in a sequence have been displayed
 * the animation should loop around
 * */
class Sequence {
    public:
        Sequence(Sequence* s);
        Sequence(std::string descFilePath, SDL_Renderer* renderer);
        ~Sequence();
        
        SDL_Texture* getNextFrame();
        std::string getName();
        SDL_Texture* getCurrentFrame();
        SDL_Rect getSrcRect();

    private:
        std::string _name;
        std::vector<Frame*> _frames;
        uint _currentFrame; // Index of current frame in sequence
        uint _totalScreenFrameCount; // Total duration of the sequence in screen frames (FPSs)
        uint _screenFrameCounter; // Number of screen frames that has passed (Gets reset every animation cycle) 

        void loadFromDescFile(std::string jsonFileName, SDL_Renderer* renderer);
};

class Animator {
    public:
        Animator();
        Animator(Animator* a);
        Animator(std::vector<std::string> sequenceDescFileNames, SDL_Renderer* renderer);
        Animator(std::map<std::string, Sequence*> sequences);
        Animator(SDL_Texture* defaultTexture);
        ~Animator();
        
        SDL_Texture* getNextFrame();
        void selectSequence(std::string sequenceName);
        std::string getCurrentSequence();
        SDL_Texture* getDefaultTexture();
        SDL_Texture* getCurrentFrame();
        bool getUsingDefaultTexture();
        SDL_Rect getSrcRect();

        void useDefaultTexture(bool useDefault);
    private:
        std::map<std::string, Sequence*> _sequences;
        std::string _currentSequenceName;
        SDL_Texture* _defaultTexture;
        SDL_Rect _defaultTextureSrcRect;
        int* _textureSharedAccessCounter; // To keep track of if the texture should be deleted
        bool _useDefaultTexture;
};

#endif
