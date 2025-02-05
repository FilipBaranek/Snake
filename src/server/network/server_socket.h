#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdbool.h>
#include "../game/snake.h"
#include "../../config.h"


typedef struct ServerSocket {
  int server_fd;
  int connected_socket;
  struct sockaddr_in address;
} ServerSocket;

ServerSocket* server_create();
bool server_addr_and_port(ServerSocket* server, int port);
bool server_bind(ServerSocket* server);
bool server_listen(ServerSocket* server);
bool server_accept(ServerSocket* server);
void server_write(ServerSocket* server, Snake* snake);
Config* server_read_config(ServerSocket* server);
int server_read(ServerSocket* server);
void server_close(ServerSocket* server);
void server_error(const char* message);

#endif

