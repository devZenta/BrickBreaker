//
// Created by hugog on 06/01/2025.
//

#include "data.h"
#include "menu_settings.h"

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <direct.h>

void ensure_config_directory() {

#ifdef _WIN32

    struct stat st = {0};

    if (stat("config", &st) == -1) {
        _mkdir("config");
    }
#endif
}

void save_single_setting(const char *key_to_update, int new_value) {

    ensure_config_directory();

    int difficulty = 1, volume = 1;
    FILE *file = fopen("config/settings.txt", "r");

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

    file = fopen("config/settings.txt", "w");

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

    ensure_config_directory();

    FILE *file = fopen("config/settings.txt", "r");

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

        file = fopen("config/settings.txt", "w");

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
