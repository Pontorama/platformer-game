#ifndef Constants_h
#define Constants_h
const int FRAMERATE = 60;
const float TIME_PER_FRAME = 1000/FRAMERATE;
const int DEFAULT_WINDOW_WIDTH = 1200;
const int DEFAULT_WINDOW_HEIGHT = 900;
const int PLAYER_SIZE = 128;
const float SCALE_FACTOR_X = PLAYER_SIZE / DEFAULT_WINDOW_WIDTH;
const float SCALE_FACTOR_Y = PLAYER_SIZE / DEFAULT_WINDOW_HEIGHT;
const float GRAVITY = 9.82;
#endif