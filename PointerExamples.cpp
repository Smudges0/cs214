// PointerExamples.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
using namespace std;

void refFunc(string &); // Parameter is a string reference, pass in a value
void ptrFunc(string *); // Parameter is a string pointer, pass in a pointer
void doubleInput(int *); // Parameter is an int pointer, pass in a pointer
void switchValue(int **, int *);

int main()
{
	// Simple pointer
	int val = 42;
	cout << "val = " << val << endl;
	int * ptr = &val;
	cout << "ptr = " << ptr << endl;
	cout << "ptr val = " << *ptr << endl;
	cout << endl;

	// Simple reference
	//int & ref2; // Must initialize the reference when it is declared
	//int & ref = 44; // Cannot initialize a reference to a literal
	int val2 = 44;
	int & ref = val2; // Initialize from a value variable.
	cout << "ref ptr = " << &ref << endl;
	cout << "ref is " << ref << endl;
	cout << endl;

	// Reference from pointer value
	//int & ref2 = ptr; // Refs cannot point to pointers, only to values.
	int & ref2 = *ptr;
	cout << "ref2 ptr = " << &ref2 << endl;
	cout << "ref2 is " << ref2 << endl;
	cout << endl;

	// This looks like ref2 but is NOT a reference!!!!  It's just an int with a different address, and a COPY of the value.
	int ref3 = *ptr;
	cout << "ref3 ptr = " << &ref3 << endl;
	cout << "ref3 is " << ref3 << endl;
	cout << endl;

	// Arrays and pointers
	int ints[10] = { 1,2,3,4,5,6,7,8,9,10 };
	int * intptr = ints;
	cout << "ints is " << ints << endl;					// Address of first element
	cout << "intptr ptr = " << intptr << endl;			// Address of first element
	cout << "intptr value is " << *intptr << endl;		// 1
	cout << "int[1] is " << ints[1] << endl;			// 2
	cout << "&int[1] is " << &ints[1] << endl;			// Address of second element
	cout << "intptr 1 is " << *(intptr + 1) << endl;	// 2
	cout << endl;

	// Char arrays - Old C strings
	char str[] = "Hello world"; // Old C string (C++ has string objects now)
	char * strptr = str;
	//const char *strptr3 = "Hello world";  // Same thing as above. Also works.  But must use const with a literal.
	cout << "str is " << str << endl;					// Hello world <--- ? Why not the address?  cout handles char * specially.
	cout << "strptr ptr = " << strptr << endl;			// Hello world <--- ? Why not the address?  cout handles char * specially.
	cout << "strptr value is " << *strptr << endl;		// H
	cout << "str[1] is " << str[1] << endl;				// e
	cout << "&str[1] is " << &str[1] << endl;			// ello world <----- ? why  Because of cout
	cout << "strptr 1 is " << *(strptr + 1) << endl;	// e
	cout << endl;

	// Answer to why cout prints the whole string instead of the address of the first char:
	// https://stackoverflow.com/questions/17813423/cout-with-char-argument-prints-string-not-pointer-value
	// "std::cout will treat a char * as a pointer to (the first character of) a C-style string and print it as such."
	//
	// To get the address, cast the char pointer to a different pointer type like a void pointer.
	cout << "strptr void ptr = " << static_cast <const void *>(strptr) << endl;			// 
	cout << endl;

	// Or create the char pointer differently so it is a pointer to an array of 12 chars instead of a pointer to a string.
	char (*strptr2)[12] = &str; // This is a pointer to an array of 12 chars (instead of pointer to a string)
	cout << "strptr2 ptr = " << strptr2 << endl;		// 0046F76C - As expected
	cout << "strptr2 value is " << *strptr2 << endl;	// Hello world
	cout << endl;

	// Call function by reference and change original value
	string strVal = "test";
	cout << strVal << " before calling refFunc\n";
	refFunc(strVal); // Pass in value and function converts to a reference, then we change it
	cout << strVal << " after calling refFunc\n";
	cout << endl;

	// Call function by pointer and change original value
	strVal = "test";
	string *strValPtr = &strVal;
	cout << strVal << " before calling ptrFunc\n";
	ptrFunc(strValPtr); // Pass in pointer, then we dereference it and change it
	cout << strVal << " after calling ptrFunc\n";
	cout << endl;

	// Double Pointers
	val = 3;
	cout << "val = " << val << endl;
	cout << "&val = " << &val << endl;
	int* valPtr = &val;
	cout << "valPtr = " << valPtr << endl;
	cout << "*valPtr = " << *valPtr << endl;
	doubleInput(&val);
	cout << "new val = " << val << endl;
	cout << endl;

	val2 = 20;
	cout << "&val = " << &val << endl;
	cout << "&val2 = " << &val2 << endl;
	cout << "valPtr = " << valPtr << endl;
	cout << "*valPtr = " << *valPtr << endl;
	cout << endl;
	switchValue(&valPtr, &val2);
	cout << "&val = " << &val << endl;
	cout << "&val2 = " << &val2 << endl;
	cout << "valPtr = " << valPtr << endl;
	cout << "*valPtr = " << *valPtr << endl;
	cout << endl;

}

void refFunc(string &strVal)
{
	strVal = "changed";
}

void ptrFunc(string *strValPtr)
{
	*strValPtr = "changed";
}

void doubleInput(int* input)
{
	// Dereference the pointer to provide access:
	// *input refers the the value held by the memory address input.
	// By dereferencing the address, we can directly amend what is stored there
	// from within the function.
	cout << "input = " << input << endl;
	cout << "*input = " << *input << endl;
	cout << "&input = " << &input << endl;
	*input = *input + *input;
}

void switchValue(int** input, int* input2)
{
	cout << "input = " << input << endl;
	cout << "*input = " << *input << endl;
	cout << "**input = " << **input << endl;
	cout << "input2 = " << input2 << endl;
	cout << "*input2 = " << *input2 << endl;
	cout << endl;

	*input = input2;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
