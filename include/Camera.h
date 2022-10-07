#ifndef Camera_h
#define Camera_h

#include "SDL2/SDL.h"
#include "Vector2.h"
#include "GameObject.h"
#include "UIElement.h"
#include "RenderUtils.h"
#include "CameraUtils.h"
#include "DebugLogger.h"
#include <vector>
#include "ServiceLocator.h"

using namespace Vector;
using namespace std;

class Camera {
    public:
        Camera(SDL_Renderer* renderer);
        ~Camera();
        void renderGameObjects(vector<GameObject*> objectsToRender);
        void renderUI(vector<UIElement*> uiElementsToRender);
        void renderDebug();
        void renderDebug(vector<GameObject*> objectsToRender);
        void drawToScreen();
        void move();
        void update();
        Vector2 translateWorldToScreen(Vector2 worldPos);
        SDL_Rect translateWorldToScreen(SDL_Rect worldRect);
        Vector2 translateScreenToWorld(Vector2 screenPos);
        SDL_Rect translateScreenToWorld(SDL_Rect screenRect);
        void setZoom(float zoomLevel);
        void teleport(Vector2 newPos);
        void setFollowMode(bool follow);
        void setObjectToFollow(GameObject* objToFollow);
        void clearObjectToFollow();

    private:
        SDL_Renderer* _renderer;
        Vector2 _pos; // Camera position in world coordinates
        Vector2 _dir;
        Vector2 _viewSize; // Camera output size in pixels
        SDL_Rect _focusZone; // Zone which should always be in view, in world coordinate units
        float _scrollSpeedX; // Speed at which the camera moves in x direction, in pixels/unit time
        float _scrollSpeedY; // Speed at which the camera moves in y direction, in pixels/unit time
        float _zoomLevel; // Ratio between pixels on screen and world units
        Vector2 _focusPoint; // Point in the center of the camera view, in world coordinates
        bool _followMode;
        GameObject* _objToFollow; // This should NOT be freed by the camera

        void renderObject(GameObject* go);
        void init();
};

#endif
