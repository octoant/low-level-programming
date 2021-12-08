#include <malloc.h>
#include "image.h"

static inline size_t calc_size(uint64_t width, uint64_t height) {
  return width * height * sizeof(struct pixel);
}

struct image image_create(uint64_t width, uint64_t height) {
  return (struct image) { width, height, malloc(calc_size(width, height)) };
}

void image_destroy(struct image img) { free(img.data); }
