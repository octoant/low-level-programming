#ifndef BMP_H
#define BMP_H

#include <stdio.h>
#include "file.h"
#include "image.h"

enum read_status from_bmp(FILE *, struct image *);
enum write_status to_bmp(FILE *, struct image const *);

#endif
