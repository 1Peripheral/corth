#define PPRINT_IMPL
#include "include/machine.h"

int main(void) {
  Machine machine;
  machine_init(&machine);

  machine_repl(&machine);

  machine_destroy(&machine);
  return 0;
}
