//
// Created by hugog on 03/01/2025.
//

#include "menu.h"
#include "game.h"
#include "history.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include <stdio.h>
#include <stdbool.h>


int displayMenu(SDL_Renderer* renderer){

    if (TTF_Init() == -1) {
        printf("Failed to initialize TTF: %s\n", TTF_GetError());
        return -1;
    }

    TTF_Font* font = TTF_OpenFont("resources/assets/fonts/winter_minie.ttf", 100);

    if (!font) {
        printf("Failed to load font: %s\n", TTF_GetError());
        return -1;
    }

    SDL_Color textColor = {255, 255, 255, 255};

    SDL_Surface* titleSurface = TTF_RenderText_Blended(font, "Brick Breaker", textColor);

    if (!titleSurface) {
        printf("Failed to create title surface: %s\n", TTF_GetError());
        return -1;
    }

    SDL_Texture* titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);
    SDL_FreeSurface(titleSurface);

    if (!titleTexture) {
        printf("Failed to create title texture: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Rect titleRect = {
        .x = (1280 - titleSurface->w) / 2,
        .y = 50,
        .w = titleSurface->w,
        .h = titleSurface->h
    };

    SDL_Surface *background_menu = IMG_Load("resources/assets/img/background/background_menu.jpg");

    if (!background_menu) {
        printf("Failed to load background image: %s\n", IMG_GetError());
        return -1;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, background_menu);
    SDL_FreeSurface(background_menu);

    if (!texture) {
        printf("Failed to create texture from surface: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Surface *play_button_surface = IMG_Load("resources/assets/img/buttons/play_button.png");

    if (!play_button_surface) {
        printf("Failed to load play button image: %s\n", IMG_GetError());
        return -1;
    }

    SDL_Texture *play_button_texture = SDL_CreateTextureFromSurface(renderer, play_button_surface);
    SDL_FreeSurface(play_button_surface);

    if (!play_button_texture) {
        printf("Failed to create play button texture: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Surface *settings_button_surface = IMG_Load("resources/assets/img/buttons/settings_button.png");

    if (!settings_button_surface) {
        printf("Failed to load settings button image: %s\n", IMG_GetError());
        return -1;
    }

    SDL_Texture *settings_button_texture = SDL_CreateTextureFromSurface(renderer, settings_button_surface);
    SDL_FreeSurface(settings_button_surface);

    if (!settings_button_texture) {
        printf("Failed to create settings button texture: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Surface *exit_button_surface = IMG_Load("resources/assets/img/buttons/exit_button.png");

    if (!exit_button_surface) {
        printf("Failed to load exit button image: %s\n", IMG_GetError());
        return -1;
    }

    SDL_Texture *exit_button_texture = SDL_CreateTextureFromSurface(renderer, exit_button_surface);
    SDL_FreeSurface(exit_button_surface);

    if (!exit_button_texture) {
        printf("Failed to create exit button texture: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Rect playButtonRect = {
        .x = 128,
        .y = 232,
        .w = 256,
        .h = 256,
    };

    SDL_Rect optionsButtonRect = {
        .x = 512,
        .y = 232,
        .w = 256,
        .h = 256,
    };

    SDL_Rect exitButtonRect = {
        .x = 896,
        .y = 232,
        .w = 256,
        .h = 256,
    };

    while (true) {

        SDL_Event event;

        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {

                return 0;

            } else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {

                SDL_Point mousePoint = { event.button.x, event.button.y };

                if (SDL_PointInRect(&mousePoint, &playButtonRect)) {

                    // game(renderer);

                    SDL_RenderClear(renderer);
                    SDL_RenderCopy(renderer, texture, NULL, NULL);

                } else if (SDL_PointInRect(&mousePoint, &optionsButtonRect)) {

                    displaySettingsMenu(renderer);

                } else if (SDL_PointInRect(&mousePoint, &exitButtonRect)) {

                    return 0;
                }
            }
        }

        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, texture, NULL, NULL);

        SDL_RenderCopy(renderer, titleTexture, NULL, &titleRect);

        SDL_RenderCopy(renderer, play_button_texture, NULL, &playButtonRect);

        SDL_RenderCopy(renderer, settings_button_texture, NULL, &optionsButtonRect);

        SDL_RenderCopy(renderer, exit_button_texture, NULL, &exitButtonRect);

        SDL_RenderPresent(renderer);
    }
}

int selectedDifficulty = 0;

int displaySettingsMenu(SDL_Renderer* renderer) {

    if (TTF_Init() == -1) {
        printf("Failed to initialize TTF: %s\n", TTF_GetError());
        return -1;
    }

    TTF_Font* font = TTF_OpenFont("resources/assets/fonts/winter_minie.ttf", 100);

    if (!font) {
        printf("Failed to load font: %s\n", TTF_GetError());
        return -1;
    }

    SDL_Color textColor = {255, 255, 255, 255};

    SDL_Surface* titleSurface = TTF_RenderText_Blended(font, "Settings", textColor);

    if (!titleSurface) {
        printf("Failed to create title surface: %s\n", TTF_GetError());
        return -1;
    }

    SDL_Texture* titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);
    SDL_FreeSurface(titleSurface);

    if (!titleTexture) {
        printf("Failed to create title texture: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Rect titleRect = {
        .x = (1280 - titleSurface->w) / 2,
        .y = 50,
        .w = titleSurface->w,
        .h = titleSurface->h
    };

    SDL_Surface *background_menu = IMG_Load("resources/assets/img/background/background_menu.jpg");

    if (!background_menu) {
        printf("Failed to load background image: %s\n", IMG_GetError());
        return -1;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, background_menu);
    SDL_FreeSurface(background_menu);

    if (!texture) {
        printf("Failed to create texture from surface: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Surface *easy_level_surface = IMG_Load("resources/assets/img/levels/simple_level.png");

    if (!easy_level_surface) {
        printf("Failed to load easy level image: %s\n", IMG_GetError());
        return -1;
    }

    SDL_Texture *easy_level_texture = SDL_CreateTextureFromSurface(renderer, easy_level_surface);
    SDL_FreeSurface(easy_level_surface);

    if (!easy_level_texture) {
        printf("Failed to create easy level texture: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Rect easyLevelRect = {
        .x = 192,
        .y = 315,
        .w = 170,
        .h = 170,
    };

    SDL_Surface *medium_level_surface = IMG_Load("resources/assets/img/levels/medium_level.png");

    if (!medium_level_surface) {
        printf("Failed to load medium level image: %s\n", IMG_GetError());
        return -1;
    }

    SDL_Texture *medium_level_texture = SDL_CreateTextureFromSurface(renderer, medium_level_surface);
    SDL_FreeSurface(medium_level_surface);

    if (!medium_level_texture) {
        printf("Failed to create medium level texture: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Rect mediumLevelRect = {
        .x = 554,
        .y = 315,
        .w = 170,
        .h = 170,
    };

    SDL_Surface *hard_level_surface = IMG_Load("resources/assets/img/levels/hard_level.png");

    if (!hard_level_surface) {
        printf("Failed to load hard level image: %s\n", IMG_GetError());
        return -1;
    }

    SDL_Texture *hard_level_texture = SDL_CreateTextureFromSurface(renderer, hard_level_surface);
    SDL_FreeSurface(hard_level_surface);

    if (!hard_level_texture) {
        printf("Failed to create hard level texture: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Rect hardLevelRect = {
        .x = 916,
        .y = 315,
        .w = 170,
        .h = 170,
    };

    SDL_Surface *back_button_surface = IMG_Load("resources/assets/img/buttons/back_button.png");

    if (!back_button_surface) {
        printf("Failed to load back button image: %s\n", IMG_GetError());
        return -1;
    }

    SDL_Texture *back_button_texture = SDL_CreateTextureFromSurface(renderer, back_button_surface);
    SDL_FreeSurface(back_button_surface);

    if (!back_button_texture) {
        printf("Failed to create back button texture: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Rect backButtonRect = {
        .x = 10,
        .y = 30,
        .w = 128,
        .h = 128,
    };

    TTF_Font* instructionTextFont = TTF_OpenFont("resources/assets/fonts/winter_minie.ttf", 32);

    SDL_Surface* chooseDifficultySurface = TTF_RenderText_Blended(instructionTextFont, "Please select difficulty :", textColor);
    SDL_Texture* chooseDifficultyTexture = SDL_CreateTextureFromSurface(renderer, chooseDifficultySurface);
    SDL_FreeSurface(chooseDifficultySurface);

    SDL_Rect chooseDifficultyRect = { .x = 50, .y = 225, .w = chooseDifficultySurface->w, .h = chooseDifficultySurface->h };

    TTF_Font* textLevelFont = TTF_OpenFont("resources/assets/fonts/winter_minie.ttf", 24);

    SDL_Surface* easyTextSurface = TTF_RenderText_Blended(textLevelFont, "Easy", textColor);
    SDL_Texture* easyTextTexture = SDL_CreateTextureFromSurface(renderer, easyTextSurface);
    SDL_FreeSurface(easyTextSurface);

    SDL_Rect easyTextRect = {
        .x = 240,
        .y = 500,
        .w = easyTextSurface->w,
        .h = easyTextSurface->h
    };

    SDL_Surface* mediumTextSurface = TTF_RenderText_Blended(textLevelFont, "Medium", textColor);
    SDL_Texture* mediumTextTexture = SDL_CreateTextureFromSurface(renderer, mediumTextSurface);
    SDL_FreeSurface(mediumTextSurface);

    SDL_Rect mediumTextRect = {
        .x = 590,
        .y = 500,
        .w = mediumTextSurface->w,
        .h = mediumTextSurface->h
    };

    SDL_Surface* hardTextSurface = TTF_RenderText_Blended(textLevelFont, "Hard", textColor);
    SDL_Texture* hardTextTexture = SDL_CreateTextureFromSurface(renderer, hardTextSurface);
    SDL_FreeSurface(hardTextSurface);

    SDL_Rect hardTextRect = {
        .x = 975,
        .y = 500,
        .w = hardTextSurface->w,
        .h = hardTextSurface->h
    };

    /*SDL_Rect easyLevelRect = {
        .x = 192,
        .y = 315,
        .w = 170,
        .h = 170,
    };*/

    /*SDL_Rect mediumLevelRect = {
        .x = 554,
        .y = 315,
        .w = 170,
        .h = 170,
    };*/

    /*SDL_Rect hardLevelRect = {
        .x = 916,
        .y = 315,
        .w = 170,
        .h = 170,
    };*/

    /*SDL_Rect backButtonRect = {
        .x = 10,
        .y = 30,
        .w = 128,
        .h = 128,
    };*/

    while (true) {

        SDL_Event event;

        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {

                return 0;

            } else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {

                SDL_Point mousePoint = { event.button.x, event.button.y };

                if (SDL_PointInRect(&mousePoint, &easyLevelRect)) {

                    //difficulty = 1;

                } else if (SDL_PointInRect(&mousePoint, &mediumLevelRect)) {

                    //difficulty = 2;

                } else if (SDL_PointInRect(&mousePoint, &hardLevelRect)) {

                    //difficulty = 3;

                } else if (SDL_PointInRect(&mousePoint, &backButtonRect)) {

                    return displayMenu(renderer);
                }
            }
        }

        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, texture, NULL, NULL);

        SDL_RenderCopy(renderer, easy_level_texture, NULL, &easyLevelRect);
        SDL_RenderCopy(renderer, medium_level_texture, NULL, &mediumLevelRect);
        SDL_RenderCopy(renderer, hard_level_texture, NULL, &hardLevelRect);
        SDL_RenderCopy(renderer, back_button_texture, NULL, &backButtonRect);

        SDL_RenderCopy(renderer, titleTexture, NULL, &titleRect);

        SDL_RenderCopy(renderer, chooseDifficultyTexture, NULL, &chooseDifficultyRect);

        SDL_RenderCopy(renderer, easyTextTexture, NULL, &easyTextRect);
        SDL_RenderCopy(renderer, mediumTextTexture, NULL, &mediumTextRect);
        SDL_RenderCopy(renderer, hardTextTexture, NULL, &hardTextRect);

        SDL_RenderPresent(renderer);
    }
}