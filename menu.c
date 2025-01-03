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

        SDL_RenderCopy(renderer, play_button_texture, NULL, &playButtonRect);

        SDL_RenderCopy(renderer, settings_button_texture, NULL, &optionsButtonRect);

        SDL_RenderCopy(renderer, exit_button_texture, NULL, &exitButtonRect);

        SDL_RenderPresent(renderer);
    }
}

/*int displaySettingsMenu(SDL_Renderer* renderer){


    SDL_Surface *background_menu = IMG_Load("assets/img/background_menu.jpg");

    if (!background_menu) {
        printf("Failed to load background image: %s\n", IMG_GetError());
        return -1;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, background_menu);

    if (!texture) {
        printf("Failed to create texture from surface: %s\n", SDL_GetError());
        return -1;
    }

    // Chargement de l'image du bouton easy
    SDL_Surface *button_easy_surface = IMG_Load("../data/img/easy.png");
    SDL_Texture *button_easy_texture = SDL_CreateTextureFromSurface(renderer, button_easy_surface);

    // Chargement de l'image du bouton medium
    SDL_Surface *button_medium_surface = IMG_Load("../data/img/medium.png");
    SDL_Texture *button_medium_texture = SDL_CreateTextureFromSurface(renderer, button_medium_surface);

    // Chargement de l'image du bouton medium
    SDL_Surface *button_hard_surface = IMG_Load("../data/img/hard.png");
    SDL_Texture *button_hard_texture = SDL_CreateTextureFromSurface(renderer, button_hard_surface);



    // Création de la structure du bouton easy
    SDL_Rect button_rect_easy = {
        .x = 195,
        .y = 100,
        .w = 250,
        .h = 90,
    };

    // Création de la structure du bouton medium
    SDL_Rect button_rect_medium = {
        .x = 195,
        .y = 200,
        .w = 250,
        .h = 90,
    };

    // Création de la structure du bouton hard
    SDL_Rect button_rect_hard = {
        .x = 195,
        .y = 300,
        .w = 250,
        .h = 90,
    };

    // Boucle principale
    while (true) {
        // Mise à jour de l'état de la SDL
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return;
            }else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                return;
            }

            SDL_Point easy = { event.button.x, event.button.y };
            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT &&
                    SDL_PointInRect(&easy, &button_rect_easy)) {
                // Gérer le clic sur le bouton easy
                difficulty = 0;
                game(renderer, difficulty);
            }

            SDL_Point medium = { event.button.x, event.button.y };
            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT &&
                    SDL_PointInRect(&medium, &button_rect_medium)) {
                // Gérer le clic sur le bouton medium
                difficulty = 1;
                game(renderer, difficulty);
            }
            SDL_Point hard = { event.button.x, event.button.y };
            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT &&
                    SDL_PointInRect(&hard, &button_rect_hard)) {
                // Gérer le clic sur le bouton hard
                difficulty = 2;
                game(renderer, difficulty);
                    }

        }

        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, texture, NULL, NULL);

        // Affichage de l'image du bouton easy
        SDL_RenderCopy(renderer, button_easy_texture, NULL, &button_rect_easy);

        // Affichage de l'image du bouton medium
        SDL_RenderCopy(renderer, button_medium_texture, NULL, &button_rect_medium);

        //Affichage de l'image du bouton hard
        SDL_RenderCopy(renderer, button_hard_texture, NULL, &button_rect_hard);



        // Affichage de la fenêtre
        SDL_RenderPresent(renderer);
    }
}*/
