#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../../server/game/snake.h"
#include "../../config.h"


typedef struct ClientSocket {
  int client_fd;
  struct sockaddr_in server_address;
} ClientSocket;


ClientSocket* create_client();
bool client_addr_and_port(ClientSocket* client, int server_port);
bool client_connect(ClientSocket* client);
bool disconnected(const char* buffer);
void client_send_config(ClientSocket* client, Config* config);
void client_write(ClientSocket* client, int input);
Snake* client_read(ClientSocket* client);
void client_close(ClientSocket* client);
void client_error(const char* message);

#endif

