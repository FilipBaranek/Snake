#ifndef SERVER_H
#define SERVER_H

#include <pthread.h>
#include "network/server_socket.h"
#include "game/game.h"

#define PORT 44388

void run_server();

#endif
