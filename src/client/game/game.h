#ifndef CLIENT_GAME_H
#define CLIENT_GAME_H

#include <pthread.h>
#include "game_window.h"
#include "../network/client_socket.h"
#include "../menu/menu.h"
#include "../../config.h"


typedef struct ClientThreadData
{
  ClientSocket* client;
  WINDOW* game_window;
  bool game_end;
  bool pause;
  pthread_mutex_t client_mutex;
  pthread_cond_t start_rendering;
} ClientThreadData;

void client_game_config(ClientThreadData* threadData, Config* config);
void* send_input(void* threadData);
void* render(void* threadData);

#endif
