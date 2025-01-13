//
// Created by hugog on 03/01/2025.
//

#include "game.h"

#include <SDL_image.h>
#include <stdio.h>


int displayGame(SDL_Renderer* renderer) {

    SDL_Surface* paddleSurface = IMG_Load("resources/assets/img/icons/paddle.png");

    if (!paddleSurface) {
        printf("Failed to load paddleSurface: %s\n", IMG_GetError());
        return -1;
    }

    SDL_Texture* paddleTexture = SDL_CreateTextureFromSurface(renderer, paddleSurface);
    SDL_FreeSurface(paddleSurface);

    if (!paddleTexture) {
        printf("Failed to create paddle texture: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Surface* ballSurface = IMG_Load("resources/assets/img/icons/ball.png");

    if (!ballSurface) {
        printf("Failed to load ballSurface: %s\n", IMG_GetError());
        return -1;
    }

    SDL_Texture* ballTexture = SDL_CreateTextureFromSurface(renderer, ballSurface);
    SDL_FreeSurface(ballSurface);

    if (!ballTexture) {
        printf("Failed to create ball texture: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Rect paddleRect = { 400, 550, 100, 20 };
    SDL_Rect ballRect = { 450, 530, 20, 20 };
    int ballSpeedX = 5, ballSpeedY = -5;

    SDL_bool quit = SDL_FALSE;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = SDL_TRUE;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_LEFT) {
                    paddleRect.x -= 10;
                } else if (event.key.keysym.sym == SDLK_RIGHT) {
                    paddleRect.x += 10;
                }
            }
        }

        ballRect.x += ballSpeedX;
        ballRect.y += ballSpeedY;

        if (ballRect.x <= 0 || ballRect.x + ballRect.w >= 800) {
            ballSpeedX = -ballSpeedX;
        }
        if (ballRect.y <= 0) {
            ballSpeedY = -ballSpeedY;
        }

        if (SDL_HasIntersection(&ballRect, &paddleRect)) {
            ballSpeedY = -ballSpeedY;
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, paddleTexture, NULL, &paddleRect);
        SDL_RenderCopy(renderer, ballTexture, NULL, &ballRect);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(paddleTexture);
    SDL_DestroyTexture(ballTexture);

    return 0;
}