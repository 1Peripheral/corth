#include "include/interpreter.h"
#include "include/lexer.h"

void interpreter_init(Machine* m) {
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
  case TT_OP_SWAP:
    stack_push(m->stack, right);
    stack_push(m->stack, left);
    break;
  case TT_OP_OVER:
    stack_push(m->stack, left);
    stack_push(m->stack, right);
    stack_push(m->stack, left);
    break;
  case TT_EQUAL:
    stack_push(m->stack, left == right ? -1 : 0);
    break;
  case TT_GREATER: 
    stack_push(m->stack, left > right ? -1 : 0);
    break;
  case TT_LOWER:
    stack_push(m->stack, left < right ? -1 : 0);
    break;
  default:
    break;
  }
}

static void do_unary_op(Machine* m, TokenType type) {
  switch (type) {
  case TT_OP_POP:
    stack_pop(m->stack);
    break;
  case TT_OP_DUP:
    stack_push(m->stack, m->stack->top->value);
    break;
  case TT_OP_PERIOD:
    PRINT_VALUE(stack_pop(m->stack));
    break;
  case TT_OP_EMIT:
    dim_on();
    printf("%c", (int)stack_pop(m->stack));
    reset_console();
    break;
  default:
    break;
  }
}

static Execution_Result evaluate(Machine* m, Token tk) {
  switch (tk.type) {
  case TT_NUMBER:
    stack_push(m->stack, atof(tk.lexeme));
    break;
  case TT_IDENT:
    break;
  case TT_PLUS: case TT_MINUS: case TT_SLASH: 
  case TT_ASTERISK: case TT_OP_SWAP: case TT_OP_OVER:
  case TT_EQUAL: case TT_GREATER: case TT_LOWER:
    if (m->stack->size < 2)
      return UNDERFLOW_ERROR;
    do_binary_op(m, tk.type);
    break;
  case TT_OP_POP: case TT_OP_DUP: case TT_OP_PERIOD:
  case TT_OP_EMIT:
    if (stack_empty(m->stack))
      return UNDERFLOW_ERROR;
    do_unary_op(m, tk.type);
    break;
  case TT_OP_ROT:
    if (m->stack->size < 3)
      return UNDERFLOW_ERROR;
    Value val = stack_pop_at(m->stack, 2);
    stack_push(m->stack, val);
    break;
  case TT_OP_CR:
    printf("\n");
    break;
  case TT_OP_PRINTSTR:
    // TODO 
    plog(DEBUG, "TODO");
    break;
  case TT_UNKN:
    return SYNTAX_ERROR;
    break;
  case TT_END:
    break;
  }
  return SUCCESS; 
}

static void interpreter_handle_instruction(Machine* m, char* input) {
  Lexer lex;
  Token tk;
  lexer_init(&lex, input);
  
  while (!lexer_finished(&lex)) {
    tk = lexer_next(&lex);
    switch (evaluate(m, tk)) {
    case SUCCESS:
      break;
    case SYNTAX_ERROR:
      plog(ERROR, "Syntax Error");
      return;
    case UNDERFLOW_ERROR:
      plog(WARNING, "Underflow");
      return;
    }
  }
}

static void interpreter_handle_command(Machine* m, char* buffer) {
  buffer++;
  if (!strcmp(buffer, "dump_stack")) {
    stack_dump(m->stack);
  }
  else if (!strcmp(buffer, "exit")) {
    exit(0);
  }
  else if (!strcmp(buffer, "clear")) {
    printf("\033[2J\033[H\n");
  }
  else {
    plog(ERROR, "Unknown command");
  }
}

void interpreter_repl(Machine* m) {
  char buffer[STDIN_BUFFER_MAX] = {0};

  while (true) {
    printf("#> ");
    fgets(buffer, STDIN_BUFFER_MAX, stdin);
    if (buffer[strlen(buffer) - 1] == '\n')
      buffer[strlen(buffer) - 1] = '\0';

    if (buffer[0] == '@')
      interpreter_handle_command(m, buffer);
    else
      interpreter_handle_instruction(m, buffer);
  }
}

void interpreter_destroy(Machine* m) {
  FREE(m->stack);
}
