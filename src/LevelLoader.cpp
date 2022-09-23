#include "LevelLoader.h"

using namespace std;
using json = nlohmann::json;

// TODO add hitbox support for player and platform

LevelLoader::LevelLoader(SDL_Renderer* renderer){
    _renderer = renderer;
}

Platform* LevelLoader::platformFromJson(GameObject* base, int id){
    Platform* out = new Platform(base, id);
    return out;
}

Player* LevelLoader::playerFromJson(GameObject* base, int id){
    Player* out = new Player(base, id);
    return out;
}

Hitbox* LevelLoader::hitboxFromJson(json::object_t object){
    Vector2 pos = {object["position"]["x"].get<float>(), object["position"]["y"].get<float>()};
    Vector2 size = {object["size"]["x"].get<float>(), object["size"]["y"].get<float>()};
    
    return new Hitbox(pos, size, object["mask"].get<int>());
}

vector<GameObject*> LevelLoader::loadLevelFromFile(string path){
    // Loads all gameobjects in level from json file
    // Basic gameobjects are stored in json format like this:
    //  "id": {
    //          "name": [string],
    //          "type": [string],
    //          "position": {"x": [float], "y":[float]},
    //          "TexturePath": [string],
    //          "Hitboxes": {},
    //          "animator":{
    //              "sequnce_name": "json_path"
    //          }
    //        }

    // Parse the json file
    ifstream inputfile(path);
    json objects = json::parse(inputfile);

    vector<GameObject*> objectList = vector<GameObject*>();
    

    for(int i = 0; i < objects.size(); i++){
        objectList.push_back(loadGameObjectFromJson(objects[to_string(i)].get<json::object_t>(), i));
    }

    return objectList;
}

GameObject* LevelLoader::loadGameObjectFromJson(json object, int id){
    // Load GameObject from json string
    GameObject go = GameObject(_renderer);
    // Read fields common to all gameobjects
    go.setName(object["name"].get<string>());
    go.setPosition(Vector2(object["position"]["x"].get<float>(), object["position"]["y"].get<float>()));
    // If field animation present, init animator
    if(object.contains("animations")){
        // Animations defined in json
        if(!object["animations"].empty()){
            vector<string> fileNames;
            for(auto &seq : object["animations"].items()){
                fileNames.push_back(ASSETS_ANIMATIONS_PATH + string(seq.value()));
            }
            go.initAnimator(fileNames);
        }else{
            // Get default texture
            // Load texture from file
            SDL_Texture* temp = IMG_LoadTexture(_renderer, string(ASSETS_PATH + object["TexturePath"].get<string>()).c_str());
            go.initAnimator(temp);
        }
    }else{
        SDL_Texture* temp = IMG_LoadTexture(_renderer, string(ASSETS_PATH + object["TexturePath"].get<string>()).c_str());
        go.initAnimator(temp);
    }
    // Create object of correct type
    string type = object["type"].get<string>();
    if(type == PLAYER_TYPE){
        return playerFromJson(&go, id);
    }else if(type == PLATFORM_TYPE){
        return platformFromJson(&go, id);
    }
}
