//
// Created by hugog on 03/01/2025.
//

#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <stdbool.h>

struct paddle {
    int x;
    int y;
    int h;
    int w;
    int speed;
    SDL_Texture* texture;
};

struct brick {
    SDL_Rect rect;
    int lives;
    SDL_Texture* texture;
    Uint32 last_hit_time;
};

struct projectile {
    SDL_Rect rect;
    int speed;
    bool active;
};

void displayGame(SDL_Renderer* renderer);

#endif //GAME_H
