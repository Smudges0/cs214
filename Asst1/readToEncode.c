#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/stat.h>

#include "readToEncode.h"
#include "huffmanTree.h"
#include "initReadFile.h"

void readToEncode(char *fileName, HeapNode *headRef)
{
  // INIT_READ(fileName);

  int fd = open(fileName, O_RDONLY);
  if (fd == -1)
  {
    perror("File Read Error");
    exit(EXIT_FAILURE);
  }
  int tokenBufSize = 10;
  char *tokenBuf = (char *)malloc(tokenBufSize);
  if (tokenBuf == NULL)
  {
    fprintf(stderr, "out of memory for tokenBuf\n");
    close(fd);
    exit(EXIT_FAILURE);
  }
  int readBufSize = 1;
  char *readBuf = (char *)malloc(readBufSize);
  if (readBuf == NULL)
  {
    fprintf(stderr, "out of memory for readBuf\n");
    close(fd);
    exit(EXIT_FAILURE);
  }
  int bytes_read;
  int tokenLength = 0;
  int reachedEnd = 0;

  // Open file for writing encoded file to
  // char *hczExtension = ".hcz";
  char *outputFileName = (char *)malloc(strlen(fileName) + 5);
  strcpy(outputFileName, fileName);
  strcat(outputFileName, ".hcz");

  int encodeFile = open(outputFileName, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
  if (encodeFile == -1)
  {
    perror("File write error");
    free(readBuf);
    free(tokenBuf);
    close(fd);
    close(encodeFile);
    exit(EXIT_FAILURE);
  }

  char *whiteSpace = (char *)malloc(1); // Hold whitespace. Write word first, then write whitespace.
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
      close(encodeFile);
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
        fprintf(stderr, "out of memory for tokenBuf realloc\n");
        free(readBuf);
        free(tokenBuf);
        close(fd);
        close(encodeFile);
        exit(EXIT_FAILURE);
      }
      else
        tokenBuf = tokenBuf2;
    }

    //printf("%.*s", bytes_read, readBuf);
    // Actually reading one char at a time....
    char aChar;
    if (!reachedEnd)
    {
      aChar = readBuf[0];
    }

    // If end of the token is reached, check if it is a valid number or string token.
    if (reachedEnd || isspace(aChar) || iscntrl(aChar))
    {
      if (reachedEnd) // Check if we're at the end of the file
      {
        if (tokenLength == 0) // At the end, and nothing left in the buffer so there's nothing to do
        {
          break;
        }
        // Write leftovers in tokenBuf
        tokenBuf[tokenLength++] = '\0';
        encode(encodeFile, headRef, tokenBuf);
      }
      // This will run if it's not EOF. We've hit whitespace
      if (tokenLength == 0) // Hit consecutive whitespace
      {
        // write whitespace to file
        whiteSpace[0] = aChar;
        encode(encodeFile, headRef, whiteSpace);
        continue;
      }
      // This will run if we hit end of token IE only if we pass all other checks.
      tokenBuf[tokenLength++] = '\0';
      // Save whitespace
      whiteSpace[0] = aChar;
      // write tokenBuf to file
      encode(encodeFile, headRef, tokenBuf);
      // write whitespace to file
      encode(encodeFile, headRef, whiteSpace);
      tokenLength = 0;
    }
    else
    {
      tokenBuf[tokenLength++] = aChar;
    }
  } // End of file read

  //Cleanup on success
  free(readBuf);
  free(tokenBuf);
  close(fd);
  close(encodeFile);
}

void encode(int encodeFile, HeapNode *head, char *word)
{
  HeapNode *aNode = head;
  while (aNode)
  {
    if (strcmp(aNode->token, word) == 0)
    {
      write(encodeFile, aNode->code, strlen(aNode->code));
      return;
    }
    aNode = aNode->right;
  }
}