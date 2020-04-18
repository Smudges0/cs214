#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

int errorCheck(int status, char *message);

int main(int argc, char *argv[])
{
  int clientSocket; // socket descriptor
  struct sockaddr_in server;

  // clientSocket = socket(AF_INET, SOCK_STREAM, 0); // create socket with IPV4 (AF_INET), TCP (SOCK_STREAM), and protocol (0))

  errorCheck(clientSocket = socket(AF_INET, SOCK_STREAM, 0), "Error: Failed to create socket.\n");

  // Set up address for socket
  server.sin_family = AF_INET;
  server.sin_port = htons(5000);       // htons converts int IP address into correct format
  server.sin_addr.s_addr = INADDR_ANY; // INADDR_ANY connects to local IP, shortcut for 0.0.0.0

  // int connectStatus = connect(clientSocket, (struct sockaddr *)&server, sizeof(server));
  int connectStatus;
  errorCheck(connectStatus = connect(clientSocket, (struct sockaddr *)&server, sizeof(server)), "Error: could not connect to server.\n");

  // Send message to server | test multithreading
  char message[256];
  strcpy(message, argv[1]);
  printf("Sending: %s\n", message);
  send(clientSocket, message, sizeof(message), 0);
  printf("Sent. Waiting for response\n");

  // Recieve message from server
  char response[256];
  recv(clientSocket, &response, sizeof(response), 0);

  printf("Server responded with: %s\n", response);

  // Close socket
  close(clientSocket);
  return 0;
}

int errorCheck(int status, char *message)
{
  if (status == -1)
  {
    perror(message);
    exit(1);
  }
  return status;
}