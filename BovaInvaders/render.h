//
//  render.h
//  BovaInvaders
//
//  Created by Nick Bova on 2/5/22.
//

#ifndef render_h
#define render_h

#include "sdlhelper.h"
#include "game.h"

typedef struct RenderAssetsStruct {
    SDL_Texture* shipTexture;
    SDL_Texture* bulletTexture;
    SDL_Texture* enemyTexture;
    SDL_Rect shipRect;
    SDL_Rect bulletRects[NUM_BULLETS];
    SDL_Rect enemyRects[NUM_ENEMIES];
} RenderAssets;

int render_init(RenderAssets*, GameState*);
void render_game_state(RenderAssets*);
#endif /* render_h */
