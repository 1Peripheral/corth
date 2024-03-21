#include "include/lexer.h"
#include <ctype.h>

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

static void lexer_skip_whitespace(Lexer* lexer) {
  while (lexer->curr_char == '\n' || lexer->curr_char == '\t' || lexer->curr_char == ' ' || lexer->curr_char == '\r')
    lexer_next_char(lexer);
}

Token lexer_next(Lexer* lexer) {
  lexer_skip_whitespace(lexer);
  Token tk;
  tk.type = TT_UNKN;
  tk.lexeme[0] = '\0';
  switch (lexer->curr_char) {
  case '+':
    tk.type = TT_PLUS;
    tk.lexeme[0] = lexer->curr_char;
    break;
  case '-':
    tk.type = TT_MINUS;
    tk.lexeme[0] = lexer->curr_char;
    break;
  case '*':
    tk.type = TT_ASTERISK;
    tk.lexeme[0] = lexer->curr_char;
    break;
  case '/':
    tk.type = TT_SLASH;
    tk.lexeme[0] = lexer->curr_char;
    break;
  case '\0':
    tk.type = TT_END;
    tk.lexeme[0] = lexer->curr_char;
    break;
  default:
    if (isdigit(lexer->curr_char)) {
      tk.type = TT_NUMBER;
      int start = lexer->curr;
      while (isdigit(lexer->curr_char)) lexer_next_char(lexer);
      strncpy(tk.lexeme, lexer->source + start, lexer->curr - start);
      tk.lexeme[lexer->curr - start] = '\0';
    }
    else if (isalpha(lexer->curr_char)) {
      tk.type = TT_IDENT;
      int start = lexer->curr;
      while (isalnum(lexer->curr_char)) lexer_next_char(lexer);
      strncpy(tk.lexeme, lexer->source + start, lexer->curr - start);
      tk.lexeme[lexer->curr - start] = '\0';
    }
    return tk;
  }
  lexer_next_char(lexer);
  return tk;
}

bool lexer_finished(const Lexer* lexer) {
  return strlen(lexer->source) <= lexer->curr || lexer->curr_char == '\0';
}
