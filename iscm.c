#include "lex.h"
#include "types.h"
#include "eval.h"
#include <stdio.h>

int main(void) {
  char* cmd = "(* 2 3 5 7 (+ 1 (* 3 5 2 3 5)))";
    //"(* 3 5)"; 
    //"(define (square x) (* x x))"; 
  char** toks = lex(cmd);
  /*
  int i = 0;
  char* tok; 
  while ((tok = toks[i++])) {
    printf("%s\n", tok);
  }
  */
  obj* syn = read_toks(toks);
  print_obj(syn);
  obj* result = eval(syn);
  print_obj(result); 
  //desymbolize_tree(syn); 
  //print_tree(syn); 
} 
