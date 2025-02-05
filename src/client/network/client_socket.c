#include "client_socket.h"



ClientSocket* create_client()
{
  return (ClientSocket*)malloc(sizeof(ClientSocket));
}

bool client_addr_and_port(ClientSocket* client, int server_port)
{
  client->client_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (client->client_fd < 0)
  {
    client_error("Address or port configuration failer");
    return false;
  }
  
  client->server_address.sin_family = AF_INET;
  client->server_address.sin_port = htons(server_port);

  if (inet_pton(AF_INET, "127.0.0.1", &client->server_address.sin_addr) <= 0)
  {
    perror("Invalid address / Address not supported\n");
    return false;
  }

  return true;
}

bool client_connect(ClientSocket* client)
{
  int connected = connect(client->client_fd, (struct sockaddr*)&client->server_address, sizeof(client->server_address));
  if (connected < 0)
  {
    client_error("Failed to connect");
    return false;
  }
  
  printf("Connected\n");
  return true;
}

bool disconnected(const char* buffer)
{
  char* disconnect_command = "disconnect";
  int disconnect = strncmp(disconnect_command, buffer, strlen(disconnect_command));
  if (disconnect == 0)
  {
    printf("Disconnected\n");
    return true;
  }

  return false;
}

void client_send_config(ClientSocket* client, Config* config)
{
  int packets = write(client->client_fd, config, sizeof(*config));
  if (packets < 0)
  {
    perror("Error during configuration");
  }
}

void client_write(ClientSocket* client, int input)
{
  int packets = write(client->client_fd, &input, sizeof(input));
  if (packets < 0)
  {
    perror("Error while writing");
  }
}

Snake* client_read(ClientSocket* client)
{ 
  Snake* snake = (Snake*)malloc(sizeof(Snake));

  int packets = read(client->client_fd, snake, sizeof(*snake));
  if (packets < 0)
  {
    perror("Error while reading");
    free(snake);
    return NULL;
  }
  return snake;
}

void client_close(ClientSocket* client)
{
  close(client->client_fd);
  free(client);
}

void client_error(const char* message)
{
  perror(message);
}

