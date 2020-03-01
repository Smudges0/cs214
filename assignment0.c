#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int insertionSort(void *toSort, int (*comparator)(void *, void *));
int quickSort(void *toSort, int (*comparator)(void *, void *));
int numComparator(void *, void *);
int stringComparator(void *, void *);

typedef struct node
{
  char *tokenStr;
  int *tokenInt;
  int isString;
  struct node *nextNode;
  struct node *prevNode;
} Node;

Node *makeNodeStr(char *token);
Node *makeNodeInt(int token);
void *getToken(Node *node);
Node *changeHeadPtr(Node *head);
void pushNode(Node **head, Node *newNode);
void appendNode(Node **head, Node *newNode);
void printNodes(Node *aNode);
void insertNodeAfter(Node **head, Node *prevNode, Node *newNode);
void removeNode(Node **head, Node *removedNode);
void insertNodeBefore(Node **head, Node *nextNode, Node *newNode);

const int ISSTRING = 1;
const int ISNUM = 0;

int main(int argc, char *argv[])
{
  // Variables
  char *sortType = argv[1];
  char *fileName = argv[2];

  // 1. Read args from command line (sort type, file name) and set flags
  printf("Arguments: %s, %s\n\n", sortType, fileName);

  // 2. Read tokens from file, put tokens into linked list, returns list

  // 3. Chose comparator based on isString flag, set pointer to correct comparator

  // 4. Call sort with correct comparator and list, returns a new sorted linked list
  // Implement comparators
  // Research Sort algorithms and what linked lists operations we need
  // 5. Print sorted list to STDOUT

  // -------------------------------------------
  // Test calls of the linked list methods.
  //--------------------------------------------
  /*
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
*/

  // -------------------------------------------
  // Test calls for comparators
  //--------------------------------------------
  // int a = 9;
  // int b = 7;
  // int c = 7;
  // void *x = &a;
  // void *y = &b;
  // void *z = &c;

  // printf("%d : Expected value should be positive.\n", numComparator(x, y));
  // printf("%d : Expected value should be negative.\n", numComparator(y, x));
  // printf("%d : Expected value should be 0.\n", numComparator(y, z));
  // printf("\n");

  // x = "abc";
  // y = "bcd";
  // z = "abcd";
  // void *z1 = "";
  // printf("%d : Expected value should be negative.\n", stringComparator(x, y));
  // printf("%d : Expected value should be positive.\n", stringComparator(y, x));
  // printf("%d : Expected value should be 0.\n", stringComparator(x, x));
  // printf("%d : Expected value should be negative.\n", stringComparator(x, z));
  // printf("%d : Expected value should be positive.\n", stringComparator(z, x));
  // printf("%d : Expected value should be positive.\n", stringComparator(x, z1));
  // printf("%d : Expected value should be negative.\n", stringComparator(z1, x));
  // printf("%d : Expected value should be 0.\n", stringComparator(z1, z1));

  // -------------------------------------------
  // Test calls for num/string linkedLists
  //--------------------------------------------

  // Node *headNum = makeNode("1");
  // appendNode(&headNum, makeNode("2"));
  // appendNode(&headNum, makeNode("-3"));

  // Node *headString = makeNode("abc");
  // appendNode(&headString, makeNode("bcd"));
  // appendNode(&headString, makeNode("abcd"));

  // insertionSort(headNum, &numComparator);
  // insertionSort(headString, &stringComparator);
  // quickSort(headNum, &numComparator);
  // quickSort(headString, &stringComparator);

  // -------------------------------------------
  // Test calls for num/string linkedLists
  //--------------------------------------------

  Node *headNum = makeNodeInt(1);
  appendNode(&headNum, makeNodeInt(2));
  appendNode(&headNum, makeNodeInt(3));
  appendNode(&headNum, makeNodeInt(9));
  appendNode(&headNum, makeNodeInt(2));
  appendNode(&headNum, makeNodeInt(NULL));

  Node *headString = makeNodeStr("cat");
  appendNode(&headString, makeNodeStr("bird"));
  appendNode(&headString, makeNodeStr("dog"));
  appendNode(&headString, makeNodeStr(""));
  appendNode(&headString, makeNodeStr("dog"));
  appendNode(&headString, makeNodeStr("doge"));

  printf("Before Sort:\n");
  printNodes(headNum);
  insertionSort(headNum, &numComparator);
  headNum = changeHeadPtr(headNum);
  printf("After Sort:\n");
  printNodes(headNum);

  printf("Before Sort:\n");
  printNodes(headString);
  insertionSort(headString, &stringComparator);
  headString = changeHeadPtr(headString);
  printf("After Sort:\n");
  printNodes(headString);
}

// -------------------------------------------
// Sort Functions
//--------------------------------------------

int insertionSort(void *toSort, int (*comparator)(void *, void *))
{
  Node *sortedHead = NULL;  // Make second list called sortedHead
  Node *key = (Node *)toSort; // Pointer to values in original list, scan from left to right
  while (key != NULL)
  {
    Node *nextKey = key->nextNode;  // Keeps track of next value to be scanned. Previous node gets moved, so it will be lost otherwise
    Node *j; // Pointer to values in sorted list, scan from left to right to insert next value
    if (sortedHead == NULL || (comparator(getToken(sortedHead), getToken(key))) >= 0) // Checks if sorted list is empty or 
                                                                                      // if key is smaller than head
    {
      key->nextNode = sortedHead; // Insert before head
      if (sortedHead)
      {
        sortedHead->prevNode = key;
      }
      key->prevNode = NULL;
      sortedHead = key;
    }
    else
    {
      // Scans sorted list from left to right until it finds a spot to insert key
      j = sortedHead;
      while (j->nextNode != NULL && (comparator(getToken(j->nextNode), getToken(key)) < 0))
      {
        j = j->nextNode;
      }
      key->nextNode = j->nextNode;
      if (j->nextNode)
      {
        j->nextNode->prevNode = key;
      }
      j->nextNode = key;
      key->prevNode = j;
    }

    // move on to next key
    key = nextKey;
  }
}

