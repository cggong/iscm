/* The implementation of bindings, frames and environments
 * uses LISP's object system. This is because variables are
 * bounded to LISP objects. 
 */ 

#include "types.h"

obj* make_binding(obj* variable, obj* value); 

obj* make_frame(cons* variables, cons* values); 

obj* adjoin_binding(obj* binding, obj* frame); 
