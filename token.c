#include "include/token.h"
#include "include/pprint.h"

static const char *TOKENS[TT_END + 1]  = {
  [TT_UNKN]     = "TT_UNKN",
  [TT_NUMBER]   = "TT_NUMBER",
  [TT_IDENT]    = "TT_IDENT",
  [TT_PLUS]     = "TT_PLUS",
  [TT_MINUS]    = "TT_MINUS",
  [TT_SLASH]    = "TT_SLASH",
  [TT_ASTERISK] = "TT_ASTERISK",
  [TT_OP_KEY]   = "TT_OP_KEY",
  [TT_OP_DUP]   = "TT_OP_DUP",
  [TT_END]   = "TT_END",
};

void token_print(Token tk) {
  cprint(DIM, "%-24s : %s", TOKENS[tk.type], tk.lexeme);
}

