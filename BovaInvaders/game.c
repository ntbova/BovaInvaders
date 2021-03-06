#include "game.h"
#include "render.h"

int game_init(GameState* state) {
    state->ship_pos_x = SCREEN_WIDTH / 2; state->ship_pos_y = SCREEN_HEIGHT - SPACE_SHIP_HEIGHT;
    for (int i = 0; i < NUM_BULLETS; i++) {
        state->bullet_pos_x[i] = INT32_MIN; state->bullet_pos_y[i] = INT32_MIN;
    }
    // Set up position of enemies based on grid margin, enemy size, and number of enemies
    // per row and per column
    int currX = ENEMY_GRID_MARGIN, currY = 0;
    for (int i = 0; i < NUM_ENEMIES; i++) {
        if (i % NUM_ENEMIES_COL == 0) {
            currX = ENEMY_GRID_MARGIN; currY = currY + ENEMY_HEIGHT;
        }
        else {
            currX = currX + ENEMY_WIDTH + ENEMY_MARGIN;
        }
        state->enemy_pos_x[i] = currX;
        state->enemy_pos_y[i] = currY;
    }
    return 1;
}

int game_loop() {
    // Game assets/variables
	int gameRunning = 1;
    GameState state; RenderAssets assets;
    // Initialize game state
    game_init(&state);
    // Initialize render assets through render_init, using game state values
    render_init(&assets, &state);
    
    Uint32 totalGameTime = 0, bulletTime = 0;
    
	SDL_Event e;

    // Start actual game loop
	while (gameRunning) {
        // Get total game time to use for various physics calcs
        totalGameTime = SDL_GetTicks();
        
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				gameRunning = 0;
			}
			else if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
					case SDLK_ESCAPE:
						gameRunning = 0;
						break;
				}
			}
		}
        
        // Handle keystate of user inputs here
        const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
        if(currentKeyStates[ SDL_SCANCODE_LEFT ]) {
            // Move ship left unless it's at the left edge of the screen
            if (state.ship_pos_x > 0) { state.ship_pos_x = state.ship_pos_x - SPACE_SHIP_SPEED; }
        }
        if (currentKeyStates[ SDL_SCANCODE_RIGHT ]) {
            // Move ship right unless it's at the right edge of the screen
            if (state.ship_pos_x < SCREEN_WIDTH - SPACE_SHIP_WIDTH) { state.ship_pos_x = state.ship_pos_x + SPACE_SHIP_SPEED; }
        }
        if (currentKeyStates[ SDL_SCANCODE_SPACE ]) {
            // If we haven't reached the max
             if (totalGameTime - bulletTime > BULLET_DELAY)
            {
                for (int i = 0; i < NUM_BULLETS; i++) {
                    if (state.bullet_pos_x[i] == INT32_MIN && state.bullet_pos_y[i] == INT32_MIN) {
                        state.bullet_pos_x[i] = state.ship_pos_x + (SPACE_SHIP_WIDTH / 2);
                        state.bullet_pos_y[i] = SCREEN_HEIGHT - (SPACE_SHIP_HEIGHT);
                        bulletTime = SDL_GetTicks();
                        break;
                    }
                }
            }
            // Otherwise don't shoot any more bullets
        }
        
        // Go over each bullet. If there are any on screen, keep them moving. If they move off screen,
        // then set there position to int min.
        for (int i = 0; i < NUM_BULLETS; i++) {
            if (state.bullet_pos_x[i] != INT32_MIN && state.bullet_pos_y[i] != INT32_MIN) {
                state.bullet_pos_y[i] = state.bullet_pos_y[i] - BULLET_SPEED;
                if (state.bullet_pos_y[i] < -SPACE_SHIP_HEIGHT) {
                    state.bullet_pos_x[i] = INT32_MIN; state.bullet_pos_y[i] = INT32_MIN;
                }
            }
        }
        
        // After moving bullets, check to see if any have collided with the enemies, remove
        // enemies from screen if they do
        for (int i = 0; i < NUM_BULLETS; i++) {
            for (int j = 0; j < NUM_ENEMIES; j++) {
                if (check_collision(assets.bulletRects[i], assets.enemyRects[j]) == 1) {
                    state.enemy_pos_x[j] = INT32_MAX; state.enemy_pos_y[j] = INT32_MAX;
                    state.bullet_pos_x[i] = INT32_MIN; state.bullet_pos_y[i] = INT32_MIN;
                }
            }
        }
        
        // Modify render assets based on current state
        assets.shipRect.x = state.ship_pos_x;
        assets.shipRect.y = state.ship_pos_y;
        
        for (int i = 0; i < NUM_BULLETS; i++) {
            assets.bulletRects[i].x = state.bullet_pos_x[i];
            assets.bulletRects[i].y = state.bullet_pos_y[i];
        }
        for (int i = 0; i < NUM_ENEMIES; i++) {
            assets.enemyRects[i].x = state.enemy_pos_x[i];
            assets.enemyRects[i].y = state.enemy_pos_y[i];
        }
        // Render using render assets
        render_game_state(&assets);
	}

	return 1;
}

int game_close() {
	return 1;
}
