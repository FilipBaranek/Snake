#ifndef SERVER_GAME_H
#define SERVER_GAME_H

#include <pthread.h>
#include "../network/server_socket.h"

typedef struct ServerThreadData
{
  Snake* snake;
  ServerSocket* server;
  bool game_end;
  bool pause;
  pthread_mutex_t render_mutex;
  pthread_mutex_t stopwatch_mutex;
  pthread_cond_t start_moving;
  pthread_cond_t start_counting;
} ServerThreadData;

void server_game_config(ServerThreadData* threadData, Snake* snake, int posX, int posY);
void generate_obstacles(Snake* snake);
void* get_input(void* threadData);
void* send_render_data(void* threadData);
void* stopwatch(void* threadData);

#endif
