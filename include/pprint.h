#ifndef PPRINT_H_
#define PPRINT_H_

#include <stdarg.h>
#include <stdio.h>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

#define DIM     "\x1b[2m"
#define BOLD    "\x1b[1m"

void pprint(const char* format, ...);
void cprint(const char* color, const char* format, ...);

#ifdef PPRINT_IMPL
void pprint(const char* format, ...) {
  va_list args;
  va_start(args, format);
  vprintf(format, args);
  printf("\n");
  va_end(args);
}

void cprint(const char* color, const char* format, ...) {
  va_list args;
  va_start(args, format);
  printf("%s", color);
  vprintf(format, args);
  printf("%s\n", RESET);
  va_end(args);
}
#endif //PPRINT_IMPL

#endif //PPRINT_H_
