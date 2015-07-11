typedef enum {
  ATOM_NUMBER, 
  ATOM_SYMBOL,
  ATOM_STRING, 
  ATOM_FUNCPTR,
  ATOM_NIL, 
  CONS, 
} lsp_type; 

typedef struct obj_rec {
  lsp_type type;
  void* contents;
} obj;

typedef struct cons_rec {
  obj* car;
  obj* cdr;
} cons;

typedef struct tree_rec {
  struct tree_rec* parent;
  struct tree_rec* first_child;
  struct tree_rec* next_sibling;
  obj* o;
} tree; 

obj* init_obj(lsp_type type, void* contents); 

obj* init_symbol(const char* name);

tree* init_tree(char** toks); 

void print_tree(tree* t); 

obj* init_cons(obj* car, obj* cdr); 

int is_nil(obj* o); 

obj* init_nil();

void desymbolize_obj(obj* o); 

void desymbolize_tree(tree* t); 
