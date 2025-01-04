//
// Created by hugog on 04/01/2025.
//

#include "menu_settings.h"
#include "menu.h"
#include "utils.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

int displaySettingsMenu(SDL_Renderer* renderer) {

    int selectedDifficulty, volume;

    load_settings(&selectedDifficulty, &volume);

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
        .h = 170
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
        .h = 170
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
        .h = 170
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
        .h = 128
    };

    TTF_Font* instructionsTextFont = TTF_OpenFont("resources/assets/fonts/winter_minie.ttf", 32);

    if (!instructionsTextFont) {
        printf("Failed to load instructionsTextFont: %s\n", TTF_GetError());
        return -1;
    }

    SDL_Surface* chooseDifficultySurface = TTF_RenderText_Blended(instructionsTextFont, "Please select difficulty :", textColor);

    if (!chooseDifficultySurface) {
        printf("Failed to create chooseDifficultySurface: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Texture* chooseDifficultyTexture = SDL_CreateTextureFromSurface(renderer, chooseDifficultySurface);
    SDL_FreeSurface(chooseDifficultySurface);

    if (!chooseDifficultyTexture) {
        printf("Failed to create chooseDifficultyTexture: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Rect chooseDifficultyRect = {
        .x = 50,
        .y = 225,
        .w = chooseDifficultySurface->w,
        .h = chooseDifficultySurface->h
    };

    TTF_Font* textLevelFont = TTF_OpenFont("resources/assets/fonts/winter_minie.ttf", 24);

    if (!textLevelFont) {
        printf("Failed to load textLevelFont: %s\n", TTF_GetError());
        return -1;
    }

    SDL_Surface* easyTextSurface = TTF_RenderText_Blended(textLevelFont, "Easy", textColor);

    if (!easyTextSurface) {
        printf("Failed to create easyTextSurface: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Texture* easyTextTexture = SDL_CreateTextureFromSurface(renderer, easyTextSurface);
    SDL_FreeSurface(easyTextSurface);

    if (!easyTextTexture) {
        printf("Failed to create easyTextTexture: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Rect easyTextRect = {
        .x = 240,
        .y = 500,
        .w = easyTextSurface->w,
        .h = easyTextSurface->h
    };

    SDL_Surface* mediumTextSurface = TTF_RenderText_Blended(textLevelFont, "Medium", textColor);

    if (!mediumTextSurface) {
        printf("Failed to create mediumTextSurface: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Texture* mediumTextTexture = SDL_CreateTextureFromSurface(renderer, mediumTextSurface);
    SDL_FreeSurface(mediumTextSurface);

    if (!mediumTextTexture) {
        printf("Failed to create mediumTextTexture: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Rect mediumTextRect = {
        .x = 590,
        .y = 500,
        .w = mediumTextSurface->w,
        .h = mediumTextSurface->h
    };

    SDL_Surface* hardTextSurface = TTF_RenderText_Blended(textLevelFont, "Hard", textColor);

    if (!hardTextSurface) {
        printf("Failed to create hardTextSurface: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Texture* hardTextTexture = SDL_CreateTextureFromSurface(renderer, hardTextSurface);
    SDL_FreeSurface(hardTextSurface);

    if (!hardTextTexture) {
        printf("Failed to create hardTextTexture: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Rect hardTextRect = {
        .x = 975,
        .y = 500,
        .w = hardTextSurface->w,
        .h = hardTextSurface->h
    };

    SDL_Surface* checkboxUncheckedSurface = IMG_Load("resources/assets/img/icons/checkbox_unchecked.png");
    SDL_Surface* checkboxCheckedSurface = IMG_Load("resources/assets/img/icons/checkbox_checked.png");

    if (!checkboxUncheckedSurface || !checkboxCheckedSurface) {
        printf("Failed to load checkbox images: %s\n", IMG_GetError());
        return -1;
    }

    SDL_Texture* checkboxUncheckedTexture = SDL_CreateTextureFromSurface(renderer, checkboxUncheckedSurface);
    SDL_Texture* checkboxCheckedTexture = SDL_CreateTextureFromSurface(renderer, checkboxCheckedSurface);

    SDL_FreeSurface(checkboxUncheckedSurface);
    SDL_FreeSurface(checkboxCheckedSurface);

    if (!checkboxUncheckedTexture || !checkboxCheckedTexture) {
        printf("Failed to create checkbox textures: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Rect easyCheckboxRect = {
        .x = 200,
        .y = 500,
        .w = 24,
        .h = 24
    };

    SDL_Rect mediumCheckboxRect = {
        .x = 550,
        .y = 500,
        .w = 24,
        .h = 24
    };

    SDL_Rect hardCheckboxRect = {
        .x = 935,
        .y = 500,
        .w = 24,
        .h = 24
    };

    SDL_Surface* volumeOnSurface = IMG_Load("resources/assets/img/buttons/volume_on_button.png");
    SDL_Surface* volumeOffSurface = IMG_Load("resources/assets/img/buttons/volume_off_button.png");

    if (!volumeOnSurface || !volumeOffSurface) {
        printf("Failed to load volume button images: %s\n", IMG_GetError());
        return -1;
    }

    SDL_Texture* volumeOnTexture = SDL_CreateTextureFromSurface(renderer, volumeOnSurface);
    SDL_Texture* volumeOffTexture = SDL_CreateTextureFromSurface(renderer, volumeOffSurface);

    SDL_FreeSurface(volumeOnSurface);
    SDL_FreeSurface(volumeOffSurface);

    if (!volumeOnTexture || !volumeOffTexture) {
        printf("Failed to create volume button textures: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Surface* enableVolumeSurface = TTF_RenderText_Blended(instructionsTextFont, "Active volume :", textColor);
    SDL_Surface* disableVolumeSurface = TTF_RenderText_Blended(instructionsTextFont, "Muted volume :", textColor);

    SDL_Texture* enableVolumeTexture = SDL_CreateTextureFromSurface(renderer, enableVolumeSurface);
    SDL_Texture* disableVolumeTexture = SDL_CreateTextureFromSurface(renderer, disableVolumeSurface);

    SDL_FreeSurface(enableVolumeSurface);
    SDL_FreeSurface(disableVolumeSurface);

    if (!enableVolumeTexture || !disableVolumeTexture) {
        printf("Failed to create volume text textures: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Rect volumeTextRect = {
        .x = 50,
        .y = 624,
        .w = enableVolumeSurface->w,
        .h = enableVolumeSurface->h
    };

    SDL_Rect volumeButtonRect = {
        .x = volumeTextRect.x + volumeTextRect.w + 20,
        .y = 612,
        .w = 64,
        .h = 64
    };

    while (true) {

        SDL_Event event;

        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {

                return 0;

            } else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {

                SDL_Point mousePoint = { event.button.x, event.button.y };

                if (SDL_PointInRect(&mousePoint, &easyLevelRect)) {

                    selectedDifficulty = 1;
                    save_single_setting("difficulty", 1);

                } else if (SDL_PointInRect(&mousePoint, &mediumLevelRect)) {

                    selectedDifficulty = 2;
                    save_single_setting("difficulty", 2);

                } else if (SDL_PointInRect(&mousePoint, &hardLevelRect)) {

                    selectedDifficulty = 3;
                    save_single_setting("difficulty", 3);

                } else if (SDL_PointInRect(&mousePoint, &backButtonRect)) {

                    return displayMenu(renderer);

                } else if (SDL_PointInRect(&mousePoint, &volumeButtonRect)) {

                    volume = !volume;
                    save_single_setting("volume", volume);
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

        SDL_RenderCopy(renderer, selectedDifficulty == 1 ? checkboxCheckedTexture : checkboxUncheckedTexture, NULL, &easyCheckboxRect);
        SDL_RenderCopy(renderer, selectedDifficulty == 2 ? checkboxCheckedTexture : checkboxUncheckedTexture, NULL, &mediumCheckboxRect);
        SDL_RenderCopy(renderer, selectedDifficulty == 3 ? checkboxCheckedTexture : checkboxUncheckedTexture, NULL, &hardCheckboxRect);

        SDL_RenderCopy(renderer, easyTextTexture, NULL, &easyTextRect);
        SDL_RenderCopy(renderer, mediumTextTexture, NULL, &mediumTextRect);
        SDL_RenderCopy(renderer, hardTextTexture, NULL, &hardTextRect);

        SDL_RenderCopy(renderer, volume ? enableVolumeTexture : disableVolumeTexture, NULL, &volumeTextRect);
        SDL_RenderCopy(renderer, volume ? volumeOnTexture : volumeOffTexture, NULL, &volumeButtonRect);

        SDL_RenderPresent(renderer);
    }
}
