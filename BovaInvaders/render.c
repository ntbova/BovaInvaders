//
//  render.c
//  BovaInvaders
//
//  Created by Nick Bova on 2/5/22.
//

#include "render.h"

int render_init(RenderAssets* assets, GameState* state) {
    if (sdl_init() == 0) {
        return 0;
    }
    
    assets->shipTexture = loadTextureFromPath("Resources/space_ship.bmp");
    assets->bulletTexture = loadTextureFromPath("Resources/ship_bullet.bmp");
    assets->enemyTexture = loadTextureFromPath("Resources/enemy.bmp");
    
    assets->shipRect.h = SPACE_SHIP_HEIGHT; assets->shipRect.w = SPACE_SHIP_WIDTH;
    assets->shipRect.x = state->ship_pos_x; assets->shipRect.y = state->ship_pos_y;
    // Allow up to X num bullets on screen (Will change this at some point to have an array of
    // arbitrary bullets on screen so that I change the amount as a settings whenever I want
    for (int i = 0; i < NUM_BULLETS; i++) {
        assets->bulletRects[i].h = BULLET_HEIGHT; assets->bulletRects[i].w = BULLET_WIDTH;
        assets->bulletRects[i].x = state->bullet_pos_x[i]; assets->bulletRects[i].y = state->bullet_pos_y[i];
    }
    for (int i = 0; i < NUM_ENEMIES; i++) {
        assets->enemyRects[i].h = ENEMY_HEIGHT; assets->enemyRects[i].w = ENEMY_WIDTH;
        assets->enemyRects[i].x = state->enemy_pos_x[i]; assets->enemyRects[i].y = state->enemy_pos_y[i];
    }
    
    return 1;
}

int check_collision(SDL_Rect a, SDL_Rect b) {
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;
    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return 0;
    }

    if( topA >= bottomB )
    {
        return 0;
    }

    if( rightA <= leftB )
    {
        return 0;
    }

    if( leftA >= rightB )
    {
        return 0;
    }

    //If none of the sides from A are outside B
    return 1;
}

void render_game_state(RenderAssets* assets) {
    SDL_Renderer* mainRenderer = getMainRenderer();
    // Clear screen
    SDL_RenderClear(mainRenderer);

    // Render ship to the screen
    SDL_RenderCopy(mainRenderer, assets->shipTexture, NULL, &assets->shipRect);
    
    // Render any bullets on screen
    for (int i = 0; i < NUM_BULLETS; i++) {
        SDL_RenderCopy(mainRenderer, assets->bulletTexture, NULL, &assets->bulletRects[i]);
    }

    // Render all enemies on screen
    for (int i = 0; i < NUM_ENEMIES; i++) {
        SDL_RenderCopy(mainRenderer, assets->enemyTexture, NULL, &assets->enemyRects[i]);
    }
    
    // Update screen
    SDL_RenderPresent(mainRenderer);
}
