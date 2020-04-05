#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/stat.h>

#include "huffmanTree.h"
#include "printFunctions.h"
#include "translate.h"

HeapNode *newNode(char *token, unsigned count)
{
  HeapNode *aNode = (HeapNode *)malloc(sizeof(HeapNode));
  aNode->left = NULL;
  aNode->right = NULL;
  if (token)
  {
    aNode->token = malloc(sizeof(char) * strlen(token) + 1);
    strcpy(aNode->token, token);
  }
  aNode->count = count;

  return aNode;
}

HeapNode *newCodeNode(char *code, char *token)
{
  HeapNode *aNode = (HeapNode *)malloc(sizeof(HeapNode));
  aNode->left = NULL;
  aNode->right = NULL;
  if (code)
  {
    aNode->code = malloc(sizeof(char) * strlen(code) + 1);
    strcpy(aNode->code, code);
  }
  if (token)
  {
    aNode->token = malloc(sizeof(char) * strlen(token) + 1);
    strcpy(aNode->token, token);
  }

  return aNode;
}

void listFindAppend(HeapNode **head, char *token)
{
  HeapNode *aNode = *head;

  if (!aNode)
  {
    // List is empty.  Create it and make it the head
    aNode = newNode(token, 1);
    *head = aNode;
    return;
  }
  HeapNode *prevNode;
  while (aNode) // Loop until reach last node
  {
    if (strcmp(aNode->token, token) == 0)
    {
      (aNode->count)++;
      return;
    }
    prevNode = aNode;
    aNode = aNode->right;
  }

  prevNode->right = newNode(token, 1); // If not in list, add node
  (*head)->left = prevNode->right;     // Make head node have a pointer to the last node.
}

MinHeap *createMinHeap(unsigned capacity)
// nodes are stored in an array. Nodes will be accessed with formulas 2x + 1 for left child, 2x + 2 for right child, and (x - 1)/2 for parent nodes, where X is index
{
  MinHeap *minHeap = (MinHeap *)malloc(sizeof(MinHeap));
  minHeap->size = 0;
  minHeap->capacity = capacity;

  minHeap->array = (HeapNode **)malloc(minHeap->capacity * sizeof(HeapNode));

  return minHeap;
}

void swapHeapNode(HeapNode **a, HeapNode **b)
{
  HeapNode *temp = *a;
  *a = *b;
  *b = temp;
}

void reHeapLocal(MinHeap *minHeap, int root) // order nodes to be in a minHeap
// Heapify only works if children are also heapified; That's why buildMinHeap calls heapify from the bottom up.
// This is also called a SIFT DOWN: We sift the node down to its correct place.
{
  int left = 2 * root + 1;  // address of left child in array
  int right = 2 * root + 2; // address of right child in array
  int min = root;           // tracks current minimum value

  // If left is valid node and is smaller than current smallest, mark left as the smallest
  if (left < minHeap->size && minHeap->array[left]->count < minHeap->array[min]->count)
  {
    min = left;
  }
  // If right is valid node and is smaller than current smallest, mark right as new smallest
  if (right < minHeap->size && minHeap->array[right]->count < minHeap->array[min]->count)
  {
    min = right;
  }
  // If minimum value is no longer the root, swap root and smallest node, then heapify to maintain heap order.
  if (min != root)
  {
    swapHeapNode(&minHeap->array[min], &minHeap->array[root]);
    reHeapLocal(minHeap, min);
  }
}

int isSizeOne(MinHeap *minHeap)
{
  return (minHeap->size == 1);
}

HeapNode *getMin(MinHeap *minHeap)
{
  HeapNode *min = minHeap->array[0];                     // hold current root, which is the minimum
  minHeap->array[0] = minHeap->array[minHeap->size - 1]; // Make the last node of the tree, which is a leaf, the new root. minHeap->size - 1 gives you the last node
  minHeap->size--;                                       // Decrement size of tree
  reHeapLocal(minHeap, 0);                               // Call heapify to maintain heap order

  return min; // return minimum value
}

