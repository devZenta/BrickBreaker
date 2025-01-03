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

    SDL_Surface *background_menu = IMG_Load("resources/assets/img/background_menu.jpg");

    if (!background_menu) {
        printf("Failed to load background image: %s\n", IMG_GetError());
        return -1;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, background_menu);

    if (!texture) {
        printf("Failed to create texture from surface: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Surface *play_button_surface = IMG_Load("resources/assets/img/play_button.png");

    if (!play_button_surface) {
        printf("Failed to load play button image: %s\n", IMG_GetError());
        return -1;
    }

    SDL_Texture *play_button_texture = SDL_CreateTextureFromSurface(renderer, play_button_surface);

    if (!play_button_texture) {
        printf("Failed to create play button texture: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Surface *settings_button_surface = IMG_Load("resources/assets/img/settings_button.png");

    if (!settings_button_surface) {
        printf("Failed to load settings button image: %s\n", IMG_GetError());
        return -1;
    }

    SDL_Texture *settings_button_texture = SDL_CreateTextureFromSurface(renderer, settings_button_surface);

    if (!settings_button_texture) {
        printf("Failed to create settings button texture: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Surface *exit_button_surface = IMG_Load("resources/assets/img/exit_button.png");

    if (!exit_button_surface) {
        printf("Failed to load exit button image: %s\n", IMG_GetError());
        return -1;
    }

    SDL_Texture *exit_button_texture = SDL_CreateTextureFromSurface(renderer, exit_button_surface);

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

                    //SDL_RenderClear(renderer);
                    //SDL_RenderCopy(renderer, texture, NULL, NULL);

                } else if (SDL_PointInRect(&mousePoint, &optionsButtonRect)) {

                    //displaySettingsMenu(renderer);


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
