#ifndef SEPIA_H
#define SEPIA_H

#include "image.h"

struct image sepia_c_inplace(struct image);
struct image sepia_sse(struct image);

#endif
