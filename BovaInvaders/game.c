#include "sdlhelper.h"
#include "game.h"

int game_init() {
	if (sdl_init() == 0) {
		return 0;
	}
    
    return 1;
}

int game_loop() {
    // Game assets/variables
	int gameRunning = 1;
	SDL_Texture* spaceShipTexture = loadTextureFromPath("Resources/space_ship.bmp");
    SDL_Texture* shipBulletTexture = loadTextureFromPath("Resources/ship_bullet.bmp");
    SDL_Rect spaceShipRect;
    spaceShipRect.h = SPACE_SHIP_HEIGHT; spaceShipRect.w = SPACE_SHIP_WIDTH;
    spaceShipRect.x = SCREEN_WIDTH / 2; spaceShipRect.y = SCREEN_HEIGHT - SPACE_SHIP_HEIGHT;
    // Allow up to two bullets on screen (Will change this at some point to have an array of
    // arbitrary bullets on screen so that I change the amount as a settings whenever I want
    SDL_Rect shipBulletOneRect, shipBulletTwoRect;
    shipBulletOneRect.h = SPACE_SHIP_HEIGHT; shipBulletOneRect.w = SPACE_SHIP_WIDTH;
    shipBulletOneRect.x = INT32_MIN; shipBulletOneRect.y = INT32_MIN;
    shipBulletTwoRect.h = SPACE_SHIP_HEIGHT; shipBulletTwoRect.w = SPACE_SHIP_WIDTH;
    shipBulletTwoRect.x = INT32_MIN; shipBulletTwoRect.y = INT32_MIN;
    Uint32 totalGameTime = 0, bulletOneTime = 0, bulletTwoTime = 0;
    
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
            if (spaceShipRect.x > 0) { spaceShipRect.x = spaceShipRect.x - SPACE_SHIP_SPEED; }
        }
        if (currentKeyStates[ SDL_SCANCODE_RIGHT ]) {
            // Move ship right unless it's at the right edge of the screen
            if (spaceShipRect.x < SCREEN_WIDTH - SPACE_SHIP_WIDTH) { spaceShipRect.x = spaceShipRect.x + SPACE_SHIP_SPEED; }
        }
        if (currentKeyStates[ SDL_SCANCODE_SPACE ]) {
            // If there are no bullets on screen, reset the position of first one to above where
            // the space ship is
            if (shipBulletOneRect.x == INT32_MIN && shipBulletOneRect.y == INT32_MIN) {
                shipBulletOneRect.x = spaceShipRect.x; shipBulletOneRect.y = SCREEN_HEIGHT - (SPACE_SHIP_HEIGHT * 2);
                bulletOneTime = SDL_GetTicks();
            }
            // Else, set the second bullet to to where the space ship is (don't fire second shot until
            // enough time has passed since the first shot
            else if (shipBulletTwoRect.x == INT32_MIN && shipBulletTwoRect.y == INT32_MIN
                     && SDL_GetTicks() - bulletOneTime > BULLET_DELAY) {
                shipBulletTwoRect.x = spaceShipRect.x; shipBulletTwoRect.y = SCREEN_HEIGHT - (SPACE_SHIP_HEIGHT * 2);
                bulletTwoTime = SDL_GetTicks();
            }
            // Otherwise don't shoot any more bullets
        }
        
        // If bullets are on screen, make sure to make them move up the screen until they are no longer visible
        if (bulletOneTime != 0) {
            shipBulletOneRect.y = shipBulletOneRect.y - BULLET_SPEED;
            if (shipBulletOneRect.y < -SPACE_SHIP_HEIGHT) {
                shipBulletOneRect.x = INT32_MIN; shipBulletOneRect.y = INT32_MIN;
                bulletOneTime = 0;
            }
        }
        if (bulletTwoTime != 0) {
            shipBulletTwoRect.y = shipBulletTwoRect.y - BULLET_SPEED;
            if (shipBulletTwoRect.y < -SPACE_SHIP_HEIGHT) {
                shipBulletTwoRect.x = INT32_MIN; shipBulletTwoRect.y = INT32_MIN;
                bulletTwoTime = 0;
            }
        }
        
        SDL_Renderer* mainRenderer = getMainRenderer();
        // Clear screen
        SDL_RenderClear(mainRenderer);

        // Render board to the screen
        SDL_RenderCopy(mainRenderer, spaceShipTexture, NULL, &spaceShipRect);
        SDL_RenderCopy(mainRenderer, shipBulletTexture, NULL, &shipBulletOneRect);
        SDL_RenderCopy(mainRenderer, shipBulletTexture, NULL, &shipBulletTwoRect);

        // Update screen
        SDL_RenderPresent(mainRenderer);
	}

	return 1;
}

int game_close() {
	return 1;
}
