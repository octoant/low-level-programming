#include "dimensions.h"

struct dimensions dimensions_create(uint32_t width, uint32_t height) {
  return (struct dimensions) { width, height };
}

struct dimensions dimensions_reverse(struct dimensions dims) {
  return (struct dimensions) { dims.height, dims.width };
}
