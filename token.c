#include "include/token.h"
#include "include/pprint.h"

const char *TOKENS[TT_END + 1]  = {
  [TT_UNKN]       = "TT_UNKN",
  [TT_NUMBER]     = "TT_NUMBER",
  [TT_IDENT]      = "TT_IDENT",
  [TT_PLUS]       = "TT_PLUS",
  [TT_MINUS]      = "TT_MINUS",
  [TT_SLASH]      = "TT_SLASH",
  [TT_ASTERISK]   = "TT_ASTERISK",
  [TT_EQUAL]      = "TT_EQUAL",
  [TT_GREATER]    = "TT_GREATER",
  [TT_LOWER]      = "TT_LOWER",
  [TT_OP_POP]     = "pop",
  [TT_OP_DUP]     = "dup",
  [TT_OP_SWAP]    = "swap",
  [TT_OP_OVER]    = "over",
  [TT_OP_ROT]     = "rot",
  [TT_OP_EMIT]    = "emit",
  [TT_OP_PERIOD]  = ".",
  [TT_OP_CR]      = "cr",
  [TT_OP_PRINTSTR]= "out\"",
  [TT_OP_VAR]     = "var",
  [TT_OP_ASSIGN]  = "!",
  [TT_OP_DEREF]   = "@",
  [TT_END]        = "TT_END",
};

void token_print(Token tk) {
  cprint(DIM, "%-24s : %s", TOKENS[tk.type], tk.lexeme);
}

