#include "LevelLoader.h"

using namespace std;
using json = nlohmann::json;

// TODO add hitbox support for player and platform

LevelLoader::LevelLoader(SDL_Renderer* renderer){
    _renderer = renderer;
}

Platform* LevelLoader::platformFromJson(json::object_t object, int id){
    Vector2 pos = {object["position"]["x"].get<float>(), object["position"]["y"].get<float>()};

    return new Platform(object["TexturePath"].get<string>().c_str(), _renderer, pos, object["name"].get<string>().c_str(), id);
}

Player* LevelLoader::playerFromJson(json::object_t object, int id){
    Vector2 pos = {object["position"]["x"].get<float>(), object["position"]["y"].get<float>()};

    return new Player(object["TexturePath"].get<string>().c_str(), _renderer, pos);
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
    //          "Hitboxes": {}
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

GameObject* LevelLoader::loadGameObjectFromJson(json::object_t object, int id){
    // Load GameObject from json string
    string type = object["type"].get<string>();
    if(type == PLATFORM_TYPE){
        return platformFromJson(object, id);
    }else if(type == PLAYER_TYPE){
        return playerFromJson(object, id);
    }else if(type == HITBOX_TYPE){
        hitboxFromJson(object);
    }
}