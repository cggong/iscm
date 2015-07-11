#pragma once

typedef enum {
  ATOM_NUMBER, 
  ATOM_SYMBOL,
  ATOM_STRING, 
  ATOM_FUNCPTR,
  ATOM_NIL, 
  PAIR, 
} lsp_type; 

typedef struct obj_rec {
  lsp_type type;
  void* contents;
} obj;

typedef struct pair_rec {
  obj* a;
  obj* b;
} pair;

typedef obj list; 

obj* init_obj(lsp_type type, void* contents); 

obj* init_symbol(const char* name);

obj* init_number(double d); 

void print_obj(obj* o); 

int is_nil(obj* o); 

obj* init_nil();

void desymbolize_obj(obj* o); 

/* To conform with the naming convention in this program, this function
 * should be called init_pair. However, since LISP has name for this 
 * important function, for this case we shall conform to the naming 
 * convention of LISP. 
 */
obj* cons(obj* a, obj* b);

obj* car(obj* o);

obj* cdr(obj* o); 

int is_atom(obj* o);

obj* init_list(obj* o); 

/* append two lists */
obj* append(obj* x, obj* y);

/* append object to list */
obj* append_obj(obj* x, obj* y); 

obj* read_toks(char** toks); 

int length(obj* o); 
