#include "include/lexer.h"

void lexer_init(Lexer* lexer, char* program) {
  lexer->source = program;
  lexer->curr = 0;
  lexer->curr_char = lexer->source[0];
}

static void lexer_next_char(Lexer* lexer) {
  (lexer->curr)++;
  if (lexer->curr >= strlen(lexer->source)) {
    lexer->curr_char = '\0';
    return;
  }
  lexer->curr_char = lexer->source[lexer->curr];
} 

Token lexer_next(Lexer* lexer) {
  // TODO : increment pointer , modify the way i handle tokens
  Token tk;
  switch (lexer->curr_char) {
  case '+':
    tk.type = TT_PLUS;
    break;
  case '-':
    return (Token){TT_MINUS, lexer->curr_char};
  case '*':
    return (Token){TT_ASTERISK, lexer->curr_char};
  case '/':
    return (Token){TT_SLASH, lexer->curr_char};
  default:
    break;
  }
  return (Token){TT_UNKN, NULL};
}

bool lexer_finished(const Lexer* lexer) {
  return strlen(lexer->source) - 1 <= lexer->curr || lexer->curr_char == '\0';
}
