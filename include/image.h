#ifndef IMAGE_H
#define IMAGE_H

#include "dimensions.h"
#include "pixel.h"

struct image {
  struct dimensions dims;
  struct pixel *data;
};

struct image image_create(struct dimensions);
void image_destroy(struct image *);

#endif
