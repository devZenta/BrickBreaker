//
// Created by hugog on 04/01/2025.
//

#include "utils.h"

#include <stdbool.h>

bool check_collision(SDL_Rect *a, SDL_Rect *b) {
    return (a->x < b->x + b->w && a->x + a->w > b->x &&
            a->y < b->y + b->h && a->y + a->h > b->y);
}
