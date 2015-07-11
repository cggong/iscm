#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int isalph(char c) {
  if ((c == '(') || (c == ')')) return 0; 
  return !isspace(c);
}

char* init_str(const char* s) {
  char* new_str = malloc((strlen(s) + 1) * sizeof(char));
  strcpy(new_str, s); 
  return new_str;
} 

char* init_str_with_char(char c) {
  char* new_str = calloc(2, sizeof(char));
  new_str[0] = c;
  return new_str;
} 
