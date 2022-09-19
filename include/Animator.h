#ifndef Animator_h
#define Animator_h

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Constants.h"
#include "json.hpp"
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
struct Frame {
    SDL_Texture* image; // Original image, may (and should) be a sprite sheet
    SDL_Rect srcRect; // Part of sprite sheet to display
    uint duration; // in screen frames
};

/*!
 * Sequences are used to handle an animation sequence
 * Every frame has an image and a duration
 * When all frames in a sequence have been displayed
 * the animation should loop around
 * */
class Sequence {
    public:
        Sequence(std::string descFilePath, SDL_Renderer* renderer);
        ~Sequence();
        
        SDL_Texture* getNextFrame();
        std::string getName();
        SDL_Texture* getCurrentFrame();

    private:
        std::string _name;
        std::vector<Frame> _frames;
        uint _currentFrame; // Index of current frame in sequence
        uint _totaScreenFrameCount; // Total duration of the sequence in screen frames (FPSs)
        uint _screenFrameCounter; // Number of screen frames that has passed (Gets reset every animation cycle) 

        void loadFromDescFile(std::string jsonFileName, SDL_Renderer* renderer);
};

class Animator {
    public:
        Animator();
        Animator(std::vector<std::string> sequenceDescFileNames, SDL_Renderer* renderer);
        Animator(std::map<std::string, Sequence> sequences);
        Animator(SDL_Texture* defaultTexture);
        ~Animator();
        
        SDL_Texture* getNextFrame();
        void selectSequence(std::string sequenceName);
        std::string getCurrentSequence();
        SDL_Texture* getDefaultTexture();
        SDL_Texture* getCurrentFrame();

        void useDefaultTexture(bool useDefault);
    private:
        std::map<std::string, Sequence> _sequences;
        std::string _currentSequenceName;
        SDL_Texture* _defaultTexture;
        bool _useDefaultTexture;
};

#endif
