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
  obj* o = init_obj(ATOM_SYMBOL, init_str(name));
  desymbolize_obj(o);
  return o; 
}

obj* init_number(double d) {
  double* new_d = malloc(sizeof(double));
  *new_d = d;
  return init_obj(ATOM_NUMBER, new_d);
} 

static int scan_ind = 0; 

/* Takes in an array of lexed symbols, and output the code as data. 
 */

obj* read_toks_recur(char** toks) {
  obj* o;
  DBG(("call read_toks_recur, scan_ind at \"%s\".\n", toks[scan_ind])); 
  switch (toks[scan_ind][0]) {
  case '(':
    o = init_list(init_symbol(toks[++scan_ind]));
    scan_ind++; 
    while (toks[scan_ind][0] != ')') {
      o = append_obj(o, read_toks_recur(toks));
    }
    scan_ind++; //scan over the right paren.
    break;
  default:
    o = init_symbol(toks[scan_ind++]);
  }
  return o;
}

obj* read_toks(char** toks) {
  scan_ind = 0;
  return read_toks_recur(toks);
} 

void printf_ind(int print_ind, const char* restrict format, ...) {
  for (int i = 0; i < print_ind; i++) printf("  ");
  va_list args;
  va_start(args, format); 
  vprintf(format, args);
  va_end(args); 
} 

void print_obj_recur(int p_ind, obj* o) {
  obj* b = cdr(o);
  switch (o->type) {
  case ATOM_NUMBER:
    printf_ind(p_ind, "%lf\n", *(double*)o->contents);
    break;
  case PAIR:
    printf_ind(p_ind, "(\n");
    if (b->type == ATOM_NIL) {
      print_obj_recur(p_ind + 1, car(o)); 
      /* A list with one element */
    } else if (b->type != PAIR) {
      /* A cons */
      print_obj_recur(p_ind + 1, car(o)); 
      printf_ind(p_ind, ".");
      print_obj_recur(p_ind + 1, cdr(o));
    } else {
      /* A list */
      for (obj* iter = o; iter->type != ATOM_NIL; iter = cdr(iter)) {
	print_obj_recur(p_ind + 1, car(iter));
	if ((cdr(iter)->type != PAIR)
	    && (cdr(iter)->type != ATOM_NIL)) {
	  printf_ind(p_ind, ".");
	  print_obj_recur(p_ind + 1, cdr(o));
	}
      } 
    }
    printf_ind(p_ind, ")\n"); 
    break; 
  default:
    printf_ind(p_ind, "%s\n", o->contents);
  }
}

void print_obj(obj* o) {
  print_obj_recur(0, o);
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

obj* cons(obj* a, obj* b) {
  pair* new_pair = malloc(sizeof(pair));
  new_pair->a = a;
  new_pair->b = b;
  return init_obj(PAIR, new_pair);
} 

int is_atom(obj* o) {
  return o->type != PAIR;
}

obj* car(obj* o) {
  return ((pair*)o->contents)->a;
} 

obj* cdr(obj* o) {
  return ((pair*)o->contents)->b; 
} 

obj* init_list(obj* o) {
  return cons(o, init_nil());
} 

obj* append(obj* x, obj* y) {
  if (is_nil(x)) {
    return y;
  } else {
    return cons(car(x), append(cdr(x), y));
  }
} 

obj* append_obj(obj* x, obj* y) {
  return append(x, init_list(y));
} 

int length(obj* o) {
  int len = 0; 
  for (obj* iter = o; o->type != ATOM_NIL; o = cdr(o)) {
    len++;
  }
  return len;
} 
