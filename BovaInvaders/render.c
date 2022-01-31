//
//  render.c
//  BovaInvaders
//
//  Created by Nick Bova on 1/30/22.
//

#include "render.h"
#include "sdlhelper.h"

int render_init() {
    if (sdl_init == 0) {
        return 0;
    }
    
    return 1;
}

void render_loop() {
    
}
