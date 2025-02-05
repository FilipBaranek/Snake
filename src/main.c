#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "client/menu/menu.h"
#include "client/client.h"
#include "server/server.h"
#include "config.h"


int main(int argc, char *argv[])
{
  int gametype_choice =  run_menu();
  if (gametype_choice > 1)
  {
    return EXIT_SUCCESS;
  }
  
  int gamemode_choice = run_game_mode_menu();
  int width = 0;
  int height = 0;
  int time;
  while (width < 10 || height < 10)
  {
    printf("Zadajte šírku hracej plochy (minimum je 10):\n");
    scanf("%d", &width);
    printf("Zadajte výšku hracej plochy (minimum je 10):\n");
    scanf("%d", &height);
  }

  if (gametype_choice == 1)
  {
    printf("Zadajte časový limit hry v sekundách\n");
    scanf("%d", &time);
  }
  else 
  {
    time = -1;
  } 

  Config config;
  config.gametype = gametype_choice;
  config.gamemode = gamemode_choice;
  config.width = width;
  config.height = height;
  config.time = time;

  int process_id = fork();

  if (process_id == 0)
  {
    run_server();
  }
  else 
  {
    sleep(1);
    run_client(&config);
  }
  
  return EXIT_SUCCESS;
}
