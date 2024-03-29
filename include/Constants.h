#ifndef Constants_h
#define Constants_h

#include <string>

// Framerates
const int FRAMERATE = 60;
const float TIME_PER_FRAME = 1000.0/FRAMERATE;

// Window constants
const int DEFAULT_WINDOW_WIDTH = 1200;
const int DEFAULT_WINDOW_HEIGHT = 900;
const float SCALE_FACTOR_X = 5;
const float SCALE_FACTOR_Y = 5;

// Physics constants
const float GRAVITY = 0.005;
const float SMALL_DIST = 0.01;
// Masks
const int DEFAULT_MASK = 0;
const int TERRAIN_MASK = 1;
const int INVISIBLE_MASK = 2; // For non-colliding objects
const int PLAYER_MASK = 10;

// Game object types for level loading
const std::string PLATFORM_TYPE = "Platform";
const std::string PLAYER_TYPE = "Player";
const std::string HITBOX_TYPE = "Hitbox";


// Paths
const std::string ASSETS_PATH = "/home/pongu/dev/platformer-game/assets/";
const std::string IMAGES_PATH = ASSETS_PATH + "images/";
const std::string ASSETS_ANIMATIONS_PATH = ASSETS_PATH + "Animations/";
const std::string PLAYER_TEXTURE_PATH = ASSETS_PATH + "images/Dude.png";
const std::string DEFAULT_PINK_IMAGE = ASSETS_PATH + "images/Default_image.png";

// Debug flags
const int DEBUG_MODE = 1; // General debug mode
const bool CAMERA_DEBUG_MODE = 1; // Render border around focus zone, show center point


#endif
