#include "env.h"

obj* make_binding(obj* variable, obj* value) {
  return init_cons(variable, value);
} 

obj* make_frame(obj* variables, obj* values) {
  if (is_nil(variables)) return init_nil();
  else return init_cons(make_binding(variables->car, values->car),
			make_frame(variables->cdr, values->cdr));
}

obj* adjoin_binding(obj* binding, obj* frame) {
  return init_cons(binding, frame);
} 
