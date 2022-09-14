#include "Animator.h"
#include <SDL2/SDL_render.h>

using namespace std;
using json = nlohmann::json;

/*!
 * SEQUENCE CLASS
 * Sequence objects are used to:
 * - Load animations from file
 * - Represent animations in memory
 * - Get next frame in animation sequence
 */

Sequence::Sequence(string descFilePath, SDL_Renderer* renderer){
    loadFromDescFile(descFilePath, renderer);
    
}

Sequence::~Sequence(){
    for(int i = 0; i < _frames.size(); i++){
        SDL_DestroyTexture(_frames[i].image);
    }
}

/*!
 * Get next frame image in animation sequence to be rendered
 * */
SDL_Texture* Sequence::getNextFrame(){
    // Loop animation
    _screenFrameCounter %= _totaScreenFrameCount;
    // Find correct frame to display
    int durationSum = 0;
    for(int i = 0; i < _frames.size(); i++){
        // Floor division to select correct frame to display
        if(durationSum / _screenFrameCounter > 0){
            _screenFrameCounter++;
            return _frames[i].image;
        }
        durationSum += _frames[i].duration;
    }
}

/*!
 * Load from description file
 * Loads an animation sequence from json file containing data about the sequence
 * json file should have same format as aseprites "Export sprite sheet" output
 * with hash, layers, tags and slices checked when exporting
 * */
void Sequence::loadFromDescFile(std::string jsonFileName, SDL_Renderer* renderer){
    // Load json file
    ifstream inputfile(jsonFileName);
    json objects = json::parse(inputfile);

    // Read from metadata
    // Fields to read:
    // - "image" (path to image, relative to this json)
    // - "size" -> "w" and "h", width and height of the image in pixels
    string imageFilePath = objects["meta"]["image"].get<string>();
    int width = objects["meta"]["size"]["w"].get<int>();
    int height = objects["meta"]["size"]["h"].get<int>();

    SDL_Surface* tempSurface = IMG_Load(imageFilePath.c_str());
    SDL_Texture* fullImage = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    // Get frame metadata
    // Fields to read from each frame:
    // - "frame" contains what pixels from the image the frame contains
    // - "duration" contains how long the frame should  be displayed, in ms
    json frames = objects["frames"];
    for(auto it = frames.begin(); it != frames.end(); ++it){
        Frame frame;
        // Get sub-image size
        frame.srcRect.x = it.value()["frame"]["x"].get<int>();
        frame.srcRect.y = it.value()["frame"]["y"].get<int>();
        frame.srcRect.w = it.value()["frame"]["w"].get<int>();
        frame.srcRect.h = it.value()["frame"]["h"].get<int>();
        // Copy the correct part of the full image
        // Potential FIXME, pixelformat and texture access
        frame.image = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, frame.srcRect.w, frame.srcRect.h);
        SDL_SetRenderTarget(renderer, frame.image);
        SDL_RenderCopy(renderer, fullImage, &frame.srcRect, NULL);
        // Reset target back to screen
        SDL_SetRenderTarget(renderer, NULL);
        // Get frame duration and convert it to screen frames 
        frame.duration = (uint)(it.value()["duration"].get<uint>() / (TIME_PER_FRAME * 1000.f));
        // Add frame to sequence
        _frames.push_back(frame);
    }
}

// --------------------------------
/*!
 * ANIMATOR CLASS
 * Animator objects are responsible for changing between sequences
 *
 * */

Animator::Animator(){

}

Animator::~Animator(){

}
