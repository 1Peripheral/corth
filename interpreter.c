#include "include/interpreter.h"
#include "include/lexer.h"

void interpreter_init(Interpreter* i) {
  i->stack = make_stack();
  ASSERT(i->stack);
}

static void do_binary_op(Interpreter* i, TokenType type) {
  Value right = stack_pop(i->stack);
  Value left = stack_pop(i->stack);
  switch (type) {
  case TT_PLUS:
    stack_push(i->stack, left + right);
    break;
  case TT_MINUS:
    stack_push(i->stack, left - right);
    break;
  case TT_SLASH:
    stack_push(i->stack, left / right);
    break;
  case TT_ASTERISK:
    stack_push(i->stack, left * right);
    break;
  case TT_OP_SWAP:
    stack_push(i->stack, right);
    stack_push(i->stack, left);
    break;
  case TT_OP_OVER:
    stack_push(i->stack, left);
    stack_push(i->stack, right);
    stack_push(i->stack, left);
    break;
  case TT_EQUAL:
    stack_push(i->stack, left == right ? -1 : 0);
    break;
  case TT_GREATER: 
    stack_push(i->stack, left > right ? -1 : 0);
    break;
  case TT_LOWER:
    stack_push(i->stack, left < right ? -1 : 0);
    break;
  default:
    break;
  }
}

static void do_unary_op(Interpreter* i, TokenType type) {
  switch (type) {
  case TT_OP_POP:
    stack_pop(i->stack);
    break;
  case TT_OP_DUP:
    stack_push(i->stack, i->stack->top->value);
    break;
  case TT_OP_PERIOD:
    PRINT_VALUE(stack_pop(i->stack));
    break;
  case TT_OP_EMIT:
    dim_on();
    printf("%c", (int)stack_pop(i->stack));
    reset_console();
    break;
  default:
    break;
  }
}

static Execution_Result print_string(Interpreter* i) {
  char string[PRINT_BUFFER_MAX];
  int idx = 0;
  while (i->lex.curr_char != '"') {
    if ( i->lex.curr_char == '\0')
      return SYNTAX_ERROR;
    string[idx++] = i->lex.curr_char;
    lexer_next_char(&i->lex);
  }
  lexer_next_char(&i->lex);
  printf("%s", string);
  return SUCCESS;
}

static Execution_Result evaluate(Interpreter* i, Token tk) {
  switch (tk.type) {
  case TT_NUMBER:
    stack_push(i->stack, atof(tk.lexeme));
    break;
  case TT_IDENT:
    break;
  case TT_PLUS: case TT_MINUS: case TT_SLASH: 
  case TT_ASTERISK: case TT_OP_SWAP: case TT_OP_OVER:
  case TT_EQUAL: case TT_GREATER: case TT_LOWER:
    if (i->stack->size < 2)
      return UNDERFLOW_ERROR;
    do_binary_op(i, tk.type);
    break;
  case TT_OP_POP: case TT_OP_DUP: case TT_OP_PERIOD:
  case TT_OP_EMIT:
    if (stack_empty(i->stack))
      return UNDERFLOW_ERROR;
    do_unary_op(i, tk.type);
    break;
  case TT_OP_ROT:
    if (i->stack->size < 3)
      return UNDERFLOW_ERROR;
    Value val = stack_pop_at(i->stack, 2);
    stack_push(i->stack, val);
    break;
  case TT_OP_CR:
    printf("\n");
    break;
  case TT_OP_PRINTSTR:
    return print_string(i);
    break;
  case TT_UNKN:
    return SYNTAX_ERROR;
    break;
  case TT_END:
    break;
  }
  return SUCCESS; 
}

static void interpreter_handle_instruction(Interpreter* i, char* input) {
  Token tk;
  lexer_init(&i->lex, input);
  
  while (!lexer_finished(&i->lex)) {
    tk = lexer_next(&i->lex);
    switch (evaluate(i, tk)) {
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

static void interpreter_handle_command(Interpreter* i, char* buffer) {
  buffer++;
  if (!strcmp(buffer, "dump_stack")) {
    stack_dump(i->stack);
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

void interpreter_repl(Interpreter* i) {
  char buffer[STDIN_BUFFER_MAX] = {0};

  while (true) {
    printf("#> ");
    fgets(buffer, STDIN_BUFFER_MAX, stdin);
    if (buffer[strlen(buffer) - 1] == '\n')
      buffer[strlen(buffer) - 1] = '\0';

    if (buffer[0] == '@')
      interpreter_handle_command(i, buffer);
    else
      interpreter_handle_instruction(i, buffer);
  }
}

void interpreter_destroy(Interpreter* i) {
  FREE(i->stack);
}
