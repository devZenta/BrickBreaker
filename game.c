//
// Created by hugog on 03/01/2025.
//

#include "game.h"
#include "data.h"
#include "menu.h"
#include "utils.h"

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define BRICK_WIDTH 100
#define BRICK_HEIGHT 40

#define BALL_SIZE 12

#define PADDLE_HEIGHT 30
#define PADDLE_WIDTH 150

#define ROWS 5
#define COLS 11

#define MAX_PROJECTILES 10

struct projectile projectiles[MAX_PROJECTILES];


void displayGame(SDL_Renderer* renderer) {

    srand(time(NULL));

    Uint32 lastTimer = SDL_GetTicks();

    int selectedDifficulty, volume;

    int brickLife;
    int life;
    int ballSpeed;
    int paddleSpeed;

    bool isProtected = false;
    bool canShoot = false;

    bool projectileUsed = false;

    int currentProjectile = 0;

    float score = 0.0f;
    int bricksRemaining = ROWS * COLS;
    int destroyedBricks = 0;
    const float scorePerBrick = 100.0f / (ROWS * COLS);

    bool playerWon = false;
    bool playerLost = false;

    load_settings(&selectedDifficulty, &volume);

    if (selectedDifficulty == 1) {

        brickLife = 1;
        life = 3;
        ballSpeed = 4;
        paddleSpeed = 10;

    } else if (selectedDifficulty == 2) {

        brickLife = 2;
        life = 2;
        ballSpeed = 6;
        paddleSpeed = 30;

    } else if (selectedDifficulty == 3) {

        brickLife = 3;
        life = 1;
        ballSpeed = 8;
        paddleSpeed = 50;

    }

    SDL_Surface *background_menu = IMG_Load("resources/assets/img/background/background_menu.jpg");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, background_menu);
    SDL_FreeSurface(background_menu);

    SDL_Surface* paddleSurface = IMG_Load("resources/assets/img/icons/paddle.png");
    SDL_Texture* paddleTexture = SDL_CreateTextureFromSurface(renderer, paddleSurface);
    SDL_FreeSurface(paddleSurface);

    struct paddle paddle = {
        (1280 - 150) / 2,
        600,
        PADDLE_HEIGHT,
        PADDLE_WIDTH,
        paddleSpeed,
        paddleTexture
    };

    SDL_Rect paddleRect = {
        paddle.x,
        paddle.y,
        paddle.w,
        paddle.h
    };

    SDL_Rect ball = {
        SCREEN_WIDTH / 2,
        SCREEN_HEIGHT / 2,
        BALL_SIZE,
        BALL_SIZE
    };

    int ball_directionX = (rand() % 2 == 0 ? -ballSpeed : ballSpeed);
    int ball_directionY = -ballSpeed;

    int initialPaddleX = (1280 - 150) / 2;

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

    SDL_Color titleTextColor = {
        255,
        255,
        255,
        255
    };

    SDL_Color buttonTextColor = {
        178,
        186,
        187,
        255
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

    SDL_Surface* shieldIconSurface = IMG_Load("resources/assets/img/icons/shield.png");
    SDL_Texture* shieldIconTexture = SDL_CreateTextureFromSurface(renderer, shieldIconSurface);
    SDL_FreeSurface(shieldIconSurface);

    SDL_Rect shieldIconRect = {
        .x = 145,
        .y = emoticonRect.y - 5,
        .w = 68,
        .h = 68
    };

    SDL_Surface* crosshairIconSurface = IMG_Load("resources/assets/img/icons/crosshair.png");
    SDL_Texture* crosshairIconTexture = SDL_CreateTextureFromSurface(renderer, crosshairIconSurface);
    SDL_FreeSurface(crosshairIconSurface);

    SDL_Rect crosshairIconRect = {
        .x = 230,
        .y = emoticonRect.y - 5,
        .w = 68,
        .h = 68
    };

    SDL_Surface* winIconSurface = IMG_Load("resources/assets/img/icons/win.png");
    SDL_Texture* winIconTexture = SDL_CreateTextureFromSurface(renderer, winIconSurface);
    SDL_FreeSurface(winIconSurface);

    SDL_Surface* loseIconSurface = IMG_Load("resources/assets/img/icons/game_over.png");
    SDL_Texture* loseIconTexture = SDL_CreateTextureFromSurface(renderer, loseIconSurface);
    SDL_FreeSurface(loseIconSurface);

    SDL_Surface* brickSurfaces[ROWS] = {
        IMG_Load("resources/assets/img/icons/green_brick.png"),
        IMG_Load("resources/assets/img/icons/blue_brick.png"),
        IMG_Load("resources/assets/img/icons/pink_brick.png"),
        IMG_Load("resources/assets/img/icons/orange_brick.png"),
        IMG_Load("resources/assets/img/icons/grey_brick.png")
    };

    SDL_Texture* brickTextures[ROWS];

    for (int i = 0; i < ROWS; i++) {

        brickTextures[i] = SDL_CreateTextureFromSurface(renderer, brickSurfaces[i]);
        SDL_FreeSurface(brickSurfaces[i]);

    }

    struct brick bricks[ROWS][COLS];

    for (int row = 0; row < ROWS; row++) {

        for (int col = 0; col < COLS; col++) {

            bricks[row][col].rect.x = col * (BRICK_WIDTH + 10) + 50;
            bricks[row][col].rect.y = row * (BRICK_HEIGHT + 10) + 30;
            bricks[row][col].rect.w = BRICK_WIDTH;
            bricks[row][col].rect.h = BRICK_HEIGHT;
            bricks[row][col].lives = brickLife;
            bricks[row][col].texture = brickTextures[row];
            bricks[row][col].last_hit_time = 0;

        }
    }

    for (int i = 0; i < MAX_PROJECTILES; i++) {
        projectiles[i].rect.w = 10;
        projectiles[i].rect.h = 20;
        projectiles[i].rect.x = 0;
        projectiles[i].rect.y = 0;
        projectiles[i].speed = -8;
        projectiles[i].active = false;
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

                showPopup = true;

            } else if (event.type == SDL_KEYDOWN) {

                if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_q) {

                    moveLeft = true;

                } else if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d) {

                    moveRight = true;

                } else if (event.key.keysym.sym == SDLK_SPACE && canShoot && !projectileUsed) {

                    for (int i = 0; i < MAX_PROJECTILES; i++) {

                        if (!projectiles[i].active) {

                            projectiles[i].rect.x = paddle.x + paddle.w / 2 - projectiles[i].rect.w / 2;
                            projectiles[i].rect.y = paddle.y - projectiles[i].rect.h;
                            projectiles[i].active = true;
                            currentProjectile++;
                            break;

                        }
                    }

                    if (currentProjectile == MAX_PROJECTILES) {

                        canShoot = false;
                        projectileUsed = true;

                    }

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

            if (moveLeft) {

                paddle.x -= paddle.speed;

                if (paddle.x < 0) {
                    paddle.x = 0;
                }
            }

            if (moveRight) {

                paddle.x += paddle.speed;

                if (paddle.x + PADDLE_WIDTH > SCREEN_WIDTH) {
                    paddle.x = SCREEN_WIDTH - PADDLE_WIDTH;
                }
            }

            paddleRect.x = paddle.x;

            if (SDL_GetTicks() - lastTimer > 1) {

                ball.x += ball_directionX;
                ball.y += ball_directionY;
                lastTimer = SDL_GetTicks();
            }

            if (ball.x <= 0 || ball.x + BALL_SIZE >= SCREEN_WIDTH) {

                ball_directionX = -ball_directionX;

            }

            if (ball.y <= 0) {

                ball_directionY = -ball_directionY;

            }

            if (check_collision(&ball, &paddleRect)) {

                ball_directionY = -ball_directionY;

                int hit_pos = ball.x + BALL_SIZE / 2 - paddle.x;
                if (hit_pos < PADDLE_WIDTH / 3) {
                    ball_directionX = -abs(ball_directionX);
                } else if (hit_pos > 2 * PADDLE_WIDTH / 3) {
                    ball_directionX = abs(ball_directionX);
                }
            }

            Uint32 current_time = SDL_GetTicks();

            for (int row = 0; row < ROWS; row++) {

                for (int col = 0; col < COLS; col++) {

                    struct brick *brick = &bricks[row][col];

                    if (brick->lives > 0 && check_collision(&ball, &brick->rect)) {

                        if (current_time - brick->last_hit_time > 100) {

                            ball_directionY = -ball_directionY;
                            brick->lives--;
                            brick->last_hit_time = current_time;

                        }

                        if (brick->lives == 0) {

                            score += scorePerBrick;
                            bricksRemaining--;
                            destroyedBricks++;

                        }
                        break;
                    }
                }
            }

            for (int i = 0; i < MAX_PROJECTILES; i++) {

                if (projectiles[i].active) {

                    for (int row = 0; row < ROWS; row++) {

                        for (int col = 0; col < COLS; col++) {

                            struct brick* brick = &bricks[row][col];

                            if (brick->lives > 0 && check_collision(&projectiles[i].rect, &brick->rect)) {

                                brick->lives--;
                                projectiles[i].active = false;

                                if (brick->lives == 0) {

                                    score += scorePerBrick;
                                    bricksRemaining--;
                                    destroyedBricks++;

                                }
                                break;
                            }
                        }
                    }
                }
            }

            if (destroyedBricks >= 10) {

                isProtected = true;
            }

            if (destroyedBricks >= 20) {

                canShoot = true;

            }

            for (int i = 0; i < MAX_PROJECTILES; i++) {

                if (projectiles[i].active) {

                    projectiles[i].rect.y += projectiles[i].speed;

                    if (projectiles[i].rect.y < 0) {

                        projectiles[i].active = false;

                    }
                }
            }

            if (ball.y > SCREEN_HEIGHT) {

                paddle.x = initialPaddleX;
                ball.x = SCREEN_WIDTH / 2;
                ball.y = SCREEN_HEIGHT / 2;
                ball_directionX = (rand() % 2 == 0 ? -ballSpeed : ballSpeed);
                ball_directionY = -ballSpeed;
                gameStarted = false;

                if (life > 0) {

                    if (isProtected) {

                        isProtected = false;
                        destroyedBricks = 0;

                    } else {

                        life--;

                    }
                }
            }

            if (life == 0) {

                struct Game new_game;

                new_game.score = (int)score;
                new_game.difficulty = selectedDifficulty;

                get_current_datetime(new_game.date, DATE_LENGTH);

                add_game(new_game);

                playerLost = true;
                showPopup = true;

            }

            if (bricksRemaining == 0) {

                struct Game new_game;

                new_game.score = (int)score;
                new_game.difficulty = selectedDifficulty;

                get_current_datetime(new_game.date, DATE_LENGTH);

                add_game(new_game);

                playerWon = true;
                showPopup = true;

            }
        }

        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, texture, NULL, NULL);

        for (int row = 0; row < ROWS; row++) {

            for (int col = 0; col < COLS; col++) {

                if (bricks[row][col].lives > 0) {

                    SDL_RenderCopy(renderer, bricks[row][col].texture, NULL, &bricks[row][col].rect);

                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &ball);

        if (!gameStarted) {

            SDL_RenderCopy(renderer, startTexture, NULL, &startRect);

        }

        SDL_RenderCopy(renderer, paddle.texture, NULL, &paddleRect);

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

        if (isProtected) {

            SDL_RenderCopy(renderer, shieldIconTexture, NULL, &shieldIconRect);

        }

        if (canShoot && !projectileUsed) {

            SDL_RenderCopy(renderer, crosshairIconTexture, NULL, &crosshairIconRect);

        }

        for (int i = 0; i < MAX_PROJECTILES; i++) {

            if (projectiles[i].active) {

                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_RenderFillRect(renderer, &projectiles[i].rect);

            }
        }

        if (showPopup) {

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);

            SDL_Rect popupRect = {
                440,
                200,
                400,
                400
            };

            SDL_RenderFillRect(renderer, &popupRect);

            if (playerWon) {

                SDL_Rect winIconRect = {
                    595,
                    265,
                    86,
                    86
                };

                SDL_RenderCopy(renderer, winIconTexture, NULL, &winIconRect);

                SDL_Surface* winTextSurface = TTF_RenderText_Blended(buttonFont, "Well done you won", titleTextColor);
                SDL_Texture* winTextTexture = SDL_CreateTextureFromSurface(renderer, winTextSurface);
                SDL_FreeSurface(winTextSurface);

                SDL_Rect winTextRect = {
                    500,
                    215,
                    winTextSurface->w,
                    winTextSurface->h
                };

                SDL_RenderCopy(renderer, winTextTexture, NULL, &winTextRect);
                SDL_DestroyTexture(winTextTexture);

            } else if (playerLost) {

                SDL_Rect looseIconRect = {
                    590,
                    270,
                    86,
                    86
                };

                SDL_RenderCopy(renderer, loseIconTexture, NULL, &looseIconRect);

                char loseMessage[50];
                sprintf(loseMessage, "You lost your score %d", (int)score);
                SDL_Surface* loseTextSurface = TTF_RenderText_Blended(buttonFont, loseMessage, titleTextColor);
                SDL_Texture* loseTextTexture = SDL_CreateTextureFromSurface(renderer, loseTextSurface);
                SDL_FreeSurface(loseTextSurface);

                SDL_Rect loseTextRect = {
                    480,
                    215,
                    loseTextSurface->w,
                    loseTextSurface->h
                };

                SDL_RenderCopy(renderer, loseTextTexture, NULL, &loseTextRect);
                SDL_DestroyTexture(loseTextTexture);

            } else {

                char pauseMessage[50];
                sprintf(pauseMessage, "Pause your score %d", (int)score);
                SDL_Surface* pauseTextSurface = TTF_RenderText_Blended(buttonFont, pauseMessage, titleTextColor);
                SDL_Texture* pauseTextTexture = SDL_CreateTextureFromSurface(renderer, pauseTextSurface);
                SDL_FreeSurface(pauseTextSurface);

                SDL_Rect pauseTextRect = {
                    495,
                    230,
                    pauseTextSurface->w,
                    pauseTextSurface->h
                };

                SDL_RenderCopy(renderer, pauseTextTexture, NULL, &pauseTextRect);
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderFillRect(renderer, &continueButton);
                SDL_RenderCopy(renderer, continueTextTexture, NULL, &continueTextRect);

            }

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &restartButton);
            SDL_RenderFillRect(renderer, &menuButton);
            SDL_RenderFillRect(renderer, &quitButton);

            SDL_RenderCopy(renderer, restartTextTexture, NULL, &restartTextRect);
            SDL_RenderCopy(renderer, menuTextTexture, NULL, &menuTextRect);
            SDL_RenderCopy(renderer, quitTextTexture, NULL, &quitTextRect);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(paddle.texture);
    SDL_DestroyTexture(startTexture);
    SDL_DestroyTexture(continueTextTexture);
    SDL_DestroyTexture(quitTextTexture);
    SDL_DestroyTexture(restartTextTexture);
    SDL_DestroyTexture(menuTextTexture);
    SDL_DestroyTexture(easyEmoticonTexture);
    SDL_DestroyTexture(mediumEmoticonTexture);
    SDL_DestroyTexture(hardEmoticonTexture);
    SDL_DestroyTexture(lifeIconTexture);
    SDL_DestroyTexture(shieldIconTexture);
    SDL_DestroyTexture(crosshairIconTexture);
    SDL_DestroyTexture(winIconTexture);
    SDL_DestroyTexture(loseIconTexture);

    for (int i = 0; i < ROWS; i++) {
        SDL_DestroyTexture(brickTextures[i]);
    }

    TTF_CloseFont(font);
    TTF_CloseFont(buttonFont);
}
