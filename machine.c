#include "include/machine.h"

void machine_init(Machine* m) {
  m->stack = make_stack();
  ASSERT(m->stack);
}

static void machine_handle_input(Machine* m, const char* input) {
  cprint(DIM, input);
  
}

void machine_repl(Machine* m) {
  char buffer[STDIN_BUFFER_MAX] = {0};

  while (true) {
    printf("> ");
    fgets(buffer, STDIN_BUFFER_MAX, stdin);
    if (buffer[strlen(buffer) - 1] == '\n')
      buffer[strlen(buffer) - 1] = '\0';

    machine_handle_input(m, buffer);
  }
}

void machine_destroy(Machine* m) {
  FREE(m->stack);
}
