#ifndef LEXER_H_
#define LEXER_H_

#include "common.h"
#include "token.h"

typedef struct {
  char* source;
  int curr;
  char curr_char;
} Lexer;

void lexer_init(Lexer* lexer, char* program);
Token lexer_next(Lexer* lexer);
bool lexer_finished(const Lexer* lexer);

#endif //LEXER_H_
