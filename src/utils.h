#ifndef _UTILS_H
#define _UTILS_H

#include <stddef.h>

_Noreturn void err(const char *msg, ...);

inline size_t size_max(size_t x, size_t y) {
  return x >= y ? x : y;
}

#endif