void insertNode(MinHeap *minHeap, HeapNode *minHeapNode)
// This is also called a FLOAT UP: We float the new node up to its correct place.
{
  minHeap->size++;                                                         // Increase size of minHeap
  int i = minHeap->size - 1;                                               // Counter, starts from the bottom of the heap
  while (i > 0 && minHeapNode->count < minHeap->array[(i - 1) / 2]->count) // while i isn't the root and new value is smaller than above value
  {
    minHeap->array[i] = minHeap->array[(i - 1) / 2]; // Move parent node down
    i = (i - 1) / 2;                                 // i moves into parent node's place
  }
  minHeap->array[i] = minHeapNode; // insert minHeapNode into the correct spot
}

void reHeapGlobal(MinHeap *minHeap) // Heapify entire heap
{
  int childNode = minHeap->size - 1;             // Last node in the heap
  for (int i = (childNode - 1) / 2; i >= 0; i--) // move up tree, re-heap on every parent node
  {
    reHeapLocal(minHeap, i);
  }
}

int isLeaf(HeapNode *aNode)
{
  return !(aNode->left) && !(aNode->right);
}

MinHeap *initMinHeap(HeapNode *head, int capacity)
{
  MinHeap *minHeap = createMinHeap(capacity);
  HeapNode *aNode = head;
  HeapNode *nextInList;
  for (int i = 0; i < capacity; i++)
  {
    nextInList = aNode->right; // Hold aNode->right in a temp pointer
    aNode->right = NULL;       // Remove pointer to next node
    aNode->left = NULL;        // Remove left pointer. Only relevant for head node of the list.
    minHeap->array[i] = aNode;
    aNode = nextInList; // Traverse down list using temp pointer to next node
  }

  minHeap->size = capacity;
  reHeapGlobal(minHeap);

  return minHeap;
}

HeapNode *huffmanTree(HeapNode *head, int size)
{
  HeapNode *left, *right, *parent;
  MinHeap *minHeap = initMinHeap(head, size);
  // if (size == 1)
  // {
  //   HeapNode *noToken = newNode(NULL, (minHeap->array[0])->count);
  //   noToken->left = getMin(minHeap);
  //   return getMin(minHeap);
  // }

  while (!(isSizeOne(minHeap))) // Loop until only 1 node left in minHeap
  {
    left = getMin(minHeap);                             // Take 1st minimum, make it left child
    right = getMin(minHeap);                            // Take 2nd minimum, make it right child
    parent = newNode(NULL, left->count + right->count); // Make parent hold sum of frequencies
    parent->left = left;                                // Set child pointers to correct children
    parent->right = right;
    insertNode(minHeap, parent); // Insert parent into minHeap
  }
  return getMin(minHeap); // Return the final node. This is the first node in your huffman tree.
}

int treeHeight(HeapNode *aNode)
{
  if (!aNode)
  {
    return 0;
  }

  int leftHeight = treeHeight(aNode->left);
  int rightHeight = treeHeight(aNode->right);

  if (leftHeight > rightHeight)
  {
    return (leftHeight + 1);
  }
  else
  {
    return (rightHeight + 1);
  }
}

