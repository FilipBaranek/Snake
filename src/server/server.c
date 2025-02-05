#include "server.h"

void run_server()
{
  ServerSocket* server = server_create();
  
  server_addr_and_port(server, PORT);

  if (!server_bind(server))
  {
    server_close(server);
    exit(EXIT_FAILURE);
  }

  if (!server_listen(server))
  {
    server_close(server);
    exit(EXIT_FAILURE);
  }

  if (!server_accept(server))
  {
    server_close(server);
    exit(EXIT_FAILURE);
  }
  
  pthread_t input_read;
  pthread_t render_output;
  pthread_t watch_time;

  Snake* snake = create_snake();

  ServerThreadData td;
  td.server = server;
  td.snake = snake;
  td.game_end = false;
  td.pause = false;
  
  server_game_config(&td, snake, 5, 5);
  srand(time(NULL));

  pthread_mutex_init(&td.render_mutex, NULL);
  pthread_mutex_init(&td.stopwatch_mutex, NULL);
  pthread_cond_init(&td.start_moving, NULL);
  pthread_cond_init(&td.start_counting, NULL);
  pthread_create(&input_read, NULL, get_input, (void*)&td);
  pthread_create(&render_output, NULL, send_render_data, (void*)&td);
  pthread_create(&watch_time, NULL, stopwatch, (void*)&td);
  pthread_join(input_read, NULL);
  pthread_join(render_output, NULL);
  pthread_join(watch_time, NULL);
  pthread_cond_destroy(&td.start_moving);
  pthread_cond_destroy(&td.start_counting);
  pthread_mutex_destroy(&td.render_mutex);
  pthread_mutex_destroy(&td.stopwatch_mutex);

  snake_destroy(snake);

  printf("CLOSING SERVER..\n");
  sleep(3);

  server_close(server);
}

