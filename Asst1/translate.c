#include <stdlib.h>

#include "translate.h"

char *fromCntrl(char aChar)
{
  char *arr = (char *)malloc(sizeof(char) * 2);
  switch (aChar)
  {
  case ' ':
    return " ";
    break;
  case '\n':
    return "\\n";
    break;
  case '\r':
    return "\\r";
    break;
  case '\t':
    return "\\t";
    break;
  case '\v':
    return "\\v";
    break;
  case '\f':
    return "\\f";
    break;
  case '\a':
    return "\\a";
    break;
  case '\b':
    return "\\b";
    break;
  default:
    arr[0] = aChar;
    arr[1] = '\0';
    return arr;
    break;
  }
}

char *toCntrl(char *word)
{
  switch (word[1])
  {
  case 'n':
    return "\n";
    break;
  case 'r':
    return "\r";
    break;
  case 't':
    return "\t";
    break;
  case 'v':
    return "\v";
    break;
  case 'f':
    return "\f";
    break;
  case 'a':
    return "\a";
    break;
  case 'b':
    return "\b";
    break;
  default:
    return "";
    break;
  }
}