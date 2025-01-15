//
// Created by hugog on 03/01/2025.
//

#include "game.h"

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>

#define NUM_BRICKS 50
#define BRICKS_PER_ROW 10
#define NUM_ROWS 5

void displayGame(SDL_Renderer* renderer) {

    Uint32 lastTimer = SDL_GetTicks();

    SDL_Surface *background_menu = IMG_Load("resources/assets/img/background/background_menu.jpg");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, background_menu);
    SDL_FreeSurface(background_menu);

    SDL_Surface* paddleSurface = IMG_Load("resources/assets/img/icons/paddle.png");
    SDL_Texture* paddleTexture = SDL_CreateTextureFromSurface(renderer, paddleSurface);
    SDL_FreeSurface(paddleSurface);

    SDL_Surface* ballSurface = IMG_Load("resources/assets/img/icons/ball.png");
    SDL_Texture* ballTexture = SDL_CreateTextureFromSurface(renderer, ballSurface);
    SDL_FreeSurface(ballSurface);

    TTF_Font* font = TTF_OpenFont("resources/assets/fonts/winter_minie.ttf", 100);

    SDL_Color textColor = {
        255,
        255,
        255,
        255}
    ;

    SDL_Surface* startSurface = TTF_RenderText_Blended(font, "Click to start", textColor);
    SDL_Texture* startTexture = SDL_CreateTextureFromSurface(renderer, startSurface);
    SDL_FreeSurface(startSurface);

    SDL_Rect startRect = {
        .x = 300,
        .y = 400,
        .w = startSurface->w,
        .h = startSurface->h
    };

    SDL_Rect continueButton = {
        540,
        300,
        200,
        50
    };

    SDL_Rect quitButton = {
        540,
        400,
        200,
        50
    };

    TTF_Font* buttonFont = TTF_OpenFont("resources/assets/fonts/camcode.ttf", 30);

    SDL_Color titleTextColor = {255, 255, 255, 255};
    SDL_Color buttonTextColor = {178, 186, 187, 255};

    SDL_Surface* pauseTextSurface = TTF_RenderText_Blended(buttonFont, "Pause Game", titleTextColor);
    SDL_Texture* pauseTextTexture = SDL_CreateTextureFromSurface(renderer, pauseTextSurface);
    SDL_FreeSurface(pauseTextSurface);

    SDL_Rect pauseTextRect = {
        550,
        230,
        pauseTextSurface->w,
        pauseTextSurface->h
    };

    SDL_Surface* continueTextSurface = TTF_RenderText_Blended(buttonFont, "Continue", buttonTextColor);
    SDL_Texture* continueTextTexture = SDL_CreateTextureFromSurface(renderer, continueTextSurface);
    SDL_FreeSurface(continueTextSurface);

    SDL_Rect continueTextRect = {
        575,
        310,
        continueTextSurface->w,
        continueTextSurface->h
    };

    SDL_Surface* quitTextSurface = TTF_RenderText_Blended(buttonFont, "Quit", buttonTextColor);
    SDL_Texture* quitTextTexture = SDL_CreateTextureFromSurface(renderer, quitTextSurface);
    SDL_FreeSurface(quitTextSurface);

    SDL_Rect quitTextRect = {
        610,
        410,
        quitTextSurface->w,
        quitTextSurface->h
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

        brickTextures[i] = SDL_CreateTextureFromSurface(renderer, brickSurfaces[i]);
        SDL_FreeSurface(brickSurfaces[i]);

    }

    struct paddle paddle = {
        (1280 - 200) / 2,
        620,
        30,
        200,
        2,
        false,
        paddleTexture
    };

    SDL_Rect paddleRect = {
        paddle.x,
        paddle.y,
        paddle.w,
        paddle.h
    };

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

    SDL_Rect ballRect = {
        ball.x,
        ball.y,
        ball.w,
        ball.h
    };

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

            } else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {

                if (showPopup) {

                    SDL_Point mousePoint = { event.button.x, event.button.y };

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

        if (gameStarted && !showPopup) {

            if (moveLeft && paddle.x > 0) {
                paddle.x -= paddle.speed;
            }

            if (moveRight && paddle.x + paddle.w < 1280) {
                paddle.x += paddle.speed;
            }

            paddleRect.x = paddle.x;

            if (SDL_GetTicks() - lastTimer > 16) {
                ball.x += ball.speedX;
                ball.y += ball.speedY;
                lastTimer = SDL_GetTicks();
            }

            if (ball.x + ball.w + ball.speedX > 1280 || ball.x + ball.speedX < 0) {
                ball.speedX = -ball.speedX;
            }

            if (ball.y + ball.h + ball.speedY > 720 || ball.y + ball.speedY < 0) {
                ball.speedY = -ball.speedY;
            }

            ballRect.x = ball.x;
            ballRect.y = ball.y;
        }

        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, texture, NULL, NULL);

        if (!gameStarted) {
            SDL_RenderCopy(renderer, startTexture, NULL, &startRect);
        }

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
            SDL_RenderFillRect(renderer, &continueButton);
            SDL_RenderFillRect(renderer, &quitButton);

            SDL_RenderCopy(renderer, pauseTextTexture, NULL, &pauseTextRect);
            SDL_RenderCopy(renderer, continueTextTexture, NULL, &continueTextRect);
            SDL_RenderCopy(renderer, quitTextTexture, NULL, &quitTextRect);

        }

        SDL_RenderPresent(renderer);
    }
}

