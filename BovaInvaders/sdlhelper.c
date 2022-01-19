#include "sdlhelper.h"

SDL_Window* _mainWindow;
SDL_Renderer* _mainRenderer;
SDL_PixelFormat* _mainPixelFormat;

int sdl_init()
{
	// Run SDL's init
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Failed to initialize SDL: %s", SDL_GetError());
		return 0;
	}
	else
	{
		// Create Main Window
        _mainWindow = SDL_CreateWindow("SDL Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (_mainWindow == NULL)
		{
			printf("Failed to create window: %s", SDL_GetError());
			return 0;
		}
		else
		{
			// Create _mainRenderer for texture based rendering
			_mainRenderer = SDL_CreateRenderer(_mainWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (_mainRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				return 0;
			}
			else
			{
				SDL_SetRenderDrawColor(_mainRenderer, 0xFF, 0xFF, 0xFF, 0x00);
                
                _mainPixelFormat = SDL_AllocFormat(SDL_GetWindowPixelFormat(_mainWindow));
			}
		}
	}
	return 1;
}

int sdl_close()
{
	SDL_DestroyRenderer(_mainRenderer);
	_mainRenderer = NULL;
	SDL_DestroyWindow(_mainWindow);
	_mainWindow = NULL;
	// Quit SDL subsystems
	SDL_Quit();

	return 1;
}

SDL_Renderer* getMainRenderer()
{
	return _mainRenderer;
}

SDL_Surface* loadBitmapSurfaceFromPath(char path[])
{
	SDL_Surface* retSurface = NULL;
	SDL_Surface* loadedSurface = SDL_LoadBMP(path);

	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", path, SDL_GetError());
	}
	else
	{
		retSurface = SDL_ConvertSurface(loadedSurface, _mainPixelFormat, 0);
		if (retSurface == NULL)
		{
			printf("Unabled to optimize image %s! SDL Error: %s\n", path, SDL_GetError());
		}
		// Get rid of original surface
		SDL_FreeSurface(loadedSurface);
	}
	return retSurface;
}

SDL_Texture* loadTextureFromPath(char path[])
{
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = loadBitmapSurfaceFromPath(path);
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", path, SDL_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(_mainRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}
