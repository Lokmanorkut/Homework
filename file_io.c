#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "file_io.h"

void save_game(const char *filename, Game *game) {
    char filepath[100];
    snprintf(filepath, sizeof(filepath), "%s.sav", filename);

    FILE *file = fopen(filepath, "wb");
    if (!file) {
        printf("Error: Could not save the game.\n");
        return;
    }

    fwrite(game, sizeof(Game), 1, file);
    fclose(file);
    printf("Game saved as: %s\n", filepath);
}

void load_game(const char *filename, Game *game) {
    char filepath[100];
    snprintf(filepath, sizeof(filepath), "%s.sav", filename);

    FILE *file = fopen(filepath, "rb");
    if (!file) {
        printf("Error: Save file '%s' not found.\n", filepath);
        return;
    }

    fread(game, sizeof(Game), 1, file);
    fclose(file);
    printf("Game loaded from: %s\n", filepath);
}

void list_saves() {
    DIR *dir = opendir(".");
    struct dirent *entry;

    if (!dir) {
        printf("Error: Could not open the directory.\n");
        return;
    }

    printf("Available saves:\n");
    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, ".sav")) {
            printf("- %s\n", entry->d_name);
        }
    }
    closedir(dir);
}
