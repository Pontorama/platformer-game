#ifndef Constants_h
#define Constants_h

// Framerates
const int FRAMERATE = 60;
const float TIME_PER_FRAME = 1000/FRAMERATE;

// Window constants
const int DEFAULT_WINDOW_WIDTH = 1200;
const int DEFAULT_WINDOW_HEIGHT = 900;
const float SCALE_FACTOR_X = 5;
const float SCALE_FACTOR_Y = 5;

// Physics constants
const float GRAVITY = 0.01;
const float SMALL_DIST = 0.01;
// Masks
const int DEFAULT_MASK = 0;
const int TERRAIN_MASK = 1;
const int PLAYER_MASK = 10;

// Debug
const int DEBUG_MODE = 1;

#endif