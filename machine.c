#include "include/machine.h"
#include "include/lexer.h"

void machine_init(Machine* m) {
  m->stack = make_stack();
  ASSERT(m->stack);
}

static void machine_handle_input(Machine* m, char* input) {
  Lexer lex;
  Token tk;
  lexer_init(&lex, input);
  
  while (!lexer_finished(&lex)) {
    tk = lexer_next(&lex);
    token_print(tk);
  }
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
