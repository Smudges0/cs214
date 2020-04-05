#ifndef HUFFMAN_TREE
#define HUFFMAN_TREE

typedef struct minHeapNode
{
  char *token;
  char *code;
  unsigned count;

  struct minHeapNode *left, *right;
} HeapNode;

typedef struct minHeap
{
  unsigned size;     // Current amount of Nodes
  unsigned capacity; // Maximum Nodes
  HeapNode **array;  // Access the nodes
} MinHeap;

// Function Declarations
HeapNode *newNode(char *token, unsigned count);
void listFindAppend(HeapNode **head, char *token);
MinHeap *createMinHeap(unsigned capacity);
void reHeapLocal(MinHeap *minHeap, int root);
int isSizeOne(MinHeap *minHeap);
HeapNode *getMin(MinHeap *minHeap);
void insertNode(MinHeap *minHeap, HeapNode *minHeapNode);
void reHeapGlobal(MinHeap *minHeap);
int isLeaf(HeapNode *aNode);
MinHeap *initMinHeap(HeapNode *head, int capacity);
int treeHeight(HeapNode *aNode);
HeapNode *huffmanTree(HeapNode *head, int size);
void buildHuffmanCodes(HeapNode **head, int size);
void codeWordList(HeapNode **head, char *code, char *word, char escapeChar);

HeapNode *newCodeNode(char *code, char *word);
void recreateTree(HeapNode **codetreeHead, HeapNode *head);

void printHuffmanCode(int fd, int code[], int length, char *token);
void printCodeFile(HeapNode *root, int code[], int top, int fd);
void printNodes(HeapNode *aNode);
int listLength(HeapNode *aNode);

void freeAllNodes(HeapNode *head);
#endif