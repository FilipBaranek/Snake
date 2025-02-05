#include "game_window.h"


void game_init(WINDOW** game_window, Config* config)
{
  initscr();
  cbreak();
  noecho();
  curs_set(0);

  int height = config->height + 2; 
  int width = config->width + 2; 
  int start_y = 0;
  int start_x = 0;

  *game_window = newwin(height, width, start_y, start_x);
  keypad(*game_window, TRUE);

  wrefresh(*game_window);
}

int game_get_input(WINDOW* game_window)
{
  switch (wgetch(game_window))
  {
    case KEY_UP:
      return DIR_UP;
    case KEY_DOWN:
      return DIR_DOWN;
    case KEY_LEFT:
      return DIR_LEFT;
    case KEY_RIGHT:
      return DIR_RIGHT;
    case ESC_KEY:
      return ESC_KEY;
    default:
      return -1;
  }
}

void game_destroy(WINDOW* game_window)
{
  clear();
  refresh();
  delwin(game_window);
  endwin();
}
