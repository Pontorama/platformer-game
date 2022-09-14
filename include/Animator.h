#ifndef Animator_h
#define Animator_h

#include "SDL2/SDL.h"
#include <vector>

/*!
 * 
 * */
struct Frame {
    SDL_Texture* image;
    uint duration;
};

/*!
 * Sequences are used to handle an animation sequence
 * Every frame has an image and a duration
 * 
 * */
class Sequence {
    public:
        Sequence();
        ~Sequence();
        
        SDL_Texture* getNextFrame();
    private:
        std::vector<Frame> _frames;
        uint _currentFrame;
        uint _totalFrameCount;
};

class Animator {
    public:
        Animator();
        ~Animator();

    private:
        // To add:
        std::vector<Sequence> _sequences; 
};

#endif
