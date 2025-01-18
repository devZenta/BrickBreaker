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
    TTF_Font* textFont = TTF_OpenFont("resources/assets/fonts/camcode.ttf", 20);

    if (!font || !subtitleFont || !textFont) {
        printf("Failed to load font: %s\n", TTF_GetError());
    }

    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Color textColorBull = {0, 0, 0, 255};

    SDL_Surface* titleSurface = TTF_RenderText_Blended(font, "Help", textColor);
    SDL_Surface* howToPlayTitleSurface = TTF_RenderText_Blended(subtitleFont, "How to Play", textColor);
    SDL_Surface* followInstructionsTitleSurface = TTF_RenderText_Blended(subtitleFont, "Instructions", textColor);
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
        .x = (1280 - titleSurface->w) / 2 - 20,
        .y = 50,
        .w = titleSurface->w,
        .h = titleSurface->h
    };

    SDL_Rect howToPlayTitleRect = {
        .x = 260,
        .y = 180,
        .w = howToPlayTitleSurface->w,
        .h = howToPlayTitleSurface->h
    };

    SDL_Rect followInstructionsTitleRect = {
        .x = 255,
        .y = 485,
        .w = followInstructionsTitleSurface->w,
        .h = followInstructionsTitleSurface->h
    };

    SDL_Rect doNotModifyRect = {
        .x = 290,
        .y = 560,
        .w = doNotModifySurface->w,
        .h = doNotModifySurface->h
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
        .y = 20,
        .w = 148,
        .h = 148
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

    SDL_Surface* textCreatorSurface = TTF_RenderText_Blended(footerFont, "By zenta ", textColor);

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
        .y = 150,
        .w = 100,
        .h = 100
    };

    SDL_Rect followInstructionsIconRect = {
        .x = 160,
        .y = 460,
        .w = 80,
        .h = 80
    };

    SDL_Surface* rule1Surface = TTF_RenderText_Blended(textFont, "Move the paddle to bounce the ball and break the bricks", textColor);
    SDL_Surface* rule2Surface = TTF_RenderText_Blended(textFont, "Prevent the ball from falling below the paddle to stay in the game", textColor);
    SDL_Surface* rule3Surface = TTF_RenderText_Blended(textFont, "Break all the bricks to complete the level and win", textColor);
    SDL_Surface* rule4Surface = TTF_RenderText_Blended(textFont, "Pick up power-ups to unlock special abilities and boosts", textColor);

    if (!rule1Surface || !rule2Surface || !rule3Surface || !rule4Surface) {
        printf("Failed to create rule surface: %s\n", TTF_GetError());
    }

    SDL_Texture* rule1Texture = SDL_CreateTextureFromSurface(renderer, rule1Surface);
    SDL_Texture* rule2Texture = SDL_CreateTextureFromSurface(renderer, rule2Surface);
    SDL_Texture* rule3Texture = SDL_CreateTextureFromSurface(renderer, rule3Surface);
    SDL_Texture* rule4Texture = SDL_CreateTextureFromSurface(renderer, rule4Surface);
    SDL_FreeSurface(rule1Surface);
    SDL_FreeSurface(rule2Surface);
    SDL_FreeSurface(rule3Surface);
    SDL_FreeSurface(rule4Surface);

    if (!rule1Texture || !rule2Texture || !rule3Texture || !rule4Texture) {
        printf("Failed to create rule texture: %s\n", SDL_GetError());
    }

    SDL_Rect rule1Rect = {
        .x = 290,
        .y = 260,
        .w = rule1Surface->w,
        .h = rule1Surface->h
    };

    SDL_Rect rule2Rect = {
        .x = 290,
        .y = 310,
        .w = rule2Surface->w,
        .h = rule2Surface->h
    };

    SDL_Rect rule3Rect = {
        .x = 290,
        .y = 360,
        .w = rule3Surface->w,
        .h = rule3Surface->h
    };

    SDL_Rect rule4Rect = {
        .x = 290,
        .y = 410,
        .w = rule4Surface->w,
        .h = rule4Surface->h
    };

    SDL_Surface* pinIconSurface = IMG_Load("resources/assets/img/icons/pin.png");

    if (!pinIconSurface) {
        printf("Failed to load icon image: %s\n", IMG_GetError());
    }

    SDL_Texture* pinIconTexture = SDL_CreateTextureFromSurface(renderer, pinIconSurface);
    SDL_FreeSurface(pinIconSurface);

    if (!pinIconTexture) {
        printf("Failed to create icon texture: %s\n", SDL_GetError());
    }

    SDL_Rect pinIconRect1 = {
        .x = 250,
        .y = 245,
        .w = 34,
        .h = 34
    };

    SDL_Rect pinIconRect2 = {
        .x = 250,
        .y = 295,
        .w = 34,
        .h = 34
    };

    SDL_Rect pinIconRect3 = {
        .x = 250,
        .y = 345,
        .w = 34,
        .h = 34
    };

    SDL_Rect pinIconRect4 = {
        .x = 250,
        .y = 395,
        .w = 34,
        .h = 34
    };

    SDL_Surface* instructionSurface = TTF_RenderText_Blended(textFont, "Please do not delete the files present in the Brick Breaker", textColor);
    SDL_Surface* folderSurface = TTF_RenderText_Blended(textFont, "folder", textColor);

    if (!instructionSurface || !folderSurface) {
        printf("Failed to create instruction surface: %s\n", TTF_GetError());
    }

    SDL_Texture* instructionTexture = SDL_CreateTextureFromSurface(renderer, instructionSurface);
    SDL_Texture* folderTexture = SDL_CreateTextureFromSurface(renderer, folderSurface);
    SDL_FreeSurface(instructionSurface);
    SDL_FreeSurface(folderSurface);

    if (!instructionTexture || !folderTexture) {
        printf("Failed to create instruction texture: %s\n", SDL_GetError());
    }

    SDL_Rect instructionRect = {
        .x = 290,
        .y = 610,
        .w = instructionSurface->w,
        .h = instructionSurface->h
    };

    SDL_Rect folderRect = {
        .x = 280,
        .y = instructionRect.y + instructionRect.h + 5,
        .w = folderSurface->w,
        .h = folderSurface->h
    };

    SDL_Surface* rightArrowIconSurface = IMG_Load("resources/assets/img/icons/right-arrow.png");

    if (!rightArrowIconSurface) {
        printf("Failed to load right arrow icon image: %s\n", IMG_GetError());
    }

    SDL_Texture* rightArrowIconTexture = SDL_CreateTextureFromSurface(renderer, rightArrowIconSurface);
    SDL_FreeSurface(rightArrowIconSurface);

    if (!rightArrowIconTexture) {
        printf("Failed to create right arrow icon texture: %s\n", SDL_GetError());
    }

    SDL_Rect rightArrowIconRect1 = {
        .x = 235,
        .y = 550,
        .w = 42,
        .h = 42
    };

    SDL_Rect rightArrowIconRect2 = {
        .x = 235,
        .y = 600,
        .w = 42,
        .h = 42
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
        .y = 636,
        .w = 64,
        .h = 64
    };

    SDL_Surface* githubTextSurface = TTF_RenderText_Blended(footerFont, "Here", textColor);

    if (!githubTextSurface) {
        printf("Failed to load githubTextSurface: %s\n", IMG_GetError());
    }

    SDL_Texture* githubTextTexture = SDL_CreateTextureFromSurface(renderer, githubTextSurface);
    SDL_FreeSurface(githubTextSurface);

    if (!githubTextTexture) {
        printf("Failed to create GitHub text texture: %s\n", SDL_GetError());
    }

    SDL_Rect githubTextRect = {
        .x = githubButtonRect.x + githubButtonRect.w + 5,
        .y = githubButtonRect.y + (githubButtonRect.h - githubTextSurface->h) / 2,
        .w = githubTextSurface->w,
        .h = githubTextSurface->h
    };

    TTF_Font* bubbleFont = TTF_OpenFont("resources/assets/fonts/Indiana-Jonas-48ip.otf", 30);

    if (!bubbleFont) {
        printf("Failed to load bubbleFont: %s\n", TTF_GetError());
    }

    SDL_Surface* bubbleSurface = IMG_Load("resources/assets/img/background/bubble.png");

    if (!bubbleSurface) {
        printf("Failed to load background image: %s\n", IMG_GetError());
    }

    SDL_Texture* bubbleTexture = SDL_CreateTextureFromSurface(renderer, bubbleSurface);
    SDL_FreeSurface(bubbleSurface);

    if (!bubbleTexture) {
        printf("Failed to create bubble texture: %s\n", SDL_GetError());
    }

    SDL_Rect bubbleRect = {
        .x = 950,
        .y = 300,
        .w = 328,
        .h = 328
    };

    SDL_Surface* githubCharacterSurface = IMG_Load("resources/assets/img/icons/github-character.png");

    if (!githubCharacterSurface) {
        printf("Failed to load githubCharacterSurface: %s\n", IMG_GetError());
    }

    SDL_Texture* githubCharacterTexture = SDL_CreateTextureFromSurface(renderer, githubCharacterSurface);
    SDL_FreeSurface(githubCharacterSurface);

    if (!githubCharacterTexture) {
        printf("Failed to create githubCharacterTexture: %s\n", SDL_GetError());
    }

    SDL_Rect githubCharacterRect = {
        .x = 870,
        .y = 470,
        .w = 120,
        .h = 120
    };

    SDL_Surface* opinionTextSurface1 = TTF_RenderText_Blended(bubbleFont, "Submit your ideas", textColorBull);

    if (!opinionTextSurface1) {
        printf("Failed to load opinionTextSurface1: %s\n", IMG_GetError());
    }

    SDL_Texture* opinionTextTexture1 = SDL_CreateTextureFromSurface(renderer, opinionTextSurface1);
    SDL_FreeSurface(opinionTextSurface1);

    if (!opinionTextTexture1) {
        printf("Failed to load opinionTextTexture1: %s\n", IMG_GetError());
    }

    SDL_Rect opinionTextRect1 = {
        .x = 1080,
        .y = 390,
        .w = opinionTextSurface1->w,
        .h = opinionTextSurface1->h
    };

    SDL_Surface* opinionTextSurface2 = TTF_RenderText_Blended(bubbleFont, "and share your thoughts", textColorBull);

    if (!opinionTextSurface2) {
        printf("Failed to load opinionTextSurface2: %s\n", IMG_GetError());
    }

    SDL_Texture* opinionTextTexture2 = SDL_CreateTextureFromSurface(renderer, opinionTextSurface2);
    SDL_FreeSurface(opinionTextSurface2);

    if (!opinionTextTexture2) {
        printf("Failed to load opinionTextTexture2: %s\n", IMG_GetError());
    }

    SDL_Rect opinionTextRect2 = {
        .x = 1050,
        .y = 420,
        .w = opinionTextSurface2->w,
        .h = opinionTextSurface2->h
    };

    SDL_Surface* opinionTextSurface3 = TTF_RenderText_Blended(bubbleFont, "about the game", textColorBull);

    if (!opinionTextSurface3) {
        printf("Failed to load opinionTextSurface3: %s\n", IMG_GetError());
    }

    SDL_Texture* opinionTextTexture3 = SDL_CreateTextureFromSurface(renderer, opinionTextSurface3);
    SDL_FreeSurface(opinionTextSurface3);

    if (!opinionTextTexture3) {
        printf("Failed to load opinionTextTexture3: %s\n", IMG_GetError());
    }

    SDL_Rect opinionTextRect3 = {
        .x = 1085,
        .y = 450,
        .w = opinionTextSurface3->w,
        .h = opinionTextSurface3->h
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

                } else if (SDL_PointInRect(&mousePoint, &githubButtonRect) || SDL_PointInRect(&mousePoint, &githubTextRect)) {

                    ShellExecute(0, 0, "https://github.com/devZenta/BrickBreaker", 0, 0, SW_SHOW);
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

        SDL_RenderCopy(renderer, rule1Texture, NULL, &rule1Rect);
        SDL_RenderCopy(renderer, pinIconTexture, NULL, &pinIconRect1);
        SDL_RenderCopy(renderer, rule2Texture, NULL, &rule2Rect);
        SDL_RenderCopy(renderer, pinIconTexture, NULL, &pinIconRect2);
        SDL_RenderCopy(renderer, rule3Texture, NULL, &rule3Rect);
        SDL_RenderCopy(renderer, pinIconTexture, NULL, &pinIconRect3);
        SDL_RenderCopy(renderer, rule4Texture, NULL, &rule4Rect);
        SDL_RenderCopy(renderer, pinIconTexture, NULL, &pinIconRect4);

        SDL_RenderCopy(renderer, bubbleTexture, NULL, &bubbleRect);
        SDL_RenderCopy(renderer, githubCharacterTexture, NULL, &githubCharacterRect);
        SDL_RenderCopy(renderer, opinionTextTexture1, NULL, &opinionTextRect1);
        SDL_RenderCopy(renderer, opinionTextTexture2, NULL, &opinionTextRect2);
        SDL_RenderCopy(renderer, opinionTextTexture3, NULL, &opinionTextRect3);

        SDL_RenderCopy(renderer, followInstructionsTitleTexture, NULL, &followInstructionsTitleRect);
        SDL_RenderCopy(renderer, followInstructionsIconTexture, NULL, &followInstructionsIconRect);
        SDL_RenderCopy(renderer, doNotModifyTexture, NULL, &doNotModifyRect);
        SDL_RenderCopy(renderer, instructionTexture, NULL, &instructionRect);
        SDL_RenderCopy(renderer, rightArrowIconTexture, NULL, &rightArrowIconRect1);
        SDL_RenderCopy(renderer, folderTexture, NULL, &folderRect);
        SDL_RenderCopy(renderer, rightArrowIconTexture, NULL, &rightArrowIconRect2);

        SDL_RenderCopy(renderer, githubButtonTexture, NULL, &githubButtonRect);
        SDL_RenderCopy(renderer, githubTextTexture, NULL, &githubTextRect);

        SDL_RenderCopy(renderer, iconDevTexture, NULL, &iconDevRect);
        SDL_RenderCopy(renderer, textCreatorTexture, NULL, &textCreatorRect);

        SDL_RenderPresent(renderer);
    }
}