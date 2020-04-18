#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

#include <pthread.h>

int errorCheck(int status, char *message);          // Error handling function
void *handleSendThread(void *readThreadArgsStruct); // Function to call send()

struct readThreadArgs // Structure to hold arguments for read()
{
  int socket, flag, messageSize;
  char *message;
};

int main(int argc, char *argv[])
{

  int serverSocket, clientSocket, addrSize;
  struct sockaddr_in serverAddr, clientAddr;

  // serverSocket = socket(AF_INET, SOCK_STREAM, 0); // create socket with IPV4 (AF_INET), TCP (SOCK_STREAM), and protocol (0))
  errorCheck(serverSocket = socket(AF_INET, SOCK_STREAM, 0), "Error: failed to create socket.\n");

  // Set up address for server socket
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(5000);       // htons converts int IP address into correct format
  serverAddr.sin_addr.s_addr = INADDR_ANY; // INADDR_ANY connects to local IP, shortcut for 0.0.0.0

  // bind(serverSocket, (struct sockaddr *)&server, sizeof(server));
  errorCheck(bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)), "Error: failed to bind socket.\n");

  // listen(serverSocket, 10); // Number is for backlog of connection requests
  errorCheck(listen(serverSocket, 10), "Error: failed to listen on socket.\n");

  addrSize = sizeof(struct sockaddr_in);                                                            // set size of address for clientSocket
  struct readThreadArgs *readArgs = (struct readThreadArgs *)malloc(sizeof(struct readThreadArgs)); // create a readThreadArgs struct to hold our arguments for read()
  readArgs->flag = 0;
  char message[256] = "Hello!";
  readArgs->message = message;
  readArgs->messageSize = sizeof(message);

  while (1) // Keep Listening for connections forever
  {
    printf("Waiting for connections...\n");

    // clientSocket = accept(serverSocket, NULL, NULL); // Null fields are for structs that contain address and size of address of client
    errorCheck(clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, (socklen_t *)&addrSize), "Error: failed to accept connection.\n");
    printf("Connected!\n");

    pthread_t threadID;              // create a thread object
    readArgs->socket = clientSocket; // Setting readArgs

    int *socketPointer = malloc(sizeof(int));
    *socketPointer = clientSocket;

    // Generally, we would want to malloc and make a pointer to these arguments, so the different threads can't mess with eachothers args
    // In this example, we never change them so it's fine.

    pthread_create(&threadID, NULL, handleSendThread, /*(void *)readArgs*/ (void *)socketPointer); // Create a new thread, passing it our threadID, NULL for default atrubutes, our function, and it's args
    // send(clientSocket, message, sizeof(message), 0);
    // pthread_join(threadID, NULL);
    printf("Outside thread.\n");
    // printf("Closing connection.\n");
    // close(clientSocket);
    // printf("clientSocket closed.\n");
  }

  close(serverSocket);

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

void *handleSendThread(/*void *readThreadArgsStruct*/ void *socketPointer)
{
  // Sending Response to Client
  // printf("Inside thread.\n");
  // struct readThreadArgs *argsStruct = readThreadArgsStruct;
  // printf("Sending message: %s\n", argsStruct->message);
  // send(argsStruct->socket, argsStruct->message, argsStruct->messageSize, argsStruct->flag);
  // // printf("Thread done, leaving...\n");
  // printf("Closing connection inside thread...\n");
  // close(argsStruct->socket);
  // printf("clientSocket closed. Leaving thread...\n");

  // Recieving response from client | testing multithreading
  char clientMessage[256];
  char serverMessage[256] = "Goodbye!";
  int clientSocket = *(int *)socketPointer;
  free(socketPointer);
  recv(clientSocket, &clientMessage, sizeof(clientMessage), 0);
  for (int i = 0; i < 10; i++)
  {
    printf("Client responded with: %s\n", clientMessage);
    sleep(1);
  }
  printf("Sending: %s\n", serverMessage);
  send(clientSocket, serverMessage, sizeof(serverMessage), 0);
  return NULL;
}