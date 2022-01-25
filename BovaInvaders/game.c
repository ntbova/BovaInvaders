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
                    case SDLK_LEFT:
                        if (spaceShipRect.x > 0) { spaceShipRect.x = spaceShipRect.x - SPACE_SHIP_SPEED; }
                        break;
                    case SDLK_RIGHT:
                        if (spaceShipRect.x < SCREEN_WIDTH - SPACE_SHIP_WIDTH) { spaceShipRect.x = spaceShipRect.x + SPACE_SHIP_SPEED; }
                        break;
				}
			}

			SDL_Renderer* mainRenderer = getMainRenderer();
			// Clear screen
			SDL_RenderClear(mainRenderer);

			// Render board to the screen
			SDL_RenderCopy(mainRenderer, spaceShipTexture, NULL, &spaceShipRect);

			// Update screen
			SDL_RenderPresent(mainRenderer);
		}
	}

	return 1;
}

int game_close()
{
	return 1;
}
