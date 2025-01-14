//
// Created by hugog on 03/01/2025.
//

#include "game.h"
#include "data.h"

#include <SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

#define NUM_BRICKS 50
#define BRICKS_PER_ROW 10
#define NUM_ROWS 5

int displayGame(SDL_Renderer* renderer) {

    int lastTimer = SDL_GetTicks();

    SDL_Surface *background_menu = IMG_Load("resources/assets/img/background/background_menu.jpg");

    if (!background_menu) {
        printf("Failed to load background image: %s\n", IMG_GetError());
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, background_menu);
    SDL_FreeSurface(background_menu);

    if (!texture) {
        printf("Failed to create texture from surface: %s\n", SDL_GetError());
    }

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

    SDL_Surface* barSurface = IMG_Load("resources/assets/img/background/vertical_bar.png");

    if (!barSurface) {
        printf("Failed to load barSurface: %s\n", IMG_GetError());
        return -1;
    }

    SDL_Texture* barTexture = SDL_CreateTextureFromSurface(renderer, barSurface);
    SDL_FreeSurface(barSurface);

    if (!barTexture) {
        printf("Failed to create bar texture: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Rect leftBarRect = {
        20,
        4,
        16,
        718
    };

    SDL_Rect rightBarRect = {
        1280 - 20 - 16,
        4,
        16,
        718
    };

    SDL_Surface* horizontalBarSurface = IMG_Load("resources/assets/img/background/horizontal_bar.png");

    if (!horizontalBarSurface) {
        printf("Failed to load horizontalBarSurface: %s\n", IMG_GetError());
        return -1;
    }

    SDL_Texture* horizontalBarTexture = SDL_CreateTextureFromSurface(renderer, horizontalBarSurface);
    SDL_FreeSurface(horizontalBarSurface);

    if (!horizontalBarTexture) {
        printf("Failed to create horizontal bar texture: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Rect horizontalBarRect = {
        35,
        2,
        1210,
        16
    };

    SDL_Surface* brickSurfaces[NUM_ROWS] = {
        IMG_Load("resources/assets/img/icons/green_brick.png"),
        IMG_Load("resources/assets/img/icons/blue_brick.png"),
        IMG_Load("resources/assets/img/icons/pink_brick.png"),
        IMG_Load("resources/assets/img/icons/orange_brick.png"),
        IMG_Load("resources/assets/img/icons/grey_brick.png")
    };

    SDL_Texture* brickTextures[NUM_ROWS];
    for (int i = 0; i < NUM_ROWS; i++) {
        if (!brickSurfaces[i]) {
            printf("Failed to load brick surface: %s\n", IMG_GetError());
            return -1;
        }
        brickTextures[i] = SDL_CreateTextureFromSurface(renderer, brickSurfaces[i]);
        SDL_FreeSurface(brickSurfaces[i]);
        if (!brickTextures[i]) {
            printf("Failed to create brick texture: %s\n", SDL_GetError());
            return -1;
        }
    }

    struct paddle paddle = {
        (1280 - 200) / 2,
        620,
        30,
        200,
        1,
        false,
        paddleTexture
    };

    SDL_Rect paddleRect = {paddle.x, paddle.y, paddle.w, paddle.h};

    struct ball ball = {
        paddle.x + paddle.w / 2 - 25 / 2,
        paddle.y - 35,
        25,
        25,
        7,
        7,
        1,
        ballTexture
    };

    SDL_Rect ballRect = {ball.x, ball.y, ball.w, ball.h};

    struct brick bricks[NUM_BRICKS];
    int brickWidth = 100;
    int brickHeight = 40;
    int startX = (1280 - (BRICKS_PER_ROW * brickWidth)) / 2;
    int startY = 50;

    for (int i = 0; i < NUM_BRICKS; i++) {
        bricks[i].x = startX + (i % BRICKS_PER_ROW) * brickWidth;
        bricks[i].y = startY + (i / BRICKS_PER_ROW) * brickHeight;
        bricks[i].w = brickWidth;
        bricks[i].h = brickHeight;
        bricks[i].life = 1;
        bricks[i].texture = brickTextures[i / BRICKS_PER_ROW];
    }

    bool gameStarted = false;
    bool showPopup = false;

    bool moveLeft = false;
    bool moveRight = false;

    SDL_bool quit = SDL_FALSE;

    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = SDL_TRUE;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_q) {
                    moveLeft = true;
                } else if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d) {
                    moveRight = true;
                } else if (event.key.keysym.sym == SDLK_ESCAPE) {
                    showPopup = true;
                }
            } else if (event.type == SDL_KEYUP) {
                if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_q) {
                    moveLeft = false;
                } else if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d) {
                    moveRight = false;
                }
            } else if (event.type == SDL_MOUSEMOTION) {
                paddle.x = event.motion.x - paddle.w / 2;
            } else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                if (showPopup) {
                    SDL_Point mousePoint = { event.button.x, event.button.y };
                    SDL_Rect continueButton = {540, 300, 200, 50};
                    SDL_Rect quitButton = {540, 400, 200, 50};

                    if (SDL_PointInRect(&mousePoint, &continueButton)) {
                        showPopup = false;
                    } else if (SDL_PointInRect(&mousePoint, &quitButton)) {
                        quit = SDL_TRUE;
                    }
                } else {
                    gameStarted = true;
                }
            }
        }

        if (!showPopup) {
            if (moveLeft) {
                paddle.x -= paddle.speed;
            }
            if (moveRight) {
                paddle.x += paddle.speed;
            }
        }

        if (!showPopup) {
            paddleRect.x = paddle.x;
        }

        int leftBarLimit = leftBarRect.x + leftBarRect.w;
        int rightBarLimit = rightBarRect.x - paddle.w;

        if (paddle.x < leftBarLimit) {
            paddle.x = leftBarLimit;
        } else if (paddle.x > rightBarLimit) {
            paddle.x = rightBarLimit;
        }

        if (gameStarted && !showPopup) {
            if (SDL_GetTicks() - lastTimer > 16) {
                ball.x += ball.speedX;
                ball.y += ball.speedY;
                lastTimer = SDL_GetTicks();
            }

            if (ball.x <= leftBarRect.x + leftBarRect.w || ball.x + ball.w >= rightBarRect.x) {
                ball.speedX = -ball.speedX;
            }

            if (ball.y <= horizontalBarRect.y + horizontalBarRect.h) {
                ball.speedY = -ball.speedY;
            }

            if (SDL_HasIntersection(&ballRect, &paddleRect)) {
                ball.speedY = -ball.speedY;
                ball.y = paddle.y - ball.h;
            }

            if (ball.y + ball.h >= 720) {
                gameStarted = false;
                ball.x = paddle.x + paddle.w / 2 - ball.w / 2;
                ball.y = paddle.y - ball.h;
                ball.speedX = 3;
                ball.speedY = -3;
            }

            for (int i = 0; i < NUM_BRICKS; i++) {
                if (bricks[i].life > 0) {
                    SDL_Rect brickRect = {bricks[i].x, bricks[i].y, bricks[i].w, bricks[i].h};
                    if (SDL_HasIntersection(&ballRect, &brickRect)) {
                        bricks[i].life = 0;
                        ball.speedY = -ball.speedY;
                    }
                }
            }
        }

        ballRect.x = ball.x;
        ballRect.y = ball.y;

        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, texture, NULL, NULL);

        SDL_RenderCopy(renderer, barTexture, NULL, &leftBarRect);
        SDL_RenderCopy(renderer, barTexture, NULL, &rightBarRect);
        SDL_RenderCopy(renderer, horizontalBarTexture, NULL, &horizontalBarRect);

        SDL_RenderCopy(renderer, paddle.texture, NULL, &paddleRect);
        SDL_RenderCopy(renderer, ball.texture, NULL, &ballRect);

        for (int i = 0; i < NUM_BRICKS; i++) {
            SDL_Rect brickRect = {bricks[i].x, bricks[i].y, bricks[i].w, bricks[i].h};
            SDL_RenderCopy(renderer, bricks[i].texture, NULL, &brickRect);
        }

        if (showPopup) {

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
            SDL_Rect popupRect = {440, 200, 400, 300};
            SDL_RenderFillRect(renderer, &popupRect);

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_Rect continueButton = {540, 300, 200, 50};
            SDL_Rect quitButton = {540, 400, 200, 50};
            SDL_RenderFillRect(renderer, &continueButton);
            SDL_RenderFillRect(renderer, &quitButton);
        }

        SDL_RenderPresent(renderer);
    }
}