#include <malloc.h>
#include "image.h"

static inline size_t calc_size(struct dimensions dims) {
  return dims.width * dims.height * sizeof(struct pixel);
}

struct image image_create(struct dimensions dims) {
  return (struct image) { dims, malloc(calc_size(dims)) };
}

void image_destroy(struct image *img) { free(img->data); }
