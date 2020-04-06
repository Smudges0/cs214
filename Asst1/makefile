CC = gcc # set compiler
# CFLAGS = -g # add debugging to executable, turn on all compiler warnings

.PHONY: all # in case there's a file called 'all'
all: fileCompressor

fileCompressor: fileCompressor.o huffmanTree.o readBuildCodebook.o printFunctions.o readFromCodebook.o translate.o readToEncode.o readToDecode.o recursiveMode.o
	$(CC) -o fileCompressor fileCompressor.o huffmanTree.o readBuildCodebook.o printFunctions.o readFromCodebook.o translate.o readToEncode.o readToDecode.o recursiveMode.o

fileCompressor.o: fileCompressor.c printFunctions.h huffmanTree.h readBuildCodebook.h readFromCodebook.h readToEncode.h readToDecode.h
	$(CC) -c fileCompressor.c

printFunctions.o: printFunctions.c printFunctions.h huffmanTree.h
	$(CC) -c printFunctions.c

huffmanTree.o: huffmanTree.c huffmanTree.h printFunctions.h translate.h
	$(CC) -c huffmanTree.c

# initReadFile.o: initReadFile.h
# 	$(CC)  -c initReadFile.c

readBuildCodebook.o: readBuildCodebook.c readBuildCodebook.h huffmanTree.h initReadFile.h translate.h
	$(CC) -c readBuildCodebook.c

readFromCodebook.o: readFromCodebook.c readFromCodebook.h huffmanTree.h initReadFile.h
	$(CC) -c readFromCodebook.c

readToEncode.o: readToEncode.c readToEncode.h huffmanTree.h initReadFile.h
	$(CC) -c readToEncode.c

readToDecode.o: readToDecode.c readToDecode.h huffmanTree.h initReadFile.h
	$(CC) -c readToDecode.c

translate.o: translate.c translate.h
	$(CC) -c translate.c

recursiveMode.o: recursiveMode.c recursiveMode.h huffmanTree.h
	$(CC) -c recursiveMode.c

clean:
	rm fileCompressor fileCompressor.o huffmanTree.o readBuildCodebook.o printFunctions.o readFromCodebook.o translate.o readToEncode.o readToDecode.o recursiveMode.o