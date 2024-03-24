#ifndef TOKEN_H_
#define TOKEN_H_

#include <string.h>

#define MAX_LEXEME_LEN 128

typedef enum {
  TT_UNKN,
  TT_NUMBER,
  TT_IDENT,
  TT_PLUS,
  TT_MINUS,
  TT_SLASH,
  TT_ASTERISK,
  TT_EQUAL,
  TT_GREATER,
  TT_LOWER,
  TT_OP_POP, 
  TT_OP_DUP,
  TT_OP_SWAP,
  TT_OP_OVER,
  TT_OP_ROT,
  TT_OP_EMIT,
  TT_OP_PERIOD,
  TT_OP_CR,
  TT_OP_PRINTSTR,
  TT_OP_VAR,
  TT_OP_ASSIGN,
  TT_OP_DEREF,
  TT_END,
} TokenType;

extern const char *TOKENS[];

typedef struct {
  TokenType type;
  char lexeme[MAX_LEXEME_LEN];
} Token;

void token_print(Token tk);

#endif //TOKEN_H_
