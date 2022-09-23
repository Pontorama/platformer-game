#ifndef TextureManager_h
#define TextureManager_h

#include "SDL2/SDL_image.h"

class TextureManager{
    public:
        static SDL_Texture* loadTexture(const char* fileName, SDL_Renderer* ren);
};

namespace Texture {
    // Pointer to default texture is a global variable
    // Game object is responsible for loading and freeing the default image
    extern SDL_Texture* DEFAULT_PINK_TEXTURE;
}
#endif
