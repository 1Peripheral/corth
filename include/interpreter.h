#ifndef MACHINE_H_ 
#define MACHINE_H_ 

#include "common.h"
#include "stack.h"
#include "pprint.h"

#define STDIN_BUFFER_MAX 256


typedef struct {
  Stack* stack; 
  // constants
  // variables
} Machine;

typedef enum {
  SUCCESS,
  SYNTAX_ERROR,
  UNDERFLOW_ERROR,
} Execution_Result;

void interpreter_init(Machine* m);
void interpreter_repl(Machine* m);
void interpreter_destroy(Machine* m);

#endif //MACHINE_H_
