#include "vector.h"
#include <stdio.h>

static void print_int_space(int64_t i) {
  printf("%" PRId64 " ", i);
}

int main()
{
  struct vector_int *v = vector_int_create();

  for (int64_t i = 0; i < 100; i++) {
    vector_int_push_back(v, i * i);
  }
  vector_int_for_each(v, print_int_space);
  return 0;
}
