#include "eval.h"

obj* plus(obj* a, obj* b) {
  return init_number(*(double*)a->contents + *(double*)b->contents);
}

obj* mult(obj* a, obj* b) {
  return init_number(*(double*)a->contents * *(double*)b->contents);
} 

obj* apply_plus(list* lst) {
  if (length(lst) == 2) {
    return plus(car(lst), car(cdr(lst)));
  } else {
    return plus(car(lst), apply_plus(cdr(lst)));
  }
} 
    
obj* apply_mult(list* lst) {
  if (length(lst) == 2) {
    return mult(car(lst), car(cdr(lst)));
  } else {
    return mult(car(lst), apply_mult(cdr(lst)));
  }
}

obj* apply_primitive(obj* operator, obj* operand_list) {
  switch (*(char*)operator->contents) {
  case '+':
    return apply_plus(operand_list);
  case '*':
    return apply_mult(operand_list);
  }
}

list* eval_elements_of_list(list* l) {
  int len = length(l); 
  if (len == 0) {
    return init_nil();
  } else if (len == 1) {
    return init_list(eval(car(l)));
  } else {
    return append(init_list(eval(car(l))), eval_elements_of_list(cdr(l)));
  }
}

int is_self_eval(obj* o) {
  return o->type == ATOM_NUMBER;
} 

obj* eval(list* l) {
  if (is_self_eval(l)) return l; 
  return apply_primitive(car(l), eval_elements_of_list(cdr(l)));
} 
