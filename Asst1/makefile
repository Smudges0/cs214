CC = gcc # set compiler
CFLAGS = -g # add debugging to executable, turn on all compiler warnings

.PHONY: all # in case there's a file called 'all'
all: fileCompressor

fileCompressor: fileCompressor.o huffmanTree.o readBuildCodebook.o printFunctions.o readFromCodebook.o translate.o readToEncode.o readToDecode.o recursiveMode.o
	$(CC) $(CFLAGS) -o fileCompressor fileCompressor.o huffmanTree.o readBuildCodebook.o printFunctions.o readFromCodebook.o translate.o readToEncode.o readToDecode.o recursiveMode.o

fileCompressor.o: fileCompressor.c printFunctions.h huffmanTree.h readBuildCodebook.h readFromCodebook.h readToEncode.h readToDecode.h
	$(CC) $(CFLAGS) -c fileCompressor.c

printFunctions.o: printFunctions.c printFunctions.h huffmanTree.h
	$(CC) $(CFLAGS) -c printFunctions.c

huffmanTree.o: huffmanTree.c huffmanTree.h printFunctions.h translate.h
	$(CC) $(CFLAGS) -c huffmanTree.c

# initReadFile.o: initReadFile.h
# 	$(CC) $(CFLAGS) -c initReadFile.c

readBuildCodebook.o: readBuildCodebook.c readBuildCodebook.h huffmanTree.h initReadFile.h translate.h
	$(CC) $(CFLAGS) -c readBuildCodebook.c

readFromCodebook.o: readFromCodebook.c readFromCodebook.h huffmanTree.h initReadFile.h
	$(CC) $(CFLAGS) -c readFromCodebook.c

readToEncode.o: readToEncode.c readToEncode.h huffmanTree.h initReadFile.h
	$(CC) $(CFLAGS) -c readToEncode.c

readToDecode.o: readToDecode.c readToDecode.h huffmanTree.h initReadFile.h
	$(CC) $(CFLAGS) -c readToDecode.c

translate.o: translate.c translate.h
	$(CC) $(CFLAGS) -c translate.c

recursiveMode.o: recursiveMode.c recursiveMode.h huffmanTree.h
	$(CC) $(CFLAGS) -c recursiveMode.c

clean:
	rm fileCompressor fileCompressor.o huffmanTree.o readBuildCodebook.o printFunctions.o readFromCodebook.o translate.o readToEncode.o readToDecode.o recursiveMode.o