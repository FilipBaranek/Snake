#include "client.h"


void run_client(Config* config)
{
  ClientSocket* client = create_client();
  if (!client_addr_and_port(client, PORT))
  {
    client_close(client);
    exit(EXIT_FAILURE);
  }
  if (!client_connect(client))
  {
    client_close(client);
    exit(EXIT_FAILURE);
  }
  
  WINDOW* game_window;
  game_init(&game_window, config);
  
  pthread_t input_t;
  pthread_t render_t;

  ClientThreadData td;
  td.client = client;
  td.game_window = game_window;
  td.game_end = false;
  td.pause = false;

  client_game_config(&td, config);
    
  pthread_mutex_init(&td.client_mutex, NULL);
  pthread_cond_init(&td.start_rendering, NULL);
  pthread_create(&input_t, NULL, send_input, (void*)&td);
  pthread_create(&render_t, NULL, render, (void*)&td);
  pthread_join(input_t, NULL);
  pthread_join(render_t, NULL);
  pthread_mutex_destroy(&td.client_mutex);
  pthread_cond_destroy(&td.start_rendering);
  
  game_destroy(game_window);

  printf("DISCONNECTING...\n");
  client_close(client);
}