int quickSort(void *toSort, int (*comparator)(void *, void *))
{
  Node *head = (Node *)toSort;
  printf("%d\n", comparator(getToken(head), getToken(head->nextNode)));
}

// -------------------------------------------
// Comparators
//--------------------------------------------

int numComparator(void *int1, void *int2)
{
  int x = *(int *)int1;
  int y = *(int *)int2;
  return x - y;
}

int stringComparator(void *string1, void *string2)
{
  char *x = (char *)string1;
  char *y = (char *)string2;
  int i;
  for (i = 0; x[i] != '\0' && y[i] != '\0'; i++)
  {
    if (x[i] != y[i])
    {
      break;
    }
  }
  return x[i] - y[i];
}

// -------------------------------------------
// Double-linked list
//--------------------------------------------

Node *makeNodeStr(char *token)
{
  Node *new = malloc(sizeof(Node));
  new->tokenStr = malloc(strlen(token) + 1);
  strcpy(new->tokenStr, token);
  new->isString = ISSTRING;
  new->nextNode = NULL;
  new->prevNode = NULL;
  return new;
}

Node *makeNodeInt(int token)
{
  Node *new = malloc(sizeof(Node));
  new->tokenInt = malloc(sizeof(int));
  *(new->tokenInt) = token;
  new->isString = ISNUM;
  new->nextNode = NULL;
  new->prevNode = NULL;
  return new;
}

void *getToken(Node *node)
{
  if (node->isString)
  {
    return node->tokenStr;
  }
  return node->tokenInt;
}

Node *changeHeadPtr(Node *head)
{
  while(head->prevNode != NULL)
  {
    head = head->prevNode;
  }
  return head;
}

// pushNode adds a new node at the beginning of the linked list.
void pushNode(Node **head, Node *newNode)
{
  // Pass in **head which is a pointer to a pointer so that we
  // can update the address of head here and it will update in the
  // caller.
  newNode->nextNode = *head; // newNode nextNode points to the OLD head node
  // newNode->prevNode = NULL;
  // if (*head)
  // {
  //   (*head)->prevNode = newNode;
  // }
  *head = newNode;
}

// void appendNode(Node** head, Node* newNode)
// {
//   Node **tracer = head;
//   while (*tracer)
//   {
//     tracer = &(*tracer)->nextNode;
//   }
//   newNode->nextNode = *tracer;
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
  while (aNode->nextNode) // Keep going until nextNode is NULL
  {
    aNode = aNode->nextNode;
  }
  aNode->nextNode = newNode; // set nextNode to newNode
  newNode->prevNode = aNode; // set newNode's prevNode to aNode (Old last node)
}

void insertNodeAfter(Node **head, Node *prevNode, Node *newNode)
{
  // Don't really need to pass in the head but keep the functions consistent.

  // Remember current nextNode of prevNode.  Need to insert newNode between
  // prevNode and the nextNode.

  newNode->nextNode = prevNode->nextNode; // make newNode's next node same as prevNode's
  newNode->prevNode = prevNode;           // make newNode's previous node prevNode
  prevNode->nextNode = newNode;           // make prevNode's next node newNode

  // Check if oldNextNode is not null
  if (newNode->nextNode)
  {
    newNode->nextNode->prevNode = newNode; // make next node's prevNode newNode
  }
}

void insertNodeBefore(Node **head, Node *nextNode, Node *newNode)
{
  // Check if the nextNode is the head.  If so, need to update the head.
  if (!nextNode->prevNode)
  {
    // It is the head. Update the head to newNode.
    *head = newNode; // newNode is now the head
    newNode->prevNode = NULL;
    newNode->nextNode = nextNode; // newNode's next node is now nextNode
    nextNode->prevNode = newNode; // nextNode's previous node is now the newNode
    return;
  }

  // Else, remember current prevNode of nextNode.  Need to insert newNode between
  // prevNode and the nextNode.
  newNode->nextNode = nextNode;
  newNode->prevNode = nextNode->prevNode;
  newNode->prevNode->nextNode = newNode;
  newNode->nextNode->prevNode = newNode;
}

//
void removeNode(Node **head, Node *removedNode)
{
  // Connect prevNode with the nextNode of the removed node.

  // Check if we are removing the head node.
  if (!removedNode->prevNode)
  {
    // Removing the head.  Need to update the head pointer.
    *head = removedNode->nextNode;
    // Remove the prevNode of the new head.
    if (*head)
    {
      (*head)->prevNode = NULL; // Disconnect removedNode from nextNode
      //free(removedNode);        // Free memory
    }
    removedNode->nextNode = NULL;
    return;
  }

  // Else, connect the prevNode and nextNode together
  if(removedNode->nextNode)
  {
    removedNode->nextNode->prevNode = removedNode->prevNode;
  }
  removedNode->prevNode->nextNode = removedNode->nextNode;
  removedNode->prevNode = NULL;
  removedNode->nextNode = NULL;
  //free(removedNode);
}

void printNodes(Node *aNode)
{
  if(aNode->isString)
  {
    while (aNode)
    {
      printf("%s\n", aNode->tokenStr);
      aNode = aNode->nextNode;
    }
  }
  else
  {
    while (aNode)
    {
      printf("%d\n", *(aNode->tokenInt));
      aNode = aNode->nextNode;
    }
  }
  
  
}
