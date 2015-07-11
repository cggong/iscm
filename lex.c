/* The job of iscm-lex is that given a string of a LISP expression, 
 * outputs an array consisting of its symbols. Each symbol is represented
 * by a string. 
 */
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "strhlp.h"

int scan_ind; 

char* get_token(char* s) {
  int len = strlen(s);
  while (isspace(s[scan_ind])) scan_ind++; 
  if (s[scan_ind] == '\0') return NULL;
  char* tok = malloc(10 * sizeof(char)); //token
  switch (s[scan_ind]) {
  case '(':
  case ')':
    return init_str_with_char(s[scan_ind++]);
  }
  int j = 0; 
  while (isalph(s[scan_ind])) {
    tok[j++] = s[scan_ind++];
  }
  tok[j] = '\0';
  return tok; 
} 

char** lex(char* s) {
  int len = strlen(s);
  char** toks = malloc(50 * sizeof(char*)); //tokens
  int tokc = 0;
  char* tok;
  scan_ind = 0; 
  while ((tok = get_token(s))) {
    toks[tokc++] = tok;
  }
  toks[tokc] = NULL;
  return toks; 
} 
