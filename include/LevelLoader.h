#ifndef LevelLoader_h
#define LevelLoader_h

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

#include "json.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "GameObject.h"
#include "Player.h"
#include "Constants.h"
#include "Hitbox.h"
#include "Vector2.h"
#include "Platform.h"


using namespace std;
using json = nlohmann::json;

class LevelLoader{
    public:
        LevelLoader(SDL_Renderer* renderer);
        vector<GameObject*> loadLevelFromFile(string path);
        GameObject* loadGameObjectFromJson(json::object_t object, int id);

    private:
        SDL_Renderer* _renderer;
        
        Platform* platformFromJson(json::object_t object, int id);
        Player* playerFromJson(json::object_t object, int id);

        Hitbox* hitboxFromJson(json::object_t object);

};

#endif