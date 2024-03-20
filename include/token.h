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
  TT_OP_KEY, 
  TT_OP_DUP,
} TokenType;

typedef struct {
  TokenType type;
  char lexeme[MAX_LEXEME_LEN];
} Token;

inline Token token_new(TokenType type, char* lexeme);

Token token_new(TokenType type, char* lexeme) {
  Token tk;
  tk.type = type;
  strncpy(tk.lexeme, lexeme, strlen(lexeme));
  return tk;
}

#endif //TOKEN_H_
