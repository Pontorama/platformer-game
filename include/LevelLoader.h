#ifndef LevelLoader_h
#define LevelLoader_h

#include "json.hpp" 
#include <vector>
#include <string>
#include <iostream>
#include "SDL2/SDL.h"
#include "Vector2.h"
#include "Hitbox.h"
#include "Constants.h"
#include "Animator.h"
#include "GameExceptions.h"
// Include Game object types
#include "GameObject.h"
#include "Player.h"
#include "Platform.h"

using namespace std;
using json = nlohmann::json;

namespace LevelLoader {
    vector<GameObject*> loadLevelFromFile(string levelFilePath, SDL_Renderer* renderer);
    Vector2 loadPos(json gameObjectDesc);
    string loadName(json gameObjectDesc);
    Animator* loadAnimator(json gameObjectDesc, SDL_Renderer* renderer);
    vector<Hitbox*> loadHitboxes(json gameObjectDesc);
    Player* loadPlayer(json playerDesc, SDL_Renderer* renderer);
    Platform* loadPlatform(json platformDesc, SDL_Renderer* renderer);
};

#endif
