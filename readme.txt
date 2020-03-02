FILESORT

NAME
	fileSort - reads a file, and outputs sorted values

SYNOPSIS
	fileSort -i | -q FILENAME

DESCRIPTION
	Reads comma delimited tokens from a file and stores them in a doubly linked list. 
	It then sorts the tokens using the specified sorting method and outputs the values.
	Supported sorting methods are insertion sort and quick sort.

	- File can only contain integer tokens or alpha tokens, and cannot be mixed
		- if mixed, integers will be treated as strings
	- Whitespaces are removed
	- Integers may have a leading '-' (minus sign). Otherwise, minus is an illegal character.
	- Any other characters besides alphanumerics, commas, and whitespaces are illegal characters.
	- Empty tokens (',,') are treated as empty strings, except at the end of the file where it is ignored.
	- Integers can't exceed the maximum size of an integer
	- Text file can be any size, up to maximum memory
	- Tokens can be any size, up to maximum memory
	- Uses a doubly linked list which can store either integer or char * tokens

OPTIONS
	-i Sort using Insertion Sort.
	-q Sort using Quick Sort.

EXIT STATUS
	Returns EXIT_FAILURE(1) on fatal exceptions. 
	Fatal exceptions include:
		- Incorrect number of arguments
		- Invalid sorting type
		- File read error including missing file, no access, etc
		- Out of memory errors
		- Illegal character (Numeric and alpha only)
		- Integer token too large
		- No valid tokens in file
	
	Returns EXIT_SUCCESS(0) on success.

AUTHOR
	Haneul Chae
	Simon Bruce