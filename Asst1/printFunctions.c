#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/stat.h>

#include "printFunctions.h"
#include "huffmanTree.h"

void printHuffmanCode(int fd, int code[], int length, char *token)
{
  int i;
  //int bytes_written;
  int writeBufSize = 1;
  char *writeBuf = malloc(sizeof(char) * writeBufSize);

  for (i = 0; i < length; ++i)
  {
    sprintf(writeBuf, "%d", code[i]);
    write(fd, writeBuf, 1);
    //printf("%d", arr[i]);
  }
  write(fd, "\t", 1);
  write(fd, token, strlen(token));
  write(fd, "\n", 1);
  // printf("\n");
}

void printCodeFile(HeapNode *root, int code[], int top, int fd)
{
  if (root->left)
  {
    code[top] = 0;
    printCodeFile(root->left, code, top + 1, fd);
  }
  if (root->right)
  {
    code[top] = 1;
    printCodeFile(root->right, code, top + 1, fd);
  }
  if (isLeaf(root))
  {
    // printf("  %s   | ", root->token);
    printHuffmanCode(fd, code, top, root->token);
  }
}

void printNodes(HeapNode *aNode)
{
  while (aNode)
  {
    printf("%s\t%d\n", aNode->token, aNode->count);
    aNode = aNode->right;
  }
}

int listLength(HeapNode *aNode)
{
  int length = 0;
  while (aNode)
  {
    length++;
    aNode = aNode->right;
  }
  return length;
}