#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

int insertionSort(void *toSort, int (*comparator)(void *, void *));
int quickSort(void *toSort, int (*comparator)(void *, void *));

int numComparator(void *, void *);
int stringComparator(void *, void *);
void setFileType(char *token);
//void swap(char **s1, char **s2);




typedef struct node
{
  char *tokenStr;
  int *tokenInt;
  int isString;
  struct node *nextNode;
  struct node *prevNode;
} Node;

void getNumList(Node **headRef);
void readFile(char *fileName, Node **headRef);
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
void _quickSort(Node* h, Node* l,int (*comparator)(void *, void *));
Node *partition(Node *h, Node *l,int (*comparator)(void *, void *));


const int ISSTRING = 1;
const int ISNUM = 0;
static int hasAlpha = 0;
static int hasNumber = 0;

int main(int argc, char *argv[])
{
  // Variables
  char *sortType = argv[1];
  char *fileName = argv[2];

  // 1. Read args from command line (sort type, file name) and set flags
  printf("Arguments: %s, %s\n\n", sortType, fileName);

  // 2. Read tokens from file, put tokens into linked list, returns list
  Node *headRef = NULL;
  readFile(fileName, &headRef);
  printf("Before sort:\n");
  printNodes(headRef);

  // 3. Chose comparator based on isString flag, set pointer to correct comparator
  void *comparator = NULL;
  if (hasAlpha)
  {
    comparator = &stringComparator;
  }
  else comparator = &numComparator;

  // 4. Call sort with correct comparator and list, returns a new sorted linked list
  if (sortType[0] == '-' && sortType[1] == 'i')
  {
    insertionSort(headRef, comparator);
  }
  else if (sortType[0] == '-' && sortType[1] == 'q')
  {
    quickSort(headRef, comparator);
  }
  else
  {
    fprintf(stderr, "Invalid sort type: %s.\n", sortType);
    exit(1);
  }

  headRef = changeHeadPtr(headRef);
  printf("After sort:\n");
  printNodes(headRef);
  
  
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

// -------------------------------------------
// Read from File
//--------------------------------------------

void readFile(char *fileName, Node **headRef)
{
  int emptyFile = 1;
  // open and read a file
  int fd = open(fileName, O_RDONLY);
  if (fd == -1)
  {
    printf("Error Number % d\n", errno);
    exit(1);
  }

  // Buffer to hold a single complete token read from file.
  int tokenBufSize = 10;
  char *tokenBuf = malloc(tokenBufSize);
  if (tokenBuf == NULL)
  {
    fprintf(stderr, "out of memory for tokenBuf\n");
    exit(1);
  }

  // Buffer to hold data read from file.  May not be a complete token.
  // (Reading 1 char at a time for simplicity)
  int readBufSize = 1;
  char *readBuf = malloc(readBufSize);
  if (readBuf == NULL)
  {
    fprintf(stderr, "out of memory for readBuf\n");
    exit(1);
  }

  int bytes_read;
  int tokenLength = 0;

  // Start reading the file
  //while ((bytes_read = read(fd, readBuf, readBufSize) > 0))
  while (1)
  {
    bytes_read = read(fd, readBuf, readBufSize);

    if (bytes_read == EAGAIN)
    {
      // Non-blocking IO file which is not ready with data to read.
      // Try again later.
      sleep(1);
      continue;
    }
    else if (bytes_read < 0)
    {
      perror("File Read Error");
      exit(1);
    }
    else if (bytes_read == 0)
    {
      //printf("\n\nEnd of file reached. tokenLength: %d\n", tokenLength);
      break;
    }

    if (tokenLength >= tokenBufSize - 1)
    {
      /* time to make it bigger */
      tokenBufSize += 10;
      printf("-----Growing %d-----", tokenBufSize);
      tokenBuf = realloc(tokenBuf, tokenBufSize);
      if (tokenBuf == NULL)
      {
        fprintf(stderr, "out of memory for tokenBuf realloc\n");
        exit(1);
      }
    }

    printf("%.*s", bytes_read, readBuf);
    // Actually reading one char at a time....
    char aChar = readBuf[0];
    // If end of the token is reached, check if it is a valid number or string token.
    if (aChar == ',')
    {
      emptyFile = 0;  // Differentiate between empty file and empty token at end of file

      // Ignore empty tokens
      if (tokenLength == 0)
      {
        continue;
      }

      tokenBuf[tokenLength++] = '\0'; // Add string delimiter
      printf("\nFound token: [%s]\n", tokenBuf);

      // Check if token is number or string or other illegal

      appendNode(headRef, makeNodeStr(tokenBuf)); // Store token as a string in a linked list

      setFileType(tokenBuf);
      
      // Reset token pointer to 0 to read next token
      tokenLength = 0;
    }
    else
    {
      // Keep reading but ignore whitespace
      if (!isspace(aChar))
      {
        tokenBuf[tokenLength++] = aChar;
      }
    }
  } // End of file read

  // Check if there is still a token left without the final ','
  if (tokenLength > 0)
  {
    tokenBuf[tokenLength] = '\0';
    appendNode(headRef, makeNodeStr(tokenBuf));

    setFileType(tokenBuf);
    printf("\n\nEnd of file: tokenLength = %d  Leftover token [%s]", tokenLength, tokenBuf);
    
  }
  else
  {
    if (emptyFile)
    {
      fprintf(stderr, "File is empty.\n");
    }
    else
    {
      fprintf(stderr, "File ends with empty token.\n");
    }
  }
  if (hasNumber)
  {
    getNumList(headRef);
  }
  printf("\n\n\n");
}

void setFileType(char *token)
{
  // hasAlpha = 0;
  // hasNumber = 0;
  int i;
  for (i = 0; i < strlen(token); i++)
  {
    char tChar = token[i];
    //printf("%c ", tChar);
    if (!hasAlpha)
    {
      if ((isdigit(tChar)) || (tChar == '-' && i == 0 && strlen(token) > 1)) // Assume - is a number as long as it is first, and not single.
      {
        hasNumber = 1;
      }
    }
    if (isalpha(tChar))
    {
      hasAlpha = 1;
      hasNumber = 0;
    }
    if (!(tChar == '-' && i == 0 && isdigit(token[i+1])) && !isdigit(tChar) && !isalpha(tChar))
    {
      fprintf(stderr, "Illegal character: [%c] (ASCII: %d)\n", tChar, tChar);
      exit(1);
    }
  }
  if (hasNumber && (strlen(token) > sizeof(int)))
  {
    fprintf(stderr, "Number is too large for integer.\n");
    exit(1);
  }

  // printf("\n");
  // if (hasAlpha)
  // {
  //   printf("Is alpha\n\n");
  // }
  // else if (hasNumber)
  // {
  //   printf("Is number\n\n");
  // }
  // else
  // {
  //   printf("Illegal!\n\n");
  // }
}

void getNumList(Node **headRef)
{
  Node *numList = NULL;
  Node *key = *headRef;

  while (key)
  {
    appendNode(&numList, makeNodeInt(atoi(getToken(key))));
    key = key->nextNode;
  }
  //freeList(*headRef);
  *headRef = numList;
}

int quickSort(void *toSort, int (*comparator)(void *, void *))
{
  Node *head = (Node *)toSort;
  Node *last = (Node *)toSort;
  while (last && last->nextNode){
      last = last->nextNode;
  }
  _quickSort(head, last, comparator);
  
  //printf("%d\n", comparator(getToken(head), getToken(head->nextNode)));
}

void _quickSort(Node* h, Node* l, int (*comparator)(void *, void *)){
    if (l!= NULL && h != l && h !=l->nextNode){
        
        Node *p = partition(h,l,comparator);
        //printNodes(p);
        // printf("what is p: %s\n", p->tokenStr);
        // printf("what is p: %s\n", p->prevNode->tokenStr);
        // printf("what is h: %s\n", h->tokenStr);
        _quickSort(p->nextNode,l,comparator);
        _quickSort(h, p->prevNode, comparator);
        
    }
}

Node *partition(Node *h, Node *l,int (*comparator)(void *, void *)){
     void* x = getToken(h);
     Node* i = l->nextNode;
     Node* j;
     
     for(j = l; j!= h; j = j->prevNode){
          if (comparator(getToken(j), x) >= 0){
            if (i == NULL){
                i = l;
              } else {
                i = i->prevNode;
              }
            swapValue(j, i);
         }
     }
     if (i == NULL){
       i = l;
     } else {
       i = i->prevNode;
     }
    //printf("start: %s\n", getToken(i));
    swapValue(i,h);
    return i;
}



void swapValue(Node *a, Node *b)
{
  if (!a->isString)
  {
    int t = *(a->tokenInt);
    *(a->tokenInt) = *(b->tokenInt);
    *(b->tokenInt) = t;
  }
  else
  {
    char *t = a->tokenStr;
    a->tokenStr = b->tokenStr;
    b->tokenStr = t;
  }
}

// void swap(Node **a, Node **b)
// {
//   void *temp = *a;
//   *a = *b;
//   *b = temp;
// }