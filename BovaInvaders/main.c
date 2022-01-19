//
//  main.c
//  BovaInvaders
//
//  Created by Nick Bova on 1/18/22.
//

#include <stdio.h>
#include "game.h"

int main(int argc, const char * argv[]) {
    
    if (game_init()) {
        game_loop();
    }
    
    return game_close();
}
