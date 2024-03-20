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

void machine_init(Machine* m);
void machine_repl(Machine* m);
void machine_destroy(Machine* m);

#endif //MACHINE_H_
