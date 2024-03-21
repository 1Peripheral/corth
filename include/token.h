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
  TT_OP_DROP, 
  TT_OP_DUP,
  TT_END,
} TokenType;

extern const char *TOKENS[];

typedef struct {
  TokenType type;
  char lexeme[MAX_LEXEME_LEN];
} Token;

void token_print(Token tk);

#endif //TOKEN_H_
