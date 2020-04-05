#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

#include "recursiveMode.h"
#include "huffmanTree.h"

void callRecursively(char *basePath, HeapNode **headRef, void (*readFunction)(char *, HeapNode **), char *flag)
{
  DIR *directory;
  struct dirent *directoryEntry;

  if (!(directory = opendir(basePath)))
  {
    printf("Failed to open directory.\n");
    exit(EXIT_FAILURE);
  }

  while ((directoryEntry = readdir(directory)) != NULL)
  {
    printf("%s %ld\n", directoryEntry->d_name, strlen(directoryEntry->d_name));
    if (strcmp(directoryEntry->d_name, ".") == 0 || strcmp(directoryEntry->d_name, "..") == 0) // Ignore . and .. directories.
    {
      continue;
    }

    // Get new path
    char *newPathName = malloc((sizeof(char) * strlen(basePath)) + (sizeof(char) * strlen(directoryEntry->d_name)) + 2); // +2 for '/' and '\0'
    strcpy(newPathName, basePath);
    strcat(newPathName, "/");
    strcat(newPathName, directoryEntry->d_name);
    strcat(newPathName, "\0");

    if (isDirectory(newPathName))
    {
      callRecursively(newPathName, headRef, readFunction, flag);
      continue;
    }

    if (!strcmp(flag, "-b") || !strcmp(flag, "-c")) // if building codebook
    {
      // if file ends in .txt
      printf("%s\n", getExtension(directoryEntry->d_name));
      if (strcmp(getExtension(directoryEntry->d_name), "txt") == 0)
      {
        readFunction(newPathName, headRef); // readBuildCodebook(basepath, headRef); or readToEncode(basePath, &headRef)
      }
    }
    else if (!strcmp(flag, "-d"))
    {
      // if file ends in .hcz
      if (strcmp(getExtension(directoryEntry->d_name), "hcz") == 0)
      {
        readFunction(newPathName, headRef); // readToDecode(basePath, &headRef)
      }
    }
  }
}

char *getExtension(char *fileName)
{
  char *dotPos = strrchr(fileName, '.');
  if (!dotPos || dotPos == fileName)
  {
    return "";
  }
  return dotPos + 1;
}

int isDirectory(char *path)
{
  struct stat pathStat;
  stat(path, &pathStat);
  return S_ISDIR(pathStat.st_mode);
}