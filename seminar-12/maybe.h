#ifndef MAYBE_H
#define MAYBE_H

#include <stdbool.h>

#define DECLARE_MAYBE_HEADER(name, type)                                  \
  struct maybe_##name {                                                   \
    bool ok;                                                              \
    type value;                                                           \
  };                                                                      \
  struct maybe_##name some_##name(type value);                            \
  extern struct maybe_##name none_##name;

#define DECLARE_MAYBE_SRC(name, type)                                     \
  struct maybe_##name some_##name(type value) {                           \
    return (struct maybe_##name) { .ok = true, .value = value };   \
  }                                                                       \
  struct maybe_##name none_##name = { 0 };

#endif