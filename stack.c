#include <stdlib.h>
#include <stdio.h>
#include "include/stack.h"

Element* new_element(Value value) {
  Element* new = (Element*) MALLOC(sizeof(Element));
  ASSERT(new != NULL);
  
  new->value = value;
  new->next = NULL;
  return new;
}

Stack* make_stack() {
  Stack* new = (Stack*) MALLOC(sizeof(Stack));
  ASSERT(new != NULL);

  new->top = NULL;
  new->capacity = MAX_STACK_CAPACITY;
  new->size = 0;
  return new; 
}

void stack_push(Stack* stack, Value value) {
  ASSERT(stack != NULL);
  ASSERT(stack->size < stack->capacity);
  Element* new = new_element(value);

  new->next = stack->top;
  stack->top = new; 
  stack->size++;
}

Value stack_pop(Stack* stack) {
  ASSERT(stack != NULL && "Stack is null");
  ASSERT(stack-> top != NULL && "Tried to pop an empty stack");

  Element* popped = stack->top;
  Value value = popped->value;

  stack->top = popped->next;
  FREE(popped);
  return value;
}

void stack_dump(Stack* stack) {
  if (!stack) return;
  
  Element* current = stack->top;

  printf("STACK DUMP :\n");
  while (current) {
    printf("%d\n", current->value);
    current = current->next;
  }
}

void stack_free(Stack* stack) {
  FREE(stack);
}
