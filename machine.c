#include "include/machine.h"
#include "include/lexer.h"

void machine_init(Machine* m) {
  m->stack = make_stack();
  ASSERT(m->stack);
}

static void do_binary_op(Machine* m, TokenType type) {
  Value right = stack_pop(m->stack);
  Value left = stack_pop(m->stack);
  switch (type) {
  case TT_PLUS:
    stack_push(m->stack, left + right);
    break;
  case TT_MINUS:
    stack_push(m->stack, left - right);
    break;
  case TT_SLASH:
    stack_push(m->stack, left / right);
    break;
  case TT_ASTERISK:
    stack_push(m->stack, left * right);
    break;
  default:
    break;
  }
}

// TODO :Return error type
static void evaluate(Machine* m, Token tk) {
  switch (tk.type) {
  case TT_NUMBER:
    stack_push(m->stack, atof(tk.lexeme));
    break;
  case TT_IDENT:
    break;
  case TT_PLUS:
  case TT_MINUS:
  case TT_SLASH:
  case TT_ASTERISK:
    if (m->stack->size >= 2)
      do_binary_op(m, tk.type);
    break;
  case TT_OP_DROP:
    if (!stack_empty(m->stack))
      stack_pop(m->stack);
    break;
  case TT_OP_DUP:
    if (!stack_empty(m->stack))
      stack_push(m->stack, m->stack->top->value);
    break;
  case TT_UNKN:
    plog(ERROR, "Unknown token : %s ", tk.lexeme);
    break;
  case TT_END:
    break;
  }
}

static void machine_handle_input(Machine* m, char* input) {
  Lexer lex;
  Token tk;
  lexer_init(&lex, input);
  
  while (!lexer_finished(&lex)) {
    tk = lexer_next(&lex);
    evaluate(m, tk);
  }
  stack_dump(m->stack);
}

void machine_repl(Machine* m) {
  char buffer[STDIN_BUFFER_MAX] = {0};

  while (true) {
    printf("> ");
    fgets(buffer, STDIN_BUFFER_MAX, stdin);
    if (buffer[strlen(buffer) - 1] == '\n')
      buffer[strlen(buffer) - 1] = '\0';

    machine_handle_input(m, buffer);
  }
}

void machine_destroy(Machine* m) {
  FREE(m->stack);
}
