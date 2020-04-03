#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/stat.h>

#include "readFromCodebook.h"
#include "huffmanTree.h"
#include "initReadFile.h"

void readFromCodebook(char *fileName, HeapNode **headRef)
{
  INIT_READ(fileName);

  // Start reading the file
  //while ((bytes_read = read(fd, readBuf, readBufSize) > 0))

  char *code;
  char *word;

  char escapeChar;

  // Read up until Huffman codes. Huffman codebook starts with a \ followed by a \n, so I need to read 2 characters to start reading the actual codes.
  read(fd, readBuf, readBufSize);
  escapeChar = readBuf[0];
  read(fd, readBuf, readBufSize);

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

    // If end of the token is reached, check if it is a valid token.
    if (reachedEnd || aChar == '\t' || aChar == '\n')
    {
      // Break if it's the end of the file and there's no token stored
      if (reachedEnd && tokenLength == 0)
      {
        break;
      }

      if (aChar == '\t')
      {
        tokenBuf[tokenLength++] = '\0';
        code = malloc(sizeof(tokenBuf));
        strcpy(code, tokenBuf);
        tokenLength = 0;
      }
      else if (aChar == '\n')
      {
        tokenBuf[tokenLength++] = '\0';
        word = malloc(sizeof(tokenBuf));
        strcpy(word, tokenBuf);
        tokenLength = 0;

        codeWordList(headRef, code, word, escapeChar);
      }
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
}
