//
// Created by hugog on 06/01/2025.
//

#ifndef DATA_H
#define DATA_H

#include <time.h>

#define DIFFICULTY_LENGTH 50
#define DATE_LENGTH 20

struct Game {
    int score;
    int difficulty;
    char date[DATE_LENGTH];
};

void ensure_config_directory();

void save_single_setting(const char *key_to_update, int new_value);

void load_settings(int *difficulty, int *volume);

void ensure_config_directory();

void difficulty_to_string(int difficulty, char *difficulty_str);

int string_to_difficulty(const char *difficulty_str);

void load_last_games(struct Game games[3], int *game_count);

void save_last_games(struct Game games[3], int game_count);

void add_game(struct Game new_game);

void get_current_datetime(char *buffer, size_t buffer_size);

#endif //DATA_H
