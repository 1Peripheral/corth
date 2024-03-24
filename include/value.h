#ifndef VALUE_H_
#define VALUE_H_

typedef int Value;

typedef enum {
  VALUE_TYPE,
  DEFINITION_TYPE,
} ReferenceType;

typedef struct {
  ReferenceType as;
  union {
    Value var;
    char* expression;
  };
} Reference;

#endif //VALUE_H_
