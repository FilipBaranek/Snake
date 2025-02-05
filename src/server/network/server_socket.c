#include "server_socket.h"

ServerSocket* server_create() 
{
  ServerSocket* server = malloc(sizeof(ServerSocket));

  server->server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server->server_fd < 0) 
  {
      server_error("Failed to create socket");
      free(server);
      return NULL;
  }

  return server;
}

bool server_addr_and_port(ServerSocket* server, int port)
{
  int opt = 1;

  if (setsockopt(server->server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
  {
    server_error("Address or port configuration failed");
    close(server->server_fd);
    free(server);
    return false;
  }
  
  server->address.sin_family = AF_INET;
  server->address.sin_addr.s_addr = INADDR_ANY;
  server->address.sin_port = htons(port);

  return true;
}

bool server_bind(ServerSocket* server) 
{
  if (bind(server->server_fd, (struct sockaddr*)&server->address, sizeof(server->address)) < 0)
  {
    server_error("Binding failed");
    return false;
  }

  return true;
}

bool server_listen(ServerSocket* server) 
{
  if (listen(server->server_fd, 3) < 0) 
  {
    server_error("Listening failed");
    return false;
  }

  printf("Server is listening...\n");
  
  return true;
}

bool server_accept(ServerSocket* server) 
{
  socklen_t addrlen = sizeof(server->address);
  int new_socket = accept(server->server_fd, (struct sockaddr*)&server->address, &addrlen);
  if (new_socket < 0) 
  {
    server_error("Accept failed");
    return false;
  }
  
  server->connected_socket = new_socket;
  
  return true;
}

Config* server_read_config(ServerSocket* server)
{
  Config* config = (Config*)malloc(sizeof(Config));
  int packets = read(server->connected_socket, config, sizeof(*config));
  if (packets < 0)
  {
    free(config);
    return NULL;
  }

  return config;
}

int server_read(ServerSocket* server)
{
  int input;
  int packets = read(server->connected_socket, &input, sizeof(input));
  if (packets < 0)
  {
    perror("Error while reading");
    return -1;
  }

  return input;
}

void server_write(ServerSocket* server, Snake* snake)
{
  int packets = write(server->connected_socket, snake, sizeof(*snake));
  if (packets < 0)
  {
    perror("Error while writing");
  }
}

void server_close(ServerSocket* server) 
{
  close(server->server_fd);
  close(server->connected_socket);
  free(server);
}

void server_error(const char* message)
{
  perror(message);
}

