#ifndef FILE_IO_H
#define FILE_IO_H

#include "game.h"

void save_game(const char *filename, Game *game);
void load_game(const char *filename, Game *game);
void list_saves();

#endif // FILE_IO_H
