#ifndef RECURSIVE_MODE
#define RECURSIVE_MODE

#include "huffmanTree.h"

void callRecursively(char *basePath, HeapNode **headRef, void (*readFunction)(char *, HeapNode **), char *flag);
char *getExtension(char *fileName);
int isDirectory(char *path);
int isRegFile(char *path);

#endif