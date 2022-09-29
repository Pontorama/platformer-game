#include "Animator.h"
#include <SDL2/SDL_render.h>

using namespace std;
using json = nlohmann::json;

/*!
 * FRAME CLASS
 * Class to represent frames in an animation sequence
 * */
Frame::Frame(Frame* f){
    _image = f->_image;
    _srcRect = f->_srcRect;
    _duration = f->_duration;
    _imageAccessCount = f->_imageAccessCount;
    (*_imageAccessCount)++;
}

Frame::Frame(SDL_Texture* texture, SDL_Rect srcRect, uint duration){
    _image = texture;
    _imageAccessCount = new uint(1);
    _srcRect = srcRect;
    _duration = duration;
}

Frame::~Frame(){
    (*_imageAccessCount)--;
    if(*_imageAccessCount == 0){
        SDL_DestroyTexture(_image);
        delete _imageAccessCount;
    }
}

SDL_Texture* Frame::getImage(){
    return _image;
}

SDL_Rect Frame::getSrcRect(){
    return _srcRect;
}

uint Frame::getDuration(){
    return _duration;
}

/*!
 * SEQUENCE CLASS
 * Sequence objects are used to:
 * - Load animations from file
 * - Represent animations in memory
 * - Get next frame in animation sequence
 */


Sequence::Sequence(Sequence* s){
    _name = s->_name;
    _currentFrame = s->_currentFrame;
    _totalScreenFrameCount = s->_totalScreenFrameCount;
    _screenFrameCounter = s->_screenFrameCounter;

    // Deep copy frames
    for(int i = 0; i < s->_frames.size(); i++){
        _frames.push_back(new Frame(s->_frames[i]));
    }
}

Sequence::Sequence(string descFilePath, SDL_Renderer* renderer){
    loadFromDescFile(descFilePath, renderer);
}

Sequence::Sequence(string descFilePath, string name, SDL_Renderer* renderer){
    loadFromDescFile(descFilePath, renderer);
    _name = name;
}

Sequence::Sequence(vector<Frame*> frames, string name){
    _frames = frames;
    _name = name;
    _currentFrame = 0;
    _totalScreenFrameCount = 0;
    for(auto& frame : _frames){
        _totalScreenFrameCount += frame->getDuration() / TIME_PER_FRAME;
    }
    _screenFrameCounter = 0;
}

Sequence::~Sequence(){
    for(int i = 0; i < _frames.size(); i++){
        delete _frames[i];
    }
}

/*!
 * Get next frame image in animation sequence to be rendered
 * */
SDL_Texture* Sequence::getNextFrame(){
    // Loop animation
    // Find correct frame to display
    int durationSum = 0;
    for(int i = 0; i < _frames.size(); i++){
        // Floor division to select correct frame to display
        if(durationSum / (_screenFrameCounter + 1) > 0){
            _screenFrameCounter++;
            return _frames[i]->getImage();
        }
        durationSum += _frames[i]->getDuration();
    }
    _screenFrameCounter = 0;
    return _frames[_currentFrame]->getImage();
}

SDL_Rect Sequence::getSrcRect(){
    if(_frames.size() > 0){
        return _frames[_currentFrame]->getSrcRect();
    }else{
        return {0, 0, 0, };
    }
}


/*!
 * Get the current frame, without incrementing
 * the sequence screen frame counter
 * */
SDL_Texture* Sequence::getCurrentFrame(){
    if(_frames.size() > 0){
        return _frames[_currentFrame]->getImage();
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
    string imageFilePath = ASSETS_ANIMATIONS_PATH + objects["meta"]["image"].get<string>();
    int width = objects["meta"]["size"]["w"].get<int>();
    int height = objects["meta"]["size"]["h"].get<int>();

    SDL_Texture* fullImage = IMG_LoadTexture(renderer, imageFilePath.c_str());
    // Get frame metadata
    // Fields to read from each frame:
    // - "frame" contains what pixels from the image the frame contains
    // - "duration" contains how long the frame should  be displayed, in ms
    //
    // Check if Field "frameTags" exist
    //
    // Else use tag "frames" as one sequence
    json frames = objects["frames"];
    for(auto it = frames.begin(); it != frames.end(); ++it){
        // Get sub-image size
        SDL_Rect srcRect;
        srcRect.x = it.value()["frame"]["x"].get<int>();
        srcRect.y = it.value()["frame"]["y"].get<int>();
        srcRect.w = it.value()["frame"]["w"].get<int>();
        srcRect.h = it.value()["frame"]["h"].get<int>();
        SDL_Rect destRect = {0,0,srcRect.w, srcRect.h};
        // Copy the correct part of the full image
        // Potential FIXME, pixelformat and texture access
        SDL_Texture* image = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, srcRect.w, srcRect.h);
        // FIXME how to handle transparency?
        SDL_SetRenderTarget(renderer, image);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        SDL_SetTextureBlendMode(image, SDL_BLENDMODE_BLEND);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, fullImage, &srcRect, &destRect);
        // Reset target back to screen
        SDL_SetRenderTarget(renderer, NULL);
        // Get frame duration and convert it to screen frames 
        uint duration = (uint)(it.value()["duration"].get<uint>() / (TIME_PER_FRAME * 1.f));
        // Add frame to sequence
        _frames.push_back(new Frame(image, destRect, duration));
    }
    // Free sprite sheet image
    SDL_DestroyTexture(fullImage);
    // Set current frame to first frame
    _currentFrame = 0;
    // Calcuate total frame duration
    _totalScreenFrameCount = 0;
    for(int i = 0; i < _frames.size(); i++){
        _totalScreenFrameCount += _frames[i]->getDuration();
    }
    _name = jsonFileName;
    _screenFrameCounter = 0;
}

string Sequence::getName(){
    return _name;
}

// --------------------------------
/*!
 * ANIMATOR CLASS
 * Animator objects are responsible for changing between sequences
 *
 * */

/*!
 * Default constructor for animator
 * Sets default texture to a pink square
 * */
Animator::Animator(){
    _defaultTexture = Texture::DEFAULT_PINK_TEXTURE;
    _useDefaultTexture = true;
    _textureSharedAccessCounter = new int(1);
}

/*!
 * Copy constructor
 * */
Animator::Animator(Animator* a){
    // Deep copy sequences
    for(auto& [name, seq] : a->_sequences){
        _sequences.insert({name, new Sequence(seq)});
    }
    _currentSequenceName = a->_currentSequenceName;
    _defaultTexture = a->_defaultTexture;
    _textureSharedAccessCounter = a->_textureSharedAccessCounter;
    (*_textureSharedAccessCounter)++;
    _useDefaultTexture = a->_useDefaultTexture;
    _defaultTextureSrcRect = a->_defaultTextureSrcRect;
}

Animator::Animator(SDL_Texture* defaultTexture){
    _defaultTexture = defaultTexture;
    _defaultTextureSrcRect.x = 0;
    _defaultTextureSrcRect.y = 0;
    SDL_QueryTexture(_defaultTexture, NULL, NULL, &_defaultTextureSrcRect.w, &_defaultTextureSrcRect.h);
    _textureSharedAccessCounter = new int(1);
    _useDefaultTexture = true;
}

Animator::Animator(std::string descFilePath, SDL_Renderer* renderer){
    initFromDescFile(descFilePath, renderer);
    _defaultTexture = Texture::DEFAULT_PINK_TEXTURE;
    _textureSharedAccessCounter = new int(1);
}

Animator::Animator(std::map<std::string, Sequence*> sequences){
    _sequences = sequences;
    _useDefaultTexture = false;
    _currentSequenceName = _sequences.begin()->first;
    _defaultTexture = _sequences.begin()->second->getCurrentFrame();
    _defaultTextureSrcRect.x = 0;
    _defaultTextureSrcRect.y = 0;
    SDL_QueryTexture(_defaultTexture, NULL, NULL, &_defaultTextureSrcRect.w, &_defaultTextureSrcRect.h);
    _textureSharedAccessCounter = new int(1);
}

Animator::Animator(vector<string> sequenceDescFileNames, SDL_Renderer* renderer){
    // Construct sequences from files
    for(auto filename : sequenceDescFileNames){
        Sequence* tempSeq = new Sequence(filename, renderer);
        _sequences.insert({tempSeq->getName(), tempSeq});
        _currentSequenceName = tempSeq->getName();
    }
    // Use first frame as default texture
    _defaultTexture = _sequences.begin()->second->getCurrentFrame();
    _defaultTextureSrcRect.x = 0;
    _defaultTextureSrcRect.y = 0;
    SDL_QueryTexture(_defaultTexture, NULL, NULL, &_defaultTextureSrcRect.w, &_defaultTextureSrcRect.h);
    _textureSharedAccessCounter = new int(1);
    _useDefaultTexture = false;
}

/*!
 * Creates an animator object and loads sequences from file(s).
 * @param[in] sequenceDescFileNames Path(s) to sequence descriptor file(s)
 * @param[in] sequenceNames Names of sequences (same indexing as files)
 * @param[in] renderer SDL renderer to handle images
 * */
Animator::Animator(vector<string> sequenceDescFileNames, vector<string> sequenceNames, SDL_Renderer* renderer){
    // Construct sequences from files
    for(int i = 0; i < sequenceDescFileNames.size(); i++){
        Sequence* tempSeq = new Sequence(sequenceDescFileNames[i], sequenceNames[i], renderer);
        _sequences.insert({tempSeq->getName(), tempSeq});
        _currentSequenceName = tempSeq->getName();
    }
    // Use first frame as default texture
    _defaultTexture = _sequences.begin()->second->getCurrentFrame();
    _defaultTextureSrcRect.x = 0;
    _defaultTextureSrcRect.y = 0;
    SDL_QueryTexture(_defaultTexture, NULL, NULL, &_defaultTextureSrcRect.w, &_defaultTextureSrcRect.h);
    _textureSharedAccessCounter = new int(1);
    _useDefaultTexture = false;

}