void buildHuffmanCodes(HeapNode **head, int size)
{
  HeapNode *root;
  if (size == 0) // If File is empty, insert a completely blank node
  {
    HeapNode *zeroNode = newNode("", 0);
    *head = zeroNode;
  }
  else if (size == 1) // If size is one, insert an empty node and insert the real node as it's left child
  {
    HeapNode *noToken = newNode(NULL, (*head)->count);
    noToken->left = *head;
    *head = noToken;
  }
  else // Else, build huffman tree normally
  {
    root = huffmanTree(*head, size);
    *head = root;
  }

  int top = 0;
  int arr[treeHeight(root)];
  int fd = open("HuffmanCodebook", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
  if (fd == -1)
  {
    perror("File write error");
    exit(EXIT_FAILURE);
  }

  write(fd, "\\\n", 2);
  printCodeFile(*head, arr, top, fd);
}

void codeWordList(HeapNode **head, char *code, char *word, char escapeChar)
{
  if (word[0] == escapeChar)
  {
    word = toCntrl(word);
  }

  HeapNode *aNode = *head;

  if (!aNode)
  {
    // List is empty.  Create it and make it the head
    aNode = newCodeNode(code, word);
    *head = aNode;
    return;
  }
  HeapNode *prevNode;
  while (aNode) // Loop until reach last node
  {
    prevNode = aNode;
    aNode = aNode->right;
  }

  prevNode->right = newCodeNode(code, word); //Add node
  //(*head)->left = prevNode->right;     // Make head node have a pointer to the last node.
}

void recreateTree(HeapNode **codeTreeHead, HeapNode *headOfList)
{
  HeapNode *currentTreeNode = *codeTreeHead;
  HeapNode *currentListNode = headOfList;
  HeapNode *nextInList;

  // Create a blank node to start the tree
  currentTreeNode = newCodeNode(NULL, NULL);
  *codeTreeHead = currentTreeNode;

  while (currentListNode) // Go down the list and insert nodes into tree
  {
    // ONLY GET HERE IF WE READ NOTHING FROM THE CODEBOOK. THERE IS AN EMPTY WORD IN THE LIST, CODE "" AND TOKEN ""
    // Need to break here, or will loop infinitely
    if (strlen(currentListNode->token) == 0)
    {
      break;
    }

    for (int i = 0; i < strlen(currentListNode->code); i++) // Loop over code in currentListNode
    {
      if (i != strlen(currentListNode->code) - 1) // If not at end of code, insert blank node at left/right in tree
      {
        if (currentListNode->code[i] == '0') // LEFT
        {
          if (currentTreeNode->left) // if left node already exists, go to that node
          {
            currentTreeNode = currentTreeNode->left;
            continue;
          }
          else // if doesn't exist, make node and go to it
          {
            currentTreeNode->left = newCodeNode(NULL, NULL);
            currentTreeNode = currentTreeNode->left;
            continue;
          }
        }
        else // RIGHT
        {
          if (currentTreeNode->right) // if right node exists, go to it
          {
            currentTreeNode = currentTreeNode->right;
            continue;
          }
          else // if doesn't exist, make node and go to it
          {
            currentTreeNode->right = newCodeNode(NULL, NULL);
            currentTreeNode = currentTreeNode->right;
            continue;
          }
        }
      }
      else // If at end of code, insert currentListNode into tree at left/right
      {
        if (currentListNode->code[i] == '0')
        {
          currentTreeNode->left = currentListNode;
          currentTreeNode = currentTreeNode->left;
        }
        else
        {
          currentTreeNode->right = currentListNode;
          currentTreeNode = currentTreeNode->right;
        }
        nextInList = currentListNode->right;
        // Remove pointers from node to make it a leaf
        currentTreeNode->left = NULL;
        currentTreeNode->right = NULL;
        // Once at end of code, move on to next node in the list
        currentListNode = nextInList;
        // printf("1. %s %s\n", currentTreeNode->code, currentTreeNode->token);
        // Reset currentTreeNode back to top of the tree
        currentTreeNode = *codeTreeHead;
        break;
      }
    }
  }
}

void freeAllNodes(HeapNode *head)
{
  if (head->left) // check for left child
  {
    freeAllNodes(head->left); // go to left child
  }
  if (head->right) // check for right child
  {
    freeAllNodes(head->right); // go to right child
  }

  // Free token/code if applicable
  if (head->code)
  {
    free(head->code);
  }
  if (head->token)
  {
    free(head->token);
  }

  free(head);
}