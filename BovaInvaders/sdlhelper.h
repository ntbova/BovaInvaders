#ifndef SDLHELPER_H
#define SDLHELPER_H
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int sdl_init(void);
int sdl_close(void);
SDL_Renderer* getMainRenderer(void);
SDL_Surface* loadBitmapSurfaceFromPath(char path[]);
SDL_Texture* loadTextureFromPath(char path[]);
#endif
