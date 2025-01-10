//
// Created by hugog on 03/01/2025.
//

#include "menu.h"
#include "menu_settings.h"
#include "game.h"
#include "menu_help.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include <stdio.h>
#include <stdbool.h>
#include <windows.h>


int displayMenu(SDL_Renderer* renderer){

    if (TTF_Init() == -1) {
        printf("Failed to initialize TTF: %s\n", TTF_GetError());
    }

    TTF_Font* font = TTF_OpenFont("resources/assets/fonts/winter_minie.ttf", 100);

    if (!font) {
        printf("Failed to load font: %s\n", TTF_GetError());
    }

    SDL_Color textColor = {
        255,
        255,
        255,
        255
    };

    SDL_Surface* titleSurface = TTF_RenderText_Blended(font, "Brick Breaker", textColor);

    if (!titleSurface) {
        printf("Failed to create title surface: %s\n", TTF_GetError());
    }

    SDL_Texture* titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);
    SDL_FreeSurface(titleSurface);

    if (!titleTexture) {
        printf("Failed to create title texture: %s\n", SDL_GetError());
    }

    SDL_Rect titleRect = {
        .x = (1280 - titleSurface->w) / 2 ,
        .y = 50,
        .w = titleSurface->w,
        .h = titleSurface->h
    };

    SDL_Surface *background_menu = IMG_Load("resources/assets/img/background/background_menu.jpg");

    if (!background_menu) {
        printf("Failed to load background image: %s\n", IMG_GetError());
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, background_menu);
    SDL_FreeSurface(background_menu);

    if (!texture) {
        printf("Failed to create texture from surface: %s\n", SDL_GetError());
    }

    SDL_Surface *play_button_surface = IMG_Load("resources/assets/img/buttons/play_button.png");

    if (!play_button_surface) {
        printf("Failed to load play button image: %s\n", IMG_GetError());
    }

    SDL_Texture *play_button_texture = SDL_CreateTextureFromSurface(renderer, play_button_surface);
    SDL_FreeSurface(play_button_surface);

    if (!play_button_texture) {
        printf("Failed to create play button texture: %s\n", SDL_GetError());
    }

    SDL_Rect playButtonRect = {
        .x = 520,
        .y = 400,
        .w = 170,
        .h = 170
    };

    SDL_Surface *settings_button_surface = IMG_Load("resources/assets/img/buttons/settings_button.png");

    if (!settings_button_surface) {
        printf("Failed to load settings button image: %s\n", IMG_GetError());
    }

    SDL_Texture *settings_button_texture = SDL_CreateTextureFromSurface(renderer, settings_button_surface);
    SDL_FreeSurface(settings_button_surface);

    if (!settings_button_texture) {
        printf("Failed to create settings button texture: %s\n", SDL_GetError());
    }

    SDL_Rect settingsButtonRect = {
        .x = 30,
        .y = 30,
        .w = 150,
        .h = 150
    };

    SDL_Surface *exit_button_surface = IMG_Load("resources/assets/img/buttons/exit_button.png");

    if (!exit_button_surface) {
        printf("Failed to load exit button image: %s\n", IMG_GetError());
    }

    SDL_Texture *exit_button_texture = SDL_CreateTextureFromSurface(renderer, exit_button_surface);
    SDL_FreeSurface(exit_button_surface);

    if (!exit_button_texture) {
        printf("Failed to create exit button texture: %s\n", SDL_GetError());
    }

    SDL_Rect exitButtonRect = {
        .x = 1280 - 148 - 10,
        .y = 20,
        .w = 148,
        .h = 148
    };

    SDL_Surface* iconDevSurface = IMG_Load("resources/assets/img/icons/coding.png");

    if (!iconDevSurface) {
        printf("Failed to load dev icon image: %s\n", IMG_GetError());
    }

    SDL_Texture* iconDevTexture = SDL_CreateTextureFromSurface(renderer, iconDevSurface);
    SDL_FreeSurface(iconDevSurface);

    if (!iconDevTexture) {
        printf("Failed to create dev icon texture: %s\n", SDL_GetError());
    }

    SDL_Rect iconDevRect = {
        .x = 1280 - 64 - 20,
        .y = 720 - 64 - 20,
        .w = 64,
        .h = 64
    };

    TTF_Font* footerFont = TTF_OpenFont("resources/assets/fonts/camcode.ttf", 30);

    if (!footerFont) {
        printf("Failed to load footerFont: %s\n", TTF_GetError());
    }

    SDL_Surface* textCreatorSurface = TTF_RenderText_Blended(footerFont, "created by zenta ", textColor);

    if (!textCreatorSurface) {
        printf("Failed to load textCreatorSurface: %s\n", IMG_GetError());
    }

    SDL_Texture* textCreatorTexture = SDL_CreateTextureFromSurface(renderer, textCreatorSurface);
    SDL_FreeSurface(textCreatorSurface);

    if (!textCreatorTexture) {
        printf("Failed to create creator text texture: %s\n", SDL_GetError());
    }

    SDL_Rect textCreatorRect = {
        .x = iconDevRect.x - textCreatorSurface->w - 10,
        .y = iconDevRect.y + (iconDevRect.h - textCreatorSurface->h) / 2,
        .w = textCreatorSurface->w,
        .h = textCreatorSurface->h
    };

    SDL_Surface* githubButtonSurface = IMG_Load("resources/assets/img/buttons/github_button.png");

    if (!githubButtonSurface) {
        printf("Failed to load GitHub icon image: %s\n", IMG_GetError());
    }

    SDL_Texture* githubButtonTexture = SDL_CreateTextureFromSurface(renderer, githubButtonSurface);
    SDL_FreeSurface(githubButtonSurface);

    if (!githubButtonTexture) {
        printf("Failed to create GitHub button texture: %s\n", SDL_GetError());
    }

    SDL_Rect githubButtonRect = {
        .x = 20,
        .y = 720 - 64 - 20,
        .w = 64,
        .h = 64
    };

    SDL_Surface* githubTextSurface = TTF_RenderText_Blended(footerFont, "click on me", textColor);

    if (!githubTextSurface) {
        printf("Failed to load githubTextSurface: %s\n", IMG_GetError());
    }

    SDL_Texture* githubTextTexture = SDL_CreateTextureFromSurface(renderer, githubTextSurface);
    SDL_FreeSurface(githubTextSurface);

    if (!githubTextTexture) {
        printf("Failed to create GitHub text texture: %s\n", SDL_GetError());
    }

    SDL_Rect githubTextRect = {
        .x = githubButtonRect.x + githubButtonRect.w + 10,
        .y = githubButtonRect.y + (githubButtonRect.h - githubTextSurface->h) / 2,
        .w = githubTextSurface->w,
        .h = githubTextSurface->h
    };

    SDL_Surface* helpButtonSurface = IMG_Load("resources/assets/img/buttons/help_button.png");

    if (!helpButtonSurface) {
        printf("Failed to load help button image: %s\n", IMG_GetError());
    }

    SDL_Texture* helpButtonTexture = SDL_CreateTextureFromSurface(renderer, helpButtonSurface);
    SDL_FreeSurface(helpButtonSurface);

    if (!helpButtonTexture) {
        printf("Failed to create help button texture: %s\n", SDL_GetError());
    }

    SDL_Rect helpButtonRect = {
        .x = (githubTextRect.x + textCreatorRect.x) / 2 - 75,
        .y = 720 - 64 - 20,
        .w = 64,
        .h = 64
    };

    SDL_Surface* helpTextSurface = TTF_RenderText_Blended(footerFont, "Need more help ?", textColor);

    if (!helpTextSurface) {
        printf("Failed to load helpTextSurface: %s\n", IMG_GetError());
    }

    SDL_Texture* helpTextTexture = SDL_CreateTextureFromSurface(renderer, helpTextSurface);
    SDL_FreeSurface(helpTextSurface);

    if (!helpTextTexture) {
        printf("Failed to create help text texture: %s\n", SDL_GetError());
    }

    SDL_Rect helpTextRect = {
        .x = helpButtonRect.x + helpButtonRect.w + 10,
        .y = helpButtonRect.y + (helpButtonRect.h - helpTextSurface->h) / 2,
        .w = helpTextSurface->w,
        .h = helpTextSurface->h
    };

    SDL_bool quit = false;
    bool game = false;
    bool settings = false;
    bool help = false;

    while (!quit) {

        SDL_Event event;

        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {

                return 0;

            } else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {

                SDL_Point mousePoint = { event.button.x, event.button.y };

                if (SDL_PointInRect(&mousePoint, &playButtonRect)) {

                    printf("Play clicked\n");
                    game = true;
                    break;

                } else if (SDL_PointInRect(&mousePoint, &settingsButtonRect)) {

                    printf("Settings clicked\n");
                    settings = true;
                    break;

                } else if (SDL_PointInRect(&mousePoint, &exitButtonRect)) {

                    return 0;

                } else if (SDL_PointInRect(&mousePoint, &githubButtonRect) || SDL_PointInRect(&mousePoint, &githubTextRect)) {

                    ShellExecute(0, 0, "https://github.com/devZenta/BrickBreaker", 0, 0, SW_SHOW);

                } else if (SDL_PointInRect(&mousePoint, &helpButtonRect)) {

                    printf("Help clicked\n");
                    help = true;
                    break;
                }
            }
        }

        if(game){
            //displayGame(renderer);
            quit = true;
            return 1;
        } else if(settings){
            displaySettingsMenu(renderer);
            quit = true;
            return 1;
        } else if (help){
            displayHelpMenu(renderer);
            quit = true;
            return 1;
        }

        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, texture, NULL, NULL);

        SDL_RenderCopy(renderer, titleTexture, NULL, &titleRect);

        SDL_RenderCopy(renderer, play_button_texture, NULL, &playButtonRect);
        SDL_RenderCopy(renderer, settings_button_texture, NULL, &settingsButtonRect);
        SDL_RenderCopy(renderer, exit_button_texture, NULL, &exitButtonRect);

        SDL_RenderCopy(renderer, iconDevTexture, NULL, &iconDevRect);
        SDL_RenderCopy(renderer, textCreatorTexture, NULL, &textCreatorRect);

        SDL_RenderCopy(renderer, githubButtonTexture, NULL, &githubButtonRect);
        SDL_RenderCopy(renderer, githubTextTexture, NULL, &githubTextRect);

        SDL_RenderCopy(renderer, helpButtonTexture, NULL, &helpButtonRect);
        SDL_RenderCopy(renderer, helpTextTexture, NULL, &helpTextRect);

        SDL_RenderPresent(renderer);
    }
}