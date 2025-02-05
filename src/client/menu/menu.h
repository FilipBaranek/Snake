#ifndef MENU_H
#define MENU_H

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#define ENTER 10


WINDOW* menu_create(int choices_count, int width);
void menu_print(WINDOW *menu_win, int highlight, const char *choices[], int choices_count, const char* title);
int menu_handle_input(WINDOW *menu_win, const char *choices[], int choices_count, const char* title);
void menu_destroy(WINDOW *menu_win);
int run_menu();
int run_pause_menu();
int run_game_mode_menu();

#endif
