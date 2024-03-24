#ifndef MACHINE_H_ 
#define MACHINE_H_ 

#include "common.h"
#include "stack.h"
#include "lexer.h"
#include "token.h"
#include "kv.h"
#include "pprint.h"

#define STDIN_BUFFER_MAX 256
#define PRINT_BUFFER_MAX 256

typedef struct {
  Lexer lex;
  Stack* stack; 
  KV constants;
  KV definitions;
  // Stored functions
} Interpreter;

typedef enum {
  SUCCESS,
  SYNTAX_ERROR,
  UNDERFLOW_ERROR,
} Execution_Result;

void interpreter_init(Interpreter* m);
void interpreter_repl(Interpreter* m);
void interpreter_destroy(Interpreter* m);

#endif //MACHINE_H_
