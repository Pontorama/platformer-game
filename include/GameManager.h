#ifndef GameManager_h
#define GameManager_h

#include "GameObject.h"

/*
 * Interface to access game objects from the service locator
 *
 * */
class GameManager {
    public:
        GameManager();
        virtual GameObject* getGameObject(string name);
        virtual GameObject* getGameObject(int id);
};

#endif
