#define SDL_MAIN_HANDLED

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include <stdio.h>

#include "menu.h"

int main(int argc, char **argv) {

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    if (0 != SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr,"SDL_Init Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    window = SDL_CreateWindow("Brick Breaker by zenta . (Hugo Ghesquier)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        fprintf(stderr,"SDL_CreateWindow Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL) {
        fprintf(stderr,"SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Surface* cursorSurface = SDL_LoadBMP("resources/assets/img/other/cursor.bmp");

    if (!cursorSurface) {
        printf("Erreur de chargement du curseur : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Cursor* customCursor = SDL_CreateColorCursor(cursorSurface, 0, 0);

    SDL_SetCursor(customCursor);

    displayMenu(renderer);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}