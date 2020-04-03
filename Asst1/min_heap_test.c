#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_HT 50
// Structure Definitions
typedef struct minHeapNode
{
  char token;
  unsigned count;

  struct minHeapNode *left, *right;
} HeapNode;

typedef struct minHeap
{
  unsigned size;     // Current amount of Nodes
  unsigned capacity; // Maximum Nodes
  HeapNode **array;  // Access the nodes
} MinHeap;

// Functions
HeapNode *newNode(char token, unsigned count)
{
  HeapNode *aNode = (HeapNode *)malloc(sizeof(HeapNode));
  aNode->left = NULL;
  aNode->right = NULL;
  aNode->token = token;
  aNode->count = count;

  return aNode;
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
  reHeapLocal(minHeap, minHeap->array[0]);               // Call heapify to maintain heap order

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

MinHeap *initMinHeap(char token[], int count[], int capacity)
{
  MinHeap *minHeap = createMinHeap(capacity);

  for (int i = 0; i < capacity; i++)
  {
    minHeap->array[i] = newNode(token[i], count[i]);
  }

  minHeap->size = capacity;
  reHeapGlobal(minHeap);

  return minHeap;
}

HeapNode *huffmanTree(char token[], int count[], int size)
{
  HeapNode *left, *right, *parent;
  MinHeap *minHeap = initMinHeap(token, count, size);
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

void printCodes(HeapNode *root, int arr[], int top)
{
  if (root->left)
  {

    arr[top] = 0;
    printCodes(root->left, arr, top + 1);
  }
  if (root->right)
  {

    arr[top] = 1;
    printCodes(root->right, arr, top + 1);
  }
  if (isLeaf(root))
  {

    printf("  %c   | ", root->token);
    printArray(arr, top);
  }
}

void printArray(int arr[], int n)
{
  int i;
  for (i = 0; i < n; ++i)
    printf("%d", arr[i]);

  printf("\n");
}

void HuffmanCodes(char token[], int count[], int size)
{
  HeapNode *root = huffmanTree(token, count, size);

  int arr[MAX_TREE_HT], top = 0;

  printCodes(root, arr, top);
}

int main()
{
  char token[] = {'A', 'B', 'C', 'D'};
  int count[] = {5, 1, 6, 3};

  int size = sizeof(token) / sizeof(token[0]);

  printf(" Str | Huffman code ");
  printf("\n--------------------\n");

  HuffmanCodes(token, count, size);
}