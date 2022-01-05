#include "transform.h"

struct image rotate_left(struct image const src) {
  struct dimensions dims = dimensions_reverse(src.dims);
  struct image img = image_create(dims);
  for (uint32_t i = 0; i < dims.width; i = i + 1) {
    for (uint32_t j = 0; j < dims.height; j = j + 1) {
      img.data[i + j * dims.width] =
          src.data[(dims.width - i - 1) * dims.height + j];
    }
  }
  return img;
}
