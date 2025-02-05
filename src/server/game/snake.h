#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define DIR_LEFT 0
#define DIR_RIGHT 1
#define DIR_UP 2
#define DIR_DOWN 3

typedef struct Position
{
  int posX;
  int posY;
} Position;

typedef struct Snake
{
  bool game_end;
  int length;
  int direction;
  int max_length;
  int time;
  int score;
  int gamemode;
  int gametype;
  int gameboard_width;
  int gameboard_height;
  Position obstacles[20];
  Position body[100];
  Position food;
} Snake;

Snake* create_snake();
void snake_destroy(Snake* snake);
bool colision(Snake* snake);
bool food(Snake* snake);
bool snake_move(Snake* snake);
void move_right(Snake* snake);
void move_left(Snake* snake);
void move_up(Snake* snake);
void move_down(Snake* snake);
void eat(Snake* snake);

