#ifndef GAME_H
#define GAME_H

#include <ncurses.h>
#include "../../config.h"

#define ESC_KEY 27
#define DIR_LEFT 0
#define DIR_RIGHT 1
#define DIR_UP 2
#define DIR_DOWN 3

void game_init(WINDOW** game_window, Config* config);
int game_get_input(WINDOW* game_window);
void game_destroy(WINDOW* game_window);

#endif
