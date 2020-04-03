#ifndef READ_TO_ENCODE
#define READ_TO_ENCODE

#include "huffmanTree.h"

void readToEncode(char *fileName, HeapNode *headRef);
void encode(int encodeFile, HeapNode *head, char *word);
#endif