#include "types.h"
#include "strhlp.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
//#define DEBUG
#ifdef DEBUG
#define DBG(x) printf x
#else
#define DBG(x) do {} while (0)
#endif

obj* init_obj(lsp_type type, void* contents) {
  obj* new_obj = calloc(1, sizeof(obj));
  new_obj->type = type;
  new_obj->contents = contents; 
  return new_obj;
}

obj* init_symbol(const char* name) {
  return init_obj(ATOM_SYMBOL, init_str(name));
}

tree* init_tree_bare(tree* parent, obj* o) {
  tree* new_tree = calloc(1, sizeof(tree));
  new_tree->o = o;
  new_tree->parent = parent; 
  return new_tree;
}

void append_tree_with_subtree(tree* t, tree* subtree) {
  tree* child = t->first_child; 
  if (child) {
    while (child->next_sibling) child = child->next_sibling;
    child->next_sibling = subtree; 
  } else {
    t->first_child = subtree; 
  }
} 

static int scan_ind = 0; 

/* Takes in an array of lexed symbols, and output AST. 
 */
tree* init_tree_recur(tree* parent, char** toks) {
  tree* t;
  #ifdef DEBUG
  printf("call init_tree_recur, scan_ind at \"%s\".\n", toks[scan_ind]);
  #endif
  switch (toks[scan_ind][0]) {
  case '(':
    DBG(("subtree root at \"%s\".\n", toks[scan_ind+1])); 
    t = init_tree_bare(parent, init_symbol(toks[++scan_ind]));
    scan_ind++; 
    while (toks[scan_ind][0] != ')') {
      #ifdef DEBUG
      printf("continue exploring \"%s\".\n", toks[scan_ind]);
      #endif
      append_tree_with_subtree(t, init_tree_recur(t, toks));
    }
    scan_ind++; //scan over the right paren.
    break;
  default:
    t = init_tree_bare(parent, init_symbol(toks[scan_ind++]));
  }
  return t;
}

tree* init_tree(char** toks) {
  scan_ind = 0;
  return init_tree_recur(NULL, toks);
}

void printf_ind(int print_ind, const char* restrict format, ...) {
  for (int i = 0; i < print_ind; i++) printf("  ");
  va_list args;
  va_start(args, format); 
  vprintf(format, args);
  va_end(args); 
} 

void print_tree_recur(tree* t, int print_ind) {
  switch (t->o->type) {
  case ATOM_NUMBER:
    printf_ind(print_ind, "%lf\n", *(double*)t->o->contents);
    break;
  default:
    printf_ind(print_ind, "%s\n", t->o->contents);
  } 
  for (tree* child = t->first_child; child != NULL; child = child->next_sibling) {
    print_tree_recur(child, print_ind + 1); 
  }
}

void print_tree(tree* t) {
  print_tree_recur(t, 0);
} 

obj* init_cons(obj* car, obj* cdr) {
  cons* c = malloc(sizeof(cons));
  c->car = car;
  c->cdr = cdr;
  return init_obj(CONS, c);
}

int is_nil(obj* o) {
  return o->type == ATOM_NIL;
}

obj* init_nil() {
  return init_obj(ATOM_NIL, NULL);
}

void desymbolize_obj(obj* o) {
  if (o->type != ATOM_SYMBOL) return; 
  char* s = o->contents;
  int dot_cnt = 0;
  int len = strlen(s);
  for (int i = 0; i < len; i++) {
    if (!isdigit(s[i])) {
      if (s[i] == '.') {
	dot_cnt++;
      } else return; 
    }
  }
  if (dot_cnt <= 1) {
    double* d = malloc(sizeof(double));
    sscanf(s, "%lf", d);
    o->contents = d;
    o->type = ATOM_NUMBER;
  }
}   

void desymbolize_tree(tree* t) {
  desymbolize_obj(t->o);
  for (tree* child = t->first_child; child != NULL; child = child->next_sibling) {
    desymbolize_tree(child);
  }
} 
