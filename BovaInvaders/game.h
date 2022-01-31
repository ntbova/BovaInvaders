#ifndef GAME_H
#define GAME_H
#include "sdlhelper.h"

#define SPACE_SHIP_WIDTH 50
#define SPACE_SHIP_HEIGHT 50
#define SPACE_SHIP_SPEED 2
#define BULLET_SPEED 6
#define BULLET_DELAY 500

int game_init(void);
int game_loop(void);
void render_loop(void);
int game_close(void);
#endif
