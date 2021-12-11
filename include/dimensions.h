#ifndef DIMENSION_H
#define DIMENSION_H

#include <stdint.h>

struct dimensions {
  uint32_t width, height;
};

struct dimensions dimensions_create(uint32_t, uint32_t);
struct dimensions dimensions_reverse(struct dimensions dims);

#endif
