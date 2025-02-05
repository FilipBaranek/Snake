#ifndef CLIENT_H
#define CLIENT_H

#include <pthread.h>
#include "network/client_socket.h"
#include "game/game.h"
#include "../config.h"

#define PORT 44388

void run_client(Config* config);

#endif
