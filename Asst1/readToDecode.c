#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/stat.h>

#include "readToDecode.h"
#include "huffmanTree.h"
#include "initReadFile.h"

void readToDecode(char *fileName, HeapNode **codeTreeHead)
{
  INIT_READ(fileName);

  char *outputFileName = malloc(sizeof(char) * strlen(fileName) + 5);
  strcpy(outputFileName, fileName);
  strcat(outputFileName, ".txt\0");

  int decodeFile = open(outputFileName, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
  HeapNode *currentNode = *codeTreeHead;
  // printf("%s\n", fileName);
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
      free(readBuf);
      free(tokenBuf);
      close(fd);
      close(decodeFile);
      exit(EXIT_FAILURE);
    }
    else if (bytes_read == 0)
    {
      //printf("\n\nEnd of file reached. tokenLength: %d\n", tokenLength);
      reachedEnd = 1;
      // break;
    }

    if (tokenLength >= tokenBufSize - 1)
    {
      /* time to make it bigger */
      tokenBufSize += 10;
      //printf("-----Growing %d-----", tokenBufSize);
      char *tokenBuf2 = realloc(tokenBuf, tokenBufSize);
      if (tokenBuf2 == NULL)
      {
        printf("out of memory for tokenBuf realloc\n");
        free(readBuf);
        free(tokenBuf);
        close(fd);
        close(decodeFile);
        exit(EXIT_FAILURE);
      }
      else
        tokenBuf = tokenBuf2;
    }

    //printf("%.*s", bytes_read, readBuf);
    // Actually reading one char at a time....
    char aChar;
    if (!reachedEnd) // As long as we aren't at the end, add the character to the buffer
    {
      aChar = readBuf[0];
      // printf("Read character: %c\n", aChar);
      if (aChar == '0') // LEFT
      {
        // printf("Going left\n");
        currentNode = currentNode->left;
      }
      else if (aChar == '1')
      {
        // printf("Going right\n");
        currentNode = currentNode->right;
      }
      else
      {
        printf("Invalid character in .hcz file\n");
        exit(EXIT_FAILURE);
      }

      if (isLeaf(currentNode)) // If not at end of code, follow code down tree until we get to correct node
      {
        // printf("Token matched: %s\n", currentNode->token);
        write(decodeFile, currentNode->token, strlen(currentNode->token));
        currentNode = *codeTreeHead; // Reset currentNode for next code
      }
    }
    else
    {
      // printf("Reached End of file\n");
      break;
    }

  } // End of file read

  //Cleanup on success
  free(readBuf);
  free(tokenBuf);
  close(fd);
  close(decodeFile);
}