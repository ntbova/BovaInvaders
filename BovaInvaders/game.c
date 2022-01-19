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
	SDL_Texture* gameBoardTexture = loadTextureFromPath("");

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

			SDL_Renderer* mainRenderer = getMainRenderer();
			// Clear screen
			SDL_RenderClear(mainRenderer);

			// Render board to the screen
			SDL_RenderCopy(mainRenderer, gameBoardTexture, NULL, NULL);

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
