#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/stat.h>

#include "readBuildCodebook.h"
#include "huffmanTree.h"
#include "initReadFile.h"
#include "translate.h"

void readBuildCodebook(char *fileName, HeapNode **headRef)
{
  INIT_READ(fileName);

  // Start reading the file
  //while ((bytes_read = read(fd, readBuf, readBufSize) > 0))
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

    // If end of the token is reached, check if it is a valid number or string token.
    if (reachedEnd || isspace(aChar) || iscntrl(aChar))
    {
      if (reachedEnd && tokenLength == 0)
      {
        break;
      }

      // emptyFile = 0; // Differentiate between empty file and empty token at end of file
      if (!reachedEnd)
      {
        listFindAppend(headRef, fromCntrl(aChar));
      }

      // For multiple whitespaces in a row, continue
      if (tokenLength == 0)
      {
        continue;
      }

      // Add word to list
      tokenBuf[tokenLength++] = '\0'; // Add string delimiter
      //printf("\nFound token: [%s]\n", tokenBuf);

      listFindAppend(headRef, tokenBuf);

      // Reset token pointer to 0 to read next token
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
}
