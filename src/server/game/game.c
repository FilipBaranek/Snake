#include "game.h"

void server_game_config(ServerThreadData* threadData, Snake* snake, int posX, int posY)
{
  Config* config = server_read_config(threadData->server);

  int max_length = config->width * config->height;
  snake->max_length = max_length;
  snake->gameboard_width = config->width;
  snake->gameboard_height = config->height;
  snake->time = config->gametype == 1 ? config->time : 10;
  snake->score = 0;
  snake->game_end = false;
  snake->gamemode = config->gamemode;
  snake->gametype = config->gametype;
  snake->body[0].posX = posX;
  snake->body[0].posY = posY;
  snake->length = 1;
  snake->direction = DIR_RIGHT;

  if (config->gamemode == 1)
  {
    generate_obstacles(snake);
  }

  free(config);
}

void generate_obstacles(Snake* snake)
{
  for (int i = 0; i < 20; ++i)
  {
    int posX = rand() % snake->gameboard_width;
    int posY = rand() % snake->gameboard_height;
    snake->obstacles[i].posX = snake->body[0].posX == posX ? posX - 1 : posX;
    snake->obstacles[i].posY = snake->body[0].posY == posY ? posY - 1 : posY;
  }
}

void* get_input(void* threadData)
{
  ServerThreadData* td = (ServerThreadData*)threadData;  
  int direction = DIR_RIGHT;

  while (true)
  {
    direction = server_read(td->server);
    if (direction == -1)
    {
      td->game_end = true;
      break;
    }
    else if (direction == -2)
    {
      td->pause = true;
    }
    else 
    {
      if (td->pause)
      {
        td->pause = false;
        pthread_cond_signal(&td->start_moving);
        pthread_cond_signal(&td->start_counting);
      }

      switch (direction)
      {
        case DIR_RIGHT:
          move_right(td->snake);
          break;
        case DIR_LEFT:
          move_left(td->snake);
          break;
        case DIR_UP:
          move_up(td->snake);
          break;
        case DIR_DOWN:
          move_down(td->snake);
          break;
      }
    }
  }

  return NULL;
}

void* send_render_data(void* threadData)
{
  ServerThreadData* td = (ServerThreadData*)threadData;

  while (!td->game_end)
  {
    pthread_mutex_lock(&td->render_mutex);
    while (td->pause)
    {
      pthread_cond_wait(&td->start_moving, &td->render_mutex);
    }
    pthread_mutex_unlock(&td->render_mutex);
    
    bool moved = snake_move(td->snake);
    if (!moved)
    {
      td->game_end = true;
    }
    usleep(100000);
    
    server_write(td->server, td->snake);
  }

  return NULL;
}

void* stopwatch(void* threadData)
{
  ServerThreadData* td = (ServerThreadData*)threadData;

  while (!td->game_end)
  {
    pthread_mutex_lock(&td->stopwatch_mutex);
    while (td->pause)
    {
      pthread_cond_wait(&td->start_counting, &td->stopwatch_mutex);
    }
    pthread_mutex_unlock(&td->stopwatch_mutex);
    
    sleep(1);
    --td->snake->time;
  }

  return NULL;
}
