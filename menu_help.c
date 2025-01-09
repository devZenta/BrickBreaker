//
// Created by hugog on 04/01/2025.
//

#include "menu_help.h"
#include "menu.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

int displayHelpMenu(SDL_Renderer* renderer) {

    if (TTF_Init() == -1) {
        printf("Failed to initialize TTF: %s\n", TTF_GetError());
    }

    TTF_Font* font = TTF_OpenFont("resources/assets/fonts/winter_minie.ttf", 100);
    TTF_Font* subtitleFont = TTF_OpenFont("resources/assets/fonts/camcode.ttf", 35);
    TTF_Font* textFont = TTF_OpenFont("resources/assets/fonts/camcode.ttf", 25);

    if (!font || !subtitleFont || !textFont) {
        printf("Failed to load font: %s\n", TTF_GetError());
    }

    SDL_Color textColor = {255, 255, 255, 255};

    SDL_Surface* titleSurface = TTF_RenderText_Blended(font, "Help", textColor);
    SDL_Surface* howToPlayTitleSurface = TTF_RenderText_Blended(subtitleFont, "How to Play", textColor);
    SDL_Surface* followInstructionsTitleSurface = TTF_RenderText_Blended(subtitleFont, "Please follow these instructions", textColor);
    SDL_Surface* doNotModifySurface = TTF_RenderText_Blended(textFont, "Please do not modify the settings file directly.", textColor);

    if (!titleSurface || !howToPlayTitleSurface || !followInstructionsTitleSurface || !doNotModifySurface) {
        printf("Failed to create title surface: %s\n", TTF_GetError());
    }

    SDL_Texture* titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);
    SDL_Texture* howToPlayTitleTexture = SDL_CreateTextureFromSurface(renderer, howToPlayTitleSurface);
    SDL_Texture* followInstructionsTitleTexture = SDL_CreateTextureFromSurface(renderer, followInstructionsTitleSurface);
    SDL_Texture* doNotModifyTexture = SDL_CreateTextureFromSurface(renderer, doNotModifySurface);
    SDL_FreeSurface(titleSurface);
    SDL_FreeSurface(howToPlayTitleSurface);
    SDL_FreeSurface(followInstructionsTitleSurface);
    SDL_FreeSurface(doNotModifySurface);

    if (!titleTexture || !howToPlayTitleTexture || !followInstructionsTitleTexture || !doNotModifyTexture) {
        printf("Failed to create title texture: %s\n", SDL_GetError());
    }

    SDL_Rect titleRect = {
        .x = (1280 - titleSurface->w) / 2 - 45,
        .y = 50,
        .w = titleSurface->w,
        .h = titleSurface->h
    };

    SDL_Rect howToPlayTitleRect = {
        .x = 260,
        .y = 230,
        .w = howToPlayTitleSurface->w,
        .h = howToPlayTitleSurface->h
    };

    SDL_Rect followInstructionsTitleRect = {
        .x = 255,
        .y = 525,
        .w = followInstructionsTitleSurface->w,
        .h = followInstructionsTitleSurface->h
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

    SDL_Surface *back_button_surface = IMG_Load("resources/assets/img/buttons/back_button.png");

    if (!back_button_surface) {
        printf("Failed to load back button image: %s\n", IMG_GetError());
    }

    SDL_Texture *back_button_texture = SDL_CreateTextureFromSurface(renderer, back_button_surface);
    SDL_FreeSurface(back_button_surface);

    if (!back_button_texture) {
        printf("Failed to create back button texture: %s\n", SDL_GetError());
    }

    SDL_Rect backButtonRect = {
        .x = 10,
        .y = 30,
        .w = 128,
        .h = 128
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
        .x = 1280 - 226 - 10,
        .y = -10,
        .w = 212,
        .h = 212
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

    SDL_Surface* howToPlayIconSurface = IMG_Load("resources/assets/img/icons/howToPlay.png");
    SDL_Surface* ruleIconSurface = IMG_Load("resources/assets/img/icons/pin.png");
    SDL_Surface* followInstructionsIconSurface = IMG_Load("resources/assets/img/icons/danger.png");

    if (!howToPlayIconSurface || !ruleIconSurface || !followInstructionsIconSurface) {
        printf("Failed to load icon image: %s\n", IMG_GetError());
    }

    SDL_Texture* howToPlayIconTexture = SDL_CreateTextureFromSurface(renderer, howToPlayIconSurface);
    SDL_Texture* ruleIconTexture = SDL_CreateTextureFromSurface(renderer, ruleIconSurface);
    SDL_Texture* followInstructionsIconTexture = SDL_CreateTextureFromSurface(renderer, followInstructionsIconSurface);
    SDL_FreeSurface(howToPlayIconSurface);
    SDL_FreeSurface(ruleIconSurface);
    SDL_FreeSurface(followInstructionsIconSurface);

    if (!howToPlayIconTexture || !ruleIconTexture || !followInstructionsIconTexture) {
        printf("Failed to create icon texture: %s\n", SDL_GetError());
    }

    SDL_Rect howToPlayIconRect = {
        .x = 150,
        .y = 200,
        .w = 100,
        .h = 100
    };

    SDL_Rect followInstructionsIconRect = {
        .x = 160,
        .y = 500,
        .w = 80,
        .h = 80
    };


    SDL_bool quit = false;
    bool leave = false;
    bool back = false;

    while (!quit) {

        SDL_Event event;

        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT) {

                return 0;

            } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {

                leave = true;
                break;

            } else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {

                SDL_Point mousePoint = { event.button.x, event.button.y };

                if (SDL_PointInRect(&mousePoint, &backButtonRect)) {

                    printf("Back button clicked\n");
                    back = true;

                } else if (SDL_PointInRect(&mousePoint, &exitButtonRect)) {

                    return 0;
                }
            }
        }

        if (leave) {
            displayMenu(renderer);
            quit = true;
            return 1;
        } else if (back) {
            displayMenu(renderer);
            quit = true;
            return 1;
        }

        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, texture, NULL, NULL);

        SDL_RenderCopy(renderer, back_button_texture, NULL, &backButtonRect);
        SDL_RenderCopy(renderer, exit_button_texture, NULL, &exitButtonRect);

        SDL_RenderCopy(renderer, titleTexture, NULL, &titleRect);

        SDL_RenderCopy(renderer, howToPlayTitleTexture, NULL, &howToPlayTitleRect);
        SDL_RenderCopy(renderer, howToPlayIconTexture, NULL, &howToPlayIconRect);

        SDL_RenderCopy(renderer, followInstructionsTitleTexture, NULL, &followInstructionsTitleRect);
        SDL_RenderCopy(renderer, followInstructionsIconTexture, NULL, &followInstructionsIconRect);

        SDL_RenderCopy(renderer, iconDevTexture, NULL, &iconDevRect);
        SDL_RenderCopy(renderer, textCreatorTexture, NULL, &textCreatorRect);

        SDL_RenderPresent(renderer);
    }
}