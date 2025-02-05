#include "game.h"


void client_game_config(ClientThreadData* threadData, Config* config)
{
  client_send_config(threadData->client, config);
}

void* send_input(void* threadData)
{
  ClientThreadData* td = (ClientThreadData*)threadData;
  
  int last_input;
  int input = DIR_RIGHT;
  while (!td->game_end)
  {
    input = game_get_input(td->game_window);
    if (input == ESC_KEY)
    {
      client_write(td->client, -2);
      td->pause = true;
      usleep(100000);
      int pause_option = run_pause_menu();
      if (pause_option != 0)
      {
        td->game_end = true;
      }
      client_write(td->client, last_input);
      td->pause = false;
      pthread_cond_signal(&td->start_rendering);
    }
    else
    {
      last_input = input;
      client_write(td->client, input);
    }
  }
  td->game_end = true;
  
  client_write(td->client, -1);

  return NULL;
}

void* render(void* threadData)
{
  ClientThreadData* td = (ClientThreadData*)threadData;
  
  while (!td->game_end)
  {
    pthread_mutex_lock(&td->client_mutex);
    while (td->pause)
    {
      pthread_cond_wait(&td->start_rendering, &td->client_mutex);
    }
    pthread_mutex_unlock(&td->client_mutex);

    Snake* snake = client_read(td->client);
    clear();
    for (int i = 0; i < snake->length; ++i) 
    {
        mvprintw(snake->body[i].posY + 1, snake->body[i].posX + 1, "#");
    }
    
    if (snake->gamemode == 1)
    {
      for (int i = 0; i < 20; ++i) 
      {
        mvprintw(snake->obstacles[i].posY + 1, snake->obstacles[i].posX + 1, "X");
      }
    }
    mvprintw(snake->food.posY + 1, snake->food.posX + 1, "o");
    mvprintw(snake->gameboard_height + 3, 10, "SCORE: %d", snake->score);
    mvprintw(snake->gameboard_height + 3, 30, "TIMELEFT: %d", snake->time);
    
    refresh();
    
    if (snake->game_end || snake->length == 100)
    {
      td->game_end = true;
      clear();
      mvprintw((snake->gameboard_height / 2) - 2, (snake->gameboard_width / 2 ) + 7, "YOUR SCORE: %d\n", snake->score);
      mvprintw(snake->gameboard_height / 2, snake->gameboard_width / 2, "PRESS ANY KEY TO EXIT GAME\n");
      refresh();
    }
    free(snake);
  }

  return NULL;
}

