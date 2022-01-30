#include "sdlhelper.h"
#include "game.h"

int game_init()
{
	if (sdl_init() == 0)
	{
		return 0;
	}
    
    return 1;
}

int game_loop()
{
	int gameRunning = 1;
	SDL_Texture* spaceShipTexture = loadTextureFromPath("Resources/space_ship.bmp");
    SDL_Rect spaceShipRect;
    spaceShipRect.h = SPACE_SHIP_HEIGHT; spaceShipRect.w = SPACE_SHIP_WIDTH;
    spaceShipRect.x = SCREEN_WIDTH / 2; spaceShipRect.y = SCREEN_HEIGHT - SPACE_SHIP_HEIGHT;
    
	SDL_Event e;

	while (gameRunning)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				gameRunning = 0;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						gameRunning = 0;
						break;
				}
			}
		}
        
        // Handle keystate of user inputs here
        const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
        if(currentKeyStates[ SDL_SCANCODE_LEFT ])
        {
            // Move ship left unless it's at the left edge of the screen
            if (spaceShipRect.x > 0) { spaceShipRect.x = spaceShipRect.x - SPACE_SHIP_SPEED; }
        }
        if (currentKeyStates[ SDL_SCANCODE_RIGHT ])
        {
            // Move ship right unless it's at the right edge of the screen
            if (spaceShipRect.x < SCREEN_WIDTH - SPACE_SHIP_WIDTH) { spaceShipRect.x = spaceShipRect.x + SPACE_SHIP_SPEED; }
        }
        
        SDL_Renderer* mainRenderer = getMainRenderer();
        // Clear screen
        SDL_RenderClear(mainRenderer);

        // Render board to the screen
        SDL_RenderCopy(mainRenderer, spaceShipTexture, NULL, &spaceShipRect);

        // Update screen
        SDL_RenderPresent(mainRenderer);
	}

	return 1;
}

int game_close()
{
	return 1;
}
