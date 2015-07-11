#include "lex.h"
#include "types.h"
#include <stdio.h>

int main(void) {
  char* cmd = "(+ 1 (* 3 (/ 9 6)))";
    //"(define (square x) (* x x))"; 
  char** toks = lex(cmd);
  /*
  int i = 0;
  char* tok; 
  while ((tok = toks[i++])) {
    printf("%s\n", tok);
  }
  */
  tree* syn = init_tree(toks);
  desymbolize_tree(syn); 
  print_tree(syn); 
} 
