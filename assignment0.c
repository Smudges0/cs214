#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int insertionSort(void* toSort, int (*comparator)(void*, void*));
int quickSort(void* toSort, int (*comparator)(void*, void*));
void doNothing(char* test);

typedef struct node
{
  char *token;
  struct node *nextNode;
} Node;
Node *makeNode(char *token);

int main(int argc, char *argv[])
{
  // Variables
  char* sortType = argv[1];
  char* fileName = argv[2];

  


  // 1. Read args from command line (sort type, file name) and set flags

  // 2. Read tokens from file, put tokens into linked list, returns list

  // 3. Chose comparator based on tokens, set pointer to correct comparator

  // 4. Call sort with correct comparator and list, returns a new sorted linked list

  // 5. Print sorted list to STDOUT



  // -------------------------------------------
  Node *head = NULL;
  Node *new = makeNode("Test Token");
  printf("%s, %s\n", sortType, fileName);

}

Node *makeNode(char *token)
{
  Node *new = malloc(sizeof(Node));
  new->token = malloc(strlen(token) + 1);
  strcpy(new->token, token);
  new->nextNode = NULL; // This will be set on insertion
  return new;
}