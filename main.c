#define PPRINT_IMPL
#include "include/interpreter.h"

// TODO : handle ctrl+c

int main(int argc, char* argv[]) {
  Machine interpreter;
  interpreter_init(&interpreter);

  cprint(BOLD, "Corth Interpreter v0.1");
  interpreter_repl(&interpreter);

  interpreter_destroy(&interpreter);
  return 0;
}
