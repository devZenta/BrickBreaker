//
// Created by hugog on 03/01/2025.
//

#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <windows.h>

struct paddle {
    int x;
    int y;
    int h;
    int w;
    int speed;
    boolean invisible;
    SDL_Texture* texture;
};

struct ball {
    int x;
    int y;
    int h;
    int w;
    int speedX;
    int speedY;
    int damage;
    SDL_Texture* texture;
};

struct brick {
    int x;
    int y;
    int h;
    int w;
    int life;
    SDL_Texture* texture;
};

int displayGame(SDL_Renderer* renderer);

#endif //GAME_H
