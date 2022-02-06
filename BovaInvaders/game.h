#ifndef GAME_H
#define GAME_H

#define SPACE_SHIP_WIDTH 50
#define SPACE_SHIP_HEIGHT 50
#define SPACE_SHIP_SPEED 2
#define BULLET_SPEED 4
#define ENEMY_SPEED 4
#define NUM_BULLETS 2
#define NUM_ENEMIES 30
#define BULLET_DELAY 500

typedef struct GameStates {
    int ship_pos_x;
    int ship_pos_y;
    int bullet_pos_x[NUM_BULLETS];
    int bullet_pos_y[NUM_BULLETS];
    int enemy_pos_x[NUM_ENEMIES];
    int enemy_pos_y[NUM_ENEMIES];
} GameState;

int game_init(GameState*);
int game_loop(void);
void render_loop(void);
int game_close(void);
#endif
