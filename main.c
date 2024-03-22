#define PPRINT_IMPL
#include "include/machine.h"

// TODO : handle ctrl+c

int main(int argc, char* argv[]) {
  Machine machine;
  machine_init(&machine);

  cprint(BOLD, "Corth Interpreter v0.1");
  machine_repl(&machine);

  machine_destroy(&machine);
  return 0;
}
