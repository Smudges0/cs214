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
#include "readBuildCodebook.h"
#include "readFromCodebook.h"
#include "readToEncode.h"

int main(int argc, char *argv[])
{

	if (argc < 3 || argc > 5)
	{
		fprintf(stderr, "Incorrect number of arguments.\n");
		exit(EXIT_FAILURE);
	}
	// Variables
	int doBuild = 0;
	int doCompress = 0;
	int doDecompress = 0;
	int recursive = 0;

	char *fileName;
	char *codeBook;

	for (int i = 1; i < argc; i++)
	{
		if (argv[i][0] == '-')
		{
			switch (argv[i][1])
			{
			case 'R':
				recursive = 1;
				break;
			case 'b':
				doBuild = 1;
				break;
			case 'c':
				doCompress = 1;
				break;
			case 'd':
				doDecompress = 1;
				break;
			default:
				fprintf(stderr, "Invalid flag: %s. Valid flags are -R, -b, -c, or -d.\n", argv[i]);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			if (doBuild)
			{
				fileName = argv[i];
				break;
			}
			if (doCompress)
			{
				if (argc == i + 2)
				{
					fileName = argv[i];
					codeBook = argv[++i];
					break;
				}
			}
			if (doDecompress)
			{
				if (argc == i + 2)
				{
					fileName = argv[i];
					codeBook = argv[++i];
					break;
				}
			}
			fprintf(stderr, "Not enough arguments for flag.\nBuild takes filename or path, Compress and decompress take a filename or path and a codebook.\n");
			exit(EXIT_FAILURE);
		}
	}
	// 2. Read tokens from file, put tokens into linked list, returns list
	HeapNode *headRef = NULL;
	if (doBuild)
	{
		readBuildCodebook(fileName, &headRef);
		buildHuffmanCodes(headRef, listLength(headRef));
	}

	if (doCompress) // this one needs a codebook AND a file
	{
		readFromCodebook(codeBook, &headRef);
		readToEncode(fileName, headRef);
	}

	if (!headRef)
	{
		fprintf(stderr, "No valid tokens.\n");
		exit(EXIT_FAILURE);
	}
	// printNodes(headRef);
	// printf("\n");
	// printf(" Str | Huffman code ");
	// printf("\n--------------------\n");

	//Testing translate function
	// char *controlCode = translate('\\');
	// printf("%s", controlCode);
	exit(EXIT_SUCCESS);
}
// TODO: FIND TREE HEIGHT, PASS TO PRINT FUNCTION