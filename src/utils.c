#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

_Noreturn void err(const char *msg, ...) {
  va_list args;
  va_start(args, msg);
  vfprintf(stderr, msg, args);
  va_end(args);
  abort();
}

extern inline size_t max_size(size_t x, size_t y);