Animator::~Animator(){
    (*_textureSharedAccessCounter)--;
    if(*_textureSharedAccessCounter == 0){
        // Defaut texture gets freed in Game.cpp
        if(_defaultTexture != Texture::DEFAULT_PINK_TEXTURE){
            SDL_DestroyTexture(_defaultTexture);
        }
        delete _textureSharedAccessCounter;
    }
    // Free surfaces
    for(auto& [key, seq] : _sequences){
        delete seq;
    }
}

/*!
 * Get next frame to be displayed
 * */
SDL_Texture* Animator::getNextFrame(){
    if(_useDefaultTexture || _sequences.size() == 0){
        return _defaultTexture;
    }
    return _sequences[_currentSequenceName]->getNextFrame();
}

/*!
 * Get current sequence name
 * */
string Animator::getCurrentSequence(){
    return _currentSequenceName;
}

/*!
 * Select sequence by name
 * If the parameter sequenceName is not valid, the old sequence is kept
 * */
void Animator::selectSequence(string sequenceName){
    // Check if sequenceName exists in _sequences
    // If the name is in keys, count will be 1
    if(_sequences.count(sequenceName)){
        _currentSequenceName = sequenceName;
    }
    // If the name is not valid, keep the current one
}

/*!
 * Get the current frame image without incrementing the counter
 * Wrapper to get texture from sequence
 * */
SDL_Texture* Animator::getCurrentFrame(){
    if(_useDefaultTexture || _sequences.size() == 0){
        return _defaultTexture;
    }
    return _sequences[_currentSequenceName]->getCurrentFrame();
}


/*!
 * Get default texture, used as placeholder / when no animations are playing
 * */
SDL_Texture* Animator::getDefaultTexture(){
    return _defaultTexture;
}

void Animator::useDefaultTexture(bool useDefault){
    _useDefaultTexture = useDefault;
}

bool Animator::getUsingDefaultTexture(){
    return _useDefaultTexture;
}

SDL_Rect Animator::getSrcRect(){
    if(_useDefaultTexture){
        return _defaultTextureSrcRect;
    }else if(_sequences.size() > 0){
        return _sequences[_currentSequenceName]->getSrcRect();
    }
}

/*!
 * Init sequences from a JSON description file
 * */
void Animator::initFromDescFile(string descFilePath, SDL_Renderer* renderer){
    // Load file
    ifstream inputfile(descFilePath);
    json objects = json::parse(inputfile);
    // Get metadata
    // Get image file path
    string imageFilePath = ASSETS_ANIMATIONS_PATH + objects["meta"]["image"].get<string>();
    // Get full sprite sheet image
    SDL_Texture* fullImage = IMG_LoadTexture(renderer, imageFilePath.c_str());
    // Read frames
    vector<Frame*> frames;
    for(auto& frameDesc : objects["frames"]){
        // Get image size & position in sprite sheet
        SDL_Rect srcRect;
        srcRect.x = frameDesc["frame"]["x"].get<int>();
        srcRect.y = frameDesc["frame"]["y"].get<int>();
        srcRect.w = frameDesc["frame"]["w"].get<int>();
        srcRect.h = frameDesc["frame"]["h"].get<int>();
        SDL_Rect destRect = {0, 0, srcRect.w, srcRect.h};
        // Get frame duration in ms
        uint duration = frameDesc["duration"].get<uint>();
        // Get sub-image from full image
        SDL_Texture* image = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, srcRect.w, srcRect.h);
        SDL_SetRenderTarget(renderer, image);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        SDL_SetTextureBlendMode(image, SDL_BLENDMODE_BLEND);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, fullImage, &srcRect, &destRect);
        // Reset render target to screen
        SDL_SetRenderTarget(renderer, NULL);
        // Create frame object and add it to list
        frames.push_back(new Frame(image, destRect, duration));
    }
    // First check if "frameTags" is defined 
    if(objects.contains("frameTags")){
        // Use names defined in this JSON
        json frameTags = objects["meta"]["frameTags"];
        for(auto& sequence : frameTags){
            // iterator sequence is a list element
            // Get name
            string name = sequence["name"].get<string>();
            // Get correct frames
            int startIndex = sequence["from"].get<int>();
            int endIndex = sequence["to"].get<int>();
            vector<Frame*> sequenceFrames;
            for(int i = startIndex; i <= endIndex; i++){
                sequenceFrames[i - startIndex] = frames[i];
            }
            // Create sequence
            _sequences.insert({name, new Sequence(sequenceFrames, name)});
            _currentSequenceName = name;
        }
    }else{
        // Treat all frames as one sequence
        // Name the sequence to default name
        _sequences.insert({DEFAULT_SEQUENCE_NAME, new Sequence(frames, DEFAULT_SEQUENCE_NAME)});
        _currentSequenceName = DEFAULT_SEQUENCE_NAME;
    }
    // Close file
    inputfile.close();
    // Set to not use default texture
    _useDefaultTexture = false;
}
