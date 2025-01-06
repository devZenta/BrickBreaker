//
// Created by hugog on 06/01/2025.
//

#ifndef DATA_H
#define DATA_H

void ensure_config_directory();

void save_single_setting(const char *key_to_update, int new_value);

void load_settings(int *difficulty, int *volume);

#endif //DATA_H
