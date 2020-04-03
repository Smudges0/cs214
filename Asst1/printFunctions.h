#ifndef PRINT_FUNCTIONS
#define PRINT_FUNCTIONS

#include "huffmanTree.h"
// Function Declarations
void printHuffmanCode(int fd, int code[], int length, char *token);
void printCodeFile(HeapNode *root, int code[], int top, int fd);
void printNodes(HeapNode *aNode);
int listLength(HeapNode *aNode);

#endif