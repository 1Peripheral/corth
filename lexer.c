#include "include/lexer.h"
#include "include/token.h"
#include <ctype.h>

void lexer_init(Lexer* lexer, char* program) {
  lexer->source = program;
  lexer->curr = 0;
  lexer->curr_char = lexer->source[0];
}

void lexer_next_char(Lexer* lexer) {
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

static TokenType lexer_check_keyword(const char* str) {
  for (int i = 0 ; i < TT_END + 1 ; i++) {
    if (!strcmp(str, TOKENS[i])) {
      return i;
    }
  }
  return TT_IDENT;
}

char lexer_peak(const Lexer* lexer) {
  if (lexer->curr + 1 >= strlen(lexer->source))
    return '\0';
  return lexer->source[lexer->curr + 1];
}

static Token lexer_scan_literal(Lexer* lexer) {
  Token tk;
  int start = lexer->curr;
  while (isalnum(lexer->curr_char)) lexer_next_char(lexer);
  strncpy(tk.lexeme, lexer->source + start, lexer->curr - start);
  tk.lexeme[lexer->curr - start] = '\0';
  tk.type = lexer_check_keyword(tk.lexeme);
  return tk;
}

static Token lexer_scan_number(Lexer* lexer) {
  Token tk;
  tk.type = TT_NUMBER;
  int start = lexer->curr;
  while (isdigit(lexer->curr_char)) lexer_next_char(lexer);
  strncpy(tk.lexeme, lexer->source + start, lexer->curr - start);
  tk.lexeme[lexer->curr - start] = '\0';
  return tk;
}

static bool ischar(char c) {
  return c >= '!' && c <= '~'; 
}

static bool iswhitespace(char c) {
  return c == ' ' || c == '\n' || c == '\t' || c == '\r';
}

Token lexer_next(Lexer* lexer) {
  lexer_skip_whitespace(lexer);
  Token tk;
  tk.type = TT_UNKN;
  memset(tk.lexeme, '\0', MAX_LEXEME_LEN);
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
  case '=':
    tk.type = TT_EQUAL;
    tk.lexeme[0] = lexer->curr_char;
    break;
  case '>':
    tk.type = TT_GREATER;
    tk.lexeme[0] = lexer->curr_char;
    break;
  case '<':
    tk.type = TT_LOWER;
    tk.lexeme[0] = lexer->curr_char;
    break;
  case '.':
    tk.type = TT_OP_PERIOD;
    tk.lexeme[0] = lexer->curr_char;
    if (lexer_peak(lexer) == '\"') {
      lexer_next_char(lexer);
      tk.type = TT_OP_PRINTSTR;
      tk.lexeme[1] = '\"';
    }
    break;
  case '!':
    // TODO : handle +!
    tk.type = TT_OP_ASSIGN;
    tk.lexeme[0] = lexer->curr_char;
    if (!iswhitespace(lexer_peak(lexer)) && lexer_peak(lexer) != '\0') 
      tk = lexer_scan_literal(lexer);
    break;
  case '@':
    tk.type = TT_OP_DEREF;
    tk.lexeme[0] = lexer->curr_char;
    if (!iswhitespace(lexer_peak(lexer)) && lexer_peak(lexer) != '\0') 
      tk = lexer_scan_literal(lexer);
    break;
  case '\0':
    tk.type = TT_END;
    tk.lexeme[0] = lexer->curr_char;
    break;
  default:
    if (isdigit(lexer->curr_char))
      tk = lexer_scan_number(lexer);
    else if (ischar(lexer->curr_char))
      tk = lexer_scan_literal(lexer);
    return tk;
  }
  lexer_next_char(lexer);
  return tk;
}

bool lexer_finished(const Lexer* lexer) {
  return lexer->curr >= strlen(lexer->source) || lexer->curr_char == '\0';
}
