#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int insertionSort(void *toSort, int (*comparator)(void *, void *));
int quickSort(void *toSort, int (*comparator)(void *, void *));

typedef struct node
{
  char *token;
  struct node *nextNode;
  struct node *prevNode;
} Node;

Node *makeNode(char *token);
void pushNode(Node **head, Node *newNode);
void appendNode(Node **head, Node *newNode);
void printNodes(Node *aNode);
void insertNodeAfter(Node **head, Node *prevNode, Node *newNode);
void removeNode(Node **head, Node *removedNode);
void insertNodeBefore(Node **head, Node *nextNode, Node *newNode);

int main(int argc, char *argv[])
{
  // Variables
  char *sortType = argv[1];
  char *fileName = argv[2];

  // 1. Read args from command line (sort type, file name) and set flags
  printf("Arguments: %s, %s\n\n", sortType, fileName);

  // 2. Read tokens from file, put tokens into linked list, returns list

  // 3. Chose comparator based on tokens, set pointer to correct comparator

  // 4. Call sort with correct comparator and list, returns a new sorted linked list
  // Implement comparators
  // Research Sort algorithms and what linked lists operations we need
  // 5. Print sorted list to STDOUT

  // -------------------------------------------
  // Test calls of the linked list methods.
  //--------------------------------------------
  Node *head = NULL;
  pushNode(&head, makeNode("-First Token"));
  pushNode(&head, makeNode("-Next Token"));
  printf("Printing list head after pushNodes.  Second token is head\n");
  //printf("%s\n", head->token);
  //printf("%s\n", (head->nextNode)->token);
  printNodes(head);
  printf("\n");

  Node *head2 = NULL;
  appendNode(&head2, makeNode("-First Token"));
  Node *new1 = makeNode("-New1 Token");
  appendNode(&head2, new1);
  printf("Printing list head2 after appendNodes.  Second token is at end\n");
  printNodes(head2);
  printf("\n");

  insertNodeAfter(&head2, head2, makeNode("-Inserted Node"));
  printf("Printing list head2 after insertNodeAfter head\n");
  printNodes(head2);
  printf("\n");

  insertNodeAfter(&head2, new1, makeNode("-Inserted Node after new1"));
  printf("Printing list head2 after insertNodeAfter new1\n");
  printNodes(head2);
  printf("\n");

  // Remove middle node
  removeNode(&head2, new1);
  printf("Printing list head2 after removeNode new1\n");
  printNodes(head2);
  printf("\n");

  // Add the removed node back at the head
  insertNodeBefore(&head2, head2, new1);
  printf("Printing list head2 after insertNodeBefore head\n");
  printNodes(head2);
  printf("\n");

  // Remove head node
  removeNode(&head2, head2);
  printf("Printing list head2 after removeNode head2\n");
  printNodes(head2);
  printf("\n");

  // Remove head node
  removeNode(&head2, head2);
  printf("Printing list head2 after removeNode head2\n");
  printNodes(head2);
  printf("\n");

  // Remove head node
  removeNode(&head2, head2);
  printf("Printing list head2 after removeNode head2\n");
  printNodes(head2);
  printf("\n");

  // Remove head node
  removeNode(&head2, head2);
  printf("Printing list head2 after removeNode head2\n");
  printNodes(head2);
  printf("\n");
}

// -------------------------------------------
// Double-linked list
//--------------------------------------------

Node *makeNode(char *token)
{
  Node *new = malloc(sizeof(Node));
  new->token = malloc(strlen(token) + 1);
  strcpy(new->token, token);
  new->nextNode = NULL;
  new->prevNode = NULL;
  return new;
}

// pushNode adds a new node at the beginning of the linked list.
void pushNode(Node **head, Node *newNode)
{
  // Pass in **head which is a pointer to a pointer so that we
  // can update the address of head here and it will update in the
  // caller.
  newNode->nextNode = *head;
  *head = newNode;
}

// void appendNode(Node** head, Node* newNode)
// {
//   Node **tracer = head;
//   while (*tracer)
//   {
//     tracer = &(*tracer)->nextNode;
//   }
//   *tracer = newNode;
// }

// appendNode adds a new node at the end of the linked list.
void appendNode(Node **head, Node *newNode)
{
  // Pass in **head which is a pointer to a pointer so that we
  // can update the address of head here if necessary and it will update in the
  // caller.  Only happens if the list is empty before.
  Node *aNode = *head;
  if (!aNode)
  {
    // List is empty.  Add new node using pushNode.
    pushNode(head, newNode);
    return;
  }

  // Else find the end of the list and add the node,
  while (aNode->nextNode)
  {
    aNode = aNode->nextNode;
  }
  aNode->nextNode = newNode;
  newNode->prevNode = aNode;
}

void insertNodeAfter(Node **head, Node *prevNode, Node *newNode)
{
  // Don't really need to pass in the head but keep the functions consistent.

  // Remember current nextNode of prevNode.  Need to insert newNode between
  // prevNode and the nextNode.
  //.....

  // Check if oldNextNode is not null
  //.....
}

void insertNodeBefore(Node **head, Node *nextNode, Node *newNode)
{
  // Check if the nextNode is the head.  If so, need to update the head.
  if (!nextNode->prevNode)
  {
    // It is the head. Update the head to newNode.
    //.....
    return;
  }

  // Else, remember current prevNode of nextNode.  Need to insert newNode between
  // prevNode and the nextNode.
  //.....
}

//
void removeNode(Node **head, Node *removedNode)
{
  // Connect prevNode with the nextNode of the removed node.

  // Check if we are removing the head node.
  if (!removedNode->prevNode)
  {
    // Removing the head.  Need to update the head pointer.
    //.....

    // Remove the prevNode of the new head.
    //.....
    return;
  }

  // Else, connect the prevNode and nextNode together
  //.....
}

void printNodes(Node *aNode)
{
  while (aNode)
  {
    //.....
  }
}