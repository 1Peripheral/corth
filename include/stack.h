#ifndef STACK_H_
#define STACK_H_

#include "common.h"

#ifndef MAX_STACK_CAPACITY
  #define MAX_STACK_CAPACITY 256
#endif

#define PRINT_VALUE(v) cprint(DIM, "%g", v)

typedef float Value;

typedef struct Element {
  Value value;
  struct Element* next; 
} Element;

typedef struct {
  Element* top;
  int size;
  int capacity;
} Stack;

Element* new_element(Value value);

Stack* make_stack();
void stack_push(Stack* stack, Value value);
Value stack_pop(Stack* stack);
Value stack_pop_at(Stack* stack, int index);
bool stack_empty(Stack* stack);
void stack_dump(Stack* stack);
void stack_free(Stack* stack);

#endif //STACK_H_
