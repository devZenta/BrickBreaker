//
// Created by hugog on 06/01/2025.
//

#include "data.h"
#include "menu_settings.h"

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <direct.h>
#include <time.h>

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

void difficulty_to_string(int difficulty, char *difficulty_str) {

    switch (difficulty) {

        case 1:
            strcpy(difficulty_str, "Easy");
        break;

        case 2:
            strcpy(difficulty_str, "Medium");
        break;

        case 3:
            strcpy(difficulty_str, "Hard");
        break;

        default:
            strcpy(difficulty_str, "Unknown");
        break;
    }
}

int string_to_difficulty(const char *difficulty_str) {

    if (strcmp(difficulty_str, "Easy") == 0) return 1;

    if (strcmp(difficulty_str, "Medium") == 0) return 2;

    if (strcmp(difficulty_str, "Hard") == 0) return 3;

    return -1;
}

void load_last_games(struct Game games[3], int *game_count) {

    ensure_config_directory();

    FILE *file = fopen("config/leaderboard.txt", "r");
    *game_count = 0;

    if (file != NULL) {

        char difficulty_str[DIFFICULTY_LENGTH];
        while (fscanf(file, "%d %49s %19[^\n]",
                      &games[*game_count].score,
                      difficulty_str,
                      games[*game_count].date) == 3) {

            games[*game_count].difficulty = string_to_difficulty(difficulty_str);
            (*game_count)++;

            if (*game_count >= 3) break;
                      }

        fclose(file);
    }
}

void save_last_games(struct Game games[3], int game_count) {

    ensure_config_directory();

    FILE *file = fopen("config/leaderboard.txt", "w");

    if (file != NULL) {

        char difficulty_str[DIFFICULTY_LENGTH];

        for (int i = 0; i < game_count; i++) {

            difficulty_to_string(games[i].difficulty, difficulty_str);
            fprintf(file, "%d %s %s\n", games[i].score, difficulty_str, games[i].date);

        }

        fclose(file);

    } else {

        printf("Error: Unable to save leaderboard data.\n");

    }
}

void add_game(struct Game new_game) {

    struct Game games[3];
    int game_count;

    load_last_games(games, &game_count);

    if (game_count < 3) {

        games[game_count] = new_game;
        game_count++;

    } else {

        for (int i = 1; i < 3; i++) {

            games[i - 1] = games[i];

        }

        games[2] = new_game;
    }

    save_last_games(games, game_count);
}

void get_current_datetime(char *buffer, size_t buffer_size) {

    time_t now = time(NULL);
    struct tm *timeinfo = localtime(&now);
    strftime(buffer, buffer_size, "%Y-%m-%d %H:%M:%S", timeinfo);
}
