#include "LevelLoader.h"

/*!
 * Load level from JSON descriptor file
 * @param[in] levelFilePath Path to JSON descriptor file
 * @param[in] renderer SDL renderer to be used to create game objects
 * @return A list of loaded game objects
 * */
vector<GameObject*> LevelLoader::loadLevelFromFile(string levelFilePath, SDL_Renderer* renderer){
    // Load file
    ifstream inputFile(levelFilePath);
    // Load game objects as json objects
    json gameObjects = json::parse(inputFile);
    vector<GameObject*> out;
    // Load objects
    for(auto& go : gameObjects){
        // Load correct type of object
        string type = go["type"].get<string>();
        if(type == PLAYER_TYPE){
            out.push_back(LevelLoader::loadPlayer(go, renderer));
        }else if( type == PLATFORM_TYPE){
            out.push_back(LevelLoader::loadPlatform(go, renderer));
        }else{
            // Default loader goes here
        }
    }
    // Close file
    inputFile.close();

    return out;
}

/*!
 * Get position from JSON game object descriptor
 * @param[in] gameObjectDesc JSON descriptor of GameObject
 * @return The position of the object
 * */
Vector2 LevelLoader::loadPos(json gameObjectDesc){
    float x = gameObjectDesc["position"]["x"].get<float>();
    float y = gameObjectDesc["position"]["y"].get<float>();

    return Vector2(x, y);
}

/*!
 * Get name of object from JSON descriptor
 * @param[in] gameObjectDesc JSON descriptor of GameObject
 * @return The name of the object
 * */
string LevelLoader::loadName(json gameObjectDesc){
    return gameObjectDesc["name"].get<string>();
}

/*!
 * Load animator from JSON descriptor.
 * @param[in] gameObjectDesc JSON descriptor
 * return Animator object to be used with a GameObject
 * */
Animator* LevelLoader::loadAnimator(json gameObjectDesc, SDL_Renderer* renderer){
    if(gameObjectDesc.contains("animations")){
        string animatorDecsFilePath = ASSETS_ANIMATIONS_PATH + gameObjectDesc["animations"].get<string>();
        return new Animator(animatorDecsFilePath, renderer);
    }else if(gameObjectDesc.contains("TexturePath")){
        // Use default texture only
        string imagePath = IMAGES_PATH + gameObjectDesc["TexturePath"].get<string>();
        SDL_Texture* texture = IMG_LoadTexture(renderer, imagePath.c_str());
        return new Animator(texture);
    }else{
        // No viable animator load
        // Raise exception
        throw InvalidJsonException(gameObjectDesc);
    }
}

/*!
 * Load hitboxes from JSON descriptor
 * To be implemented
 * */
vector<Hitbox*> LevelLoader::loadHitboxes(json gameObjectDesc){
    return vector<Hitbox*>();
}

/*!
 * Load the player from JSON descriptor
 * @param[in] playerDesc JSON descriptor of player
 * @return The player object loaded from JSON
 * */
Player* LevelLoader::loadPlayer(json playerDesc, SDL_Renderer* renderer){
    Animator* anim = LevelLoader::loadAnimator(playerDesc, renderer);
    Vector2 pos = LevelLoader::loadPos(playerDesc);
    vector<Hitbox*> hitboxes = LevelLoader::loadHitboxes(playerDesc);
    string name = LevelLoader::loadName(playerDesc);

    cout << "Pos: " << pos.x << " " << pos.y << endl;
    cout << "Name: " << name << endl;
    return new Player(renderer, anim, hitboxes, pos, name);
}

/*!
 * Load a platform from JSON desc
 * @param[in] platformDesc JSON descriptor of platform
 * @return A platform object loaded from JSON
 * */
Platform* LevelLoader::loadPlatform(json platformDesc, SDL_Renderer* renderer){
    Animator* anim = LevelLoader::loadAnimator(platformDesc, renderer);
    Vector2 pos = LevelLoader::loadPos(platformDesc);
    vector<Hitbox*> hitboxes = LevelLoader::loadHitboxes(platformDesc);
    string name = LevelLoader::loadName(platformDesc);

    cout << "Pos: " << pos.x << " " << pos.y << endl;
    cout << "Name: " << name << endl;

    return new Platform(renderer, anim, hitboxes, pos, name);
}
