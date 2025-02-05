#include "menu.h"

void menu_print(WINDOW* menu_win, int highlight, const char* choices[], int choices_count, const char* title) {
    box(menu_win, 0, 0);
    mvwprintw(menu_win, 0, 1, "[ %s ]", title);

    for (int i = 0; i < choices_count; ++i) {
        if (i == highlight) {
            wattron(menu_win, COLOR_PAIR(2));
        } else {
            wattron(menu_win, COLOR_PAIR(1)); 
        }
        mvwprintw(menu_win, i + 2, 2, "%s", choices[i]);
        wattroff(menu_win, COLOR_PAIR(1));
        wattroff(menu_win, COLOR_PAIR(2));
    }
    wrefresh(menu_win);
}

int menu_handle_input(WINDOW* menu_win, const char* choices[], int choices_count, const char* title) {
    int highlight = 0;
    int choice = -1;
    int input;

    while (choice == -1) {
        menu_print(menu_win, highlight, choices, choices_count, title);
        input = wgetch(menu_win);

        switch (input) {
            case KEY_UP:
                if (highlight > 0)
                    highlight--;
                break;
            case KEY_DOWN:
                if (highlight < choices_count - 1)
                    highlight++;
                break;
            case ENTER:  // Enter key
                choice = highlight;
                break;
            default:
                break;
        }
    }

    return choice;
}

void menu_destroy(WINDOW *menu_win) {
    clear();
    refresh();
    delwin(menu_win);
    endwin();
}

WINDOW* menu_create(int choices_count, int win_width) {
    initscr();
    raw();
    curs_set(0);
    keypad(stdscr, TRUE);
    noecho();
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_CYAN); 

    int height = choices_count + 4; 
    int width = win_width;
    int starty = (LINES - height) / 2;
    int startx = (COLS - width) / 2;

    WINDOW* menu_win = newwin(height, width, starty, startx);
    keypad(menu_win, TRUE);

    return menu_win;
}

int run_menu() {
    const char *choices[] = {
        "   PLAY NORMAL  ",
        " PLAY TIME LIMIT",
        "      EXIT      "
    };

    int width = 20;
    int choices_count = 3;
    const char* title = "MAIN MENU";
    WINDOW* menu_win = menu_create(choices_count, width);
    int selected = menu_handle_input(menu_win, choices, choices_count, title);
    menu_destroy(menu_win);

    return selected;
}

int run_pause_menu() {
    const char *choices[] = {
        "    PLAY    ",
        "    EXIT    ",
    };
    
    int choices_count = 2;
    int width = 16;
    const char* title = "PAUSE MENU";
    WINDOW* pause_menu_win = menu_create(choices_count, width);
    int selected = menu_handle_input(pause_menu_win, choices, choices_count, title);
    menu_destroy(pause_menu_win);

    return selected;
}

int run_game_mode_menu() {
    const char *choices[] = {
        "    FREE PLAY    ",
        "    OBSTACLES    ",
    };
   
    int choices_count = 2;
    int width = 20;
    const char* title = "MAIN MENU";
    WINDOW* game_mode_menu_win = menu_create(choices_count, width);
    int selected = menu_handle_input(game_mode_menu_win, choices, choices_count, title);
    menu_destroy(game_mode_menu_win);

    return selected;
}

