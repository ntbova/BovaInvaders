#ifndef SDLHELPER_H
#define SDLHELPER_H
#include <SDL2/SDL.h>
#include <stdio.h>

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 647

int sdl_init();
int sdl_close();
SDL_Renderer* getMainRenderer();
SDL_Surface* loadBitmapSurfaceFromPath(char path[]);
SDL_Texture* loadTextureFromPath(char path[]);
#endif
