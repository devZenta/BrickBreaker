//
// Created by hugog on 04/01/2025.
//

#ifndef UTILS_H
#define UTILS_H

void ensure_config_directory();

void save_single_setting(const char *key_to_update, int new_value);

void load_settings(int *difficulty, int *volume);

#endif //UTILS_H
