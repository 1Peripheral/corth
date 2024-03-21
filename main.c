#define PPRINT_IMPL
#include "include/machine.h"
#include "include/lexer.h"

int main(void) {
  Machine machine;
  machine_init(&machine);

  // machine_repl(&machine);
  Lexer lex;
  Token tk;
  lexer_init(&lex, "0000001231231 +  12131 / l4otfi * 1oumnia");

  while (!lexer_finished(&lex)) {
    tk = lexer_next(&lex);
    pprint("%03d : %s ", tk.type, tk.lexeme);
  }

  machine_destroy(&machine);
  return 0;
}
