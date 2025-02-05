#include "snake.h"

Snake* create_snake()
{
  Snake* snake = (Snake*)malloc(sizeof(Snake));
  
  return snake;
}

void snake_destroy(Snake* snake)
{
  free(snake);
}

void generate_food(Snake* snake)
{
  snake->food.posX = rand() % snake->gameboard_width;
  snake->food.posY = rand() % snake->gameboard_height;
  
    
  if (snake->gamemode == 1)
  {
    for (int i = 0; i < 20; ++i)
    {
      if (snake->food.posX == snake->obstacles[i].posX && snake->food.posY == snake->obstacles[i].posY)
      {
        generate_food(snake);
      }
      break;
    }
  }
}

bool colision(Snake* snake)
{
  int colisionX = -1;
  int colisionY = -1;

  switch (snake->direction)
  {
    case DIR_RIGHT:
      colisionX = snake->body[0].posX + 1;
      colisionY = snake->body[0].posY;
      break;
    case DIR_LEFT:
      colisionX = snake->body[0].posX - 1;
      colisionY = snake->body[0].posY;
      break;
    case DIR_UP:
      colisionX = snake->body[0].posX;
      colisionY = snake->body[0].posY - 1;
      break;
    case DIR_DOWN:
      colisionX = snake->body[0].posX;
      colisionY = snake->body[0].posY + 1;
      break;
  }
  
  for (int i = 0; i < snake->length; ++i)
  {
    if (snake->body[i].posX == colisionX && snake->body[i].posY == colisionY)
    {
      return true;
    }
  }
  
  if (snake->gamemode == 1)
  {
    for (int i = 0; i < 20; ++i)
    {
      if (snake->obstacles[i].posX == colisionX && snake->obstacles[i].posY == colisionY)
      {
        return true;
      }
    }
  }

  return false;
}

bool food(Snake* snake)
{
  if (snake->body[0].posX == snake->food.posX && snake->body[0].posY == snake->food.posY)
  {
    if (snake->gametype == 0)
    {
      snake->time = 10;
    }
    ++snake->score;

    return true;
  }

  return false;
}

bool snake_move(Snake* snake)
{
  if (snake->time <= 0)
  {
    snake->game_end = true;
    return false;
  }
  if (colision(snake))
  {
    snake->game_end = true;
    return false;
  }
  if (food(snake))
  {
    eat(snake);
    generate_food(snake);
  }


  for (int i = snake->length - 1; i > 0; --i)
  {
    snake->body[i].posX = snake->body[i - 1].posX;
    snake->body[i].posY = snake->body[i - 1].posY;
  }
  
  switch (snake->direction)
  {
    case DIR_RIGHT:
      ++snake->body[0].posX;
      break;
    case DIR_LEFT:
      --snake->body[0].posX;
      break;
    case DIR_UP:
      --snake->body[0].posY;
      break;
    case DIR_DOWN:
      ++snake->body[0].posY;
      break;
  }
  
  if (snake->body[0].posX < 0)
  {
    snake->body[0].posX = snake->gameboard_width - 1;
  }
  else if (snake->body[0].posX >= snake->gameboard_width)
  {
    snake->body[0].posX = 0;
  }
  else if (snake->body[0].posY < 0)
  {
    snake->body[0].posY = snake->gameboard_height - 1;
  }
  else if (snake->body[0].posY >= snake->gameboard_height)
  {
    snake->body[0].posY = 0;
  }
  
  return true;
}

void move_right(Snake* snake)
{
  snake->direction = snake->direction == DIR_LEFT ? DIR_LEFT : DIR_RIGHT;
}

void move_left(Snake* snake)
{
  snake->direction = snake->direction == DIR_RIGHT ? DIR_RIGHT : DIR_LEFT;
}

void move_up(Snake* snake)
{
  snake->direction = snake->direction == DIR_DOWN ? DIR_DOWN : DIR_UP;
}

void move_down(Snake* snake)
{
  snake->direction = snake->direction == DIR_UP ? DIR_UP : DIR_DOWN;
}

void eat(Snake* snake)
{
  ++snake->length;
}

