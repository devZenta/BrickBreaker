//
// Created by hugog on 03/01/2025.
//

#include "game.h"
#include "data.h"
#include "menu.h"

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>

#define NUM_BRICKS 55
#define BRICKS_PER_ROW 11
#define NUM_ROWS 5

void displayGame(SDL_Renderer* renderer) {

    Uint32 lastTimer = SDL_GetTicks();

    int selectedDifficulty, volume;

    int brickLife;
    int life;
    int ballSpeed;
    int paddleSpeed;
    bool invisiblePaddle;

    load_settings(&selectedDifficulty, &volume);

    if (selectedDifficulty == 1) {

        brickLife = 1;
        life = 3;
        ballSpeed = 7;
        paddleSpeed = 2;
        invisiblePaddle = false;

    } else if (selectedDifficulty == 2) {

        brickLife = 2;
        life = 2;
        ballSpeed = 9;
        paddleSpeed = 2;
        invisiblePaddle = false;

    } else if (selectedDifficulty == 3) {

        brickLife = 3;
        life = 1;
        ballSpeed = 11;
        paddleSpeed = 3;
        invisiblePaddle = true;

    }

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

    SDL_Rect restartButton = {
        540,
        370,
        200,
        50
    };

    SDL_Rect menuButton = {
        540,
        440,
        200,
        50
    };

    SDL_Rect quitButton = {
        540,
        510,
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
        520,
        quitTextSurface->w,
        quitTextSurface->h
    };

    SDL_Surface* restartTextSurface = TTF_RenderText_Blended(buttonFont, "Restart", buttonTextColor);
    SDL_Texture* restartTextTexture = SDL_CreateTextureFromSurface(renderer, restartTextSurface);
    SDL_FreeSurface(restartTextSurface);

    SDL_Rect restartTextRect = {
        585,
        380,
        restartTextSurface->w,
        restartTextSurface->h
    };

    SDL_Surface* menuTextSurface = TTF_RenderText_Blended(buttonFont, "Menu", buttonTextColor);
    SDL_Texture* menuTextTexture = SDL_CreateTextureFromSurface(renderer, menuTextSurface);
    SDL_FreeSurface(menuTextSurface);

    SDL_Rect menuTextRect = {
        595,
        450,
        menuTextSurface->w,
        menuTextSurface->h
    };

    SDL_Surface* easyEmoticonSurface = IMG_Load("resources/assets/img/levels/simple_level.png");
    SDL_Texture* easyEmoticonTexture = SDL_CreateTextureFromSurface(renderer, easyEmoticonSurface);
    SDL_FreeSurface(easyEmoticonSurface);

    SDL_Surface* mediumEmoticonSurface = IMG_Load("resources/assets/img/levels/medium_level.png");
    SDL_Texture* mediumEmoticonTexture = SDL_CreateTextureFromSurface(renderer, mediumEmoticonSurface);
    SDL_FreeSurface(mediumEmoticonSurface);

    SDL_Surface* hardEmoticonSurface = IMG_Load("resources/assets/img/levels/hard_level.png");
    SDL_Texture* hardEmoticonTexture = SDL_CreateTextureFromSurface(renderer, hardEmoticonSurface);
    SDL_FreeSurface(hardEmoticonSurface);

    SDL_Texture* selectedEmoticonTexture = NULL;

    if (selectedDifficulty == 1) {

        selectedEmoticonTexture = easyEmoticonTexture;

    } else if (selectedDifficulty == 2) {

        selectedEmoticonTexture = mediumEmoticonTexture;

    } else if (selectedDifficulty == 3) {

        selectedEmoticonTexture = hardEmoticonTexture;

    }

    SDL_Rect emoticonRect = {
        .x = 1280 - 64 - 20,
        .y = 720 - 64 - 20,
        .w = 64,
        .h = 64
    };

    SDL_Surface* lifeIconSurface = IMG_Load("resources/assets/img/icons/life.png");
    SDL_Texture* lifeIconTexture = SDL_CreateTextureFromSurface(renderer, lifeIconSurface);
    SDL_FreeSurface(lifeIconSurface);

    SDL_Rect life1IconRect = {
        .x = 20,
        .y = emoticonRect.y,
        .w = 64,
        .h = 64
    };

    SDL_Rect life2IconRect = {
        .x = 40,
        .y = emoticonRect.y,
        .w = 64,
        .h = 64
    };

    SDL_Rect life3IconRect = {
        .x = 60,
        .y = emoticonRect.y,
        .w = 64,
        .h = 64
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
        paddleSpeed,
        invisiblePaddle,
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
        0,
        -ballSpeed,
        1,
        ballTexture
    };

    SDL_Rect ballRect = {
        ball.x,
        ball.y,
        ball.w,
        ball.h
    };

    int initialPaddleX = (1280 - 200) / 2;
    int initialPaddleY = 620;
    int initialBallX = initialPaddleX + 200 / 2 - 25 / 2;
    int initialBallY = initialPaddleY - 35;

    struct brick bricks[NUM_BRICKS];

    int brickWidth = 100;
    int brickHeight = 45;
    int startX = (1280 - (BRICKS_PER_ROW * brickWidth)) / 2;
    int startY = 25;

    for (int i = 0; i < NUM_BRICKS; i++) {
        bricks[i].x = startX + (i % BRICKS_PER_ROW) * brickWidth;
        bricks[i].y = startY + (i / BRICKS_PER_ROW) * brickHeight;
        bricks[i].w = brickWidth;
        bricks[i].h = brickHeight;
        bricks[i].life = brickLife;
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

                    } else if (SDL_PointInRect(&mousePoint, &menuButton)) {

                        displayMenu(renderer);
                        quit = SDL_TRUE;

                    } else if (SDL_PointInRect(&mousePoint, &restartButton)) {

                        displayGame(renderer);
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

            if (ball.y + ball.h + ball.speedY < 0) {
                ball.speedY = -ball.speedY;
            }

            if (SDL_HasIntersection(&ballRect, &paddleRect)) {
                ball.speedY = -ball.speedY;
                ball.y = paddle.y - ball.h;
            }

            for (int i = 0; i < NUM_BRICKS; i++) {
                SDL_Rect brickRect = {bricks[i].x, bricks[i].y, bricks[i].w, bricks[i].h};
                if (bricks[i].life > 0 && SDL_HasIntersection(&ballRect, &brickRect)) {
                    bricks[i].life--;
                    ball.speedY = -ball.speedY;
                    break;
                }
            }

            if (ball.y + ball.h > 720) {
                paddle.x = initialPaddleX;
                paddle.y = initialPaddleY;
                ball.x = initialBallX;
                ball.y = initialBallY;
                ball.speedX = 0;
                ball.speedY = -ballSpeed;
                gameStarted = false;
                if (life > 0) {
                    life--;
                }
            }

            if (life == 0) {
                displayMenu(renderer);
                quit = SDL_TRUE;
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
            if (bricks[i].life > 0) {
                SDL_Rect brickRect = {bricks[i].x, bricks[i].y, bricks[i].w, bricks[i].h};
                SDL_RenderCopy(renderer, bricks[i].texture, NULL, &brickRect);
            }
        }

        SDL_RenderCopy(renderer, selectedEmoticonTexture, NULL, &emoticonRect);

        if (life >= 1) {
            SDL_RenderCopy(renderer, lifeIconTexture, NULL, &life1IconRect);
        }
        if (life >= 2) {
            SDL_RenderCopy(renderer, lifeIconTexture, NULL, &life2IconRect);
        }
        if (life >= 3) {
            SDL_RenderCopy(renderer, lifeIconTexture, NULL, &life3IconRect);
        }

        if (showPopup) {

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
            SDL_Rect popupRect = {440, 200, 400, 400};
            SDL_RenderFillRect(renderer, &popupRect);

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &continueButton);
            SDL_RenderFillRect(renderer, &restartButton);
            SDL_RenderFillRect(renderer, &menuButton);
            SDL_RenderFillRect(renderer, &quitButton);

            SDL_RenderCopy(renderer, pauseTextTexture, NULL, &pauseTextRect);
            SDL_RenderCopy(renderer, continueTextTexture, NULL, &continueTextRect);
            SDL_RenderCopy(renderer, restartTextTexture, NULL, &restartTextRect);
            SDL_RenderCopy(renderer, menuTextTexture, NULL, &menuTextRect);
            SDL_RenderCopy(renderer, quitTextTexture, NULL, &quitTextRect);

        }

        SDL_RenderPresent(renderer);
    }
}

