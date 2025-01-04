//
// Created by hugog on 04/01/2025.
//

#include "utils.h"
#include <stdio.h>
#include <string.h>

void save_single_setting(const char *key_to_update, int new_value) {

    int difficulty = 1, volume = 1;
    FILE *file = fopen("settings.txt", "r");

    if (file != NULL) {

        char key[20];
        int value;

        while (fscanf(file, "%[^=]=%d\n", key, &value) == 2) {

            if (strcmp(key, "difficulty") == 0) {

                difficulty = value;

            } else if (strcmp(key, "volume") == 0) {

                volume = value;
            }
        }

        fclose(file);

    } else {

        printf("File not found. Default settings used.\n");

    }

    if (strcmp(key_to_update, "difficulty") == 0) {

        difficulty = new_value;
        printf("Difficulty updated : %d\n", difficulty);

    } else if (strcmp(key_to_update, "volume") == 0) {

        volume = new_value;
        printf("Volume updated : %s\n", volume ? "ON" : "OFF");

    } else {

        printf("Error: Key unknown : %s\n", key_to_update);
        return;

    }

    file = fopen("settings.txt", "w");

    if (file != NULL) {

        fprintf(file, "difficulty=%d\n", difficulty);
        fprintf(file, "volume=%d\n", volume);
        fclose(file);
        printf("Saved parameters.\n");

    } else {

        printf("Error: Unable to save in settings.txt.\n");

    }
}

void load_settings(int *difficulty, int *volume) {

    FILE *file = fopen("settings.txt", "r");

    if (file != NULL) {

        char key[20];
        int value;

        while (fscanf(file, "%[^=]=%d\n", key, &value) == 2) {

            if (strcmp(key, "difficulty") == 0) {

                *difficulty = value;

            } else if (strcmp(key, "volume") == 0) {

                *volume = value;
            }
        }

        fclose(file);
        printf("Settings loaded from settings.txt : difficulty=%d, volume=%d\n", *difficulty, *volume);

    } else {

        *difficulty = 1;
        *volume = 1;

        printf("File not found. Creation of settings.txt with default parameters...\n");

        file = fopen("settings.txt", "w");

        if (file != NULL) {

            fprintf(file, "difficulty=%d\n", *difficulty);
            fprintf(file, "volume=%d\n", *volume);
            fclose(file);
            printf("Default settings saved in settings.txt.\n");

        } else {

            printf("Error: Unable to create settings.txt.\n");

        }
    }
}