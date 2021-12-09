#include "bmp.h"

#define FOR_BMP_HEADER(FOR_FIELD)                                     \
  FOR_FIELD(uint16_t, bfType)                                         \
  FOR_FIELD(uint32_t, bfileSize)                                      \
  FOR_FIELD(uint32_t, bfReserved)                                     \
  FOR_FIELD(uint32_t, bOffBits)                                       \
  FOR_FIELD(uint32_t, biSize)                                         \
  FOR_FIELD(uint32_t, biWidth)                                        \
  FOR_FIELD(uint32_t, biHeight)                                       \
  FOR_FIELD(uint16_t, biPlanes)                                       \
  FOR_FIELD(uint16_t, biBitCount)                                     \
  FOR_FIELD(uint32_t, biCompression)                                  \
  FOR_FIELD(uint32_t, biSizeImage)                                    \
  FOR_FIELD(uint32_t, biXPelsPerMeter)                                \
  FOR_FIELD(uint32_t, biYPelsPerMeter)                                \
  FOR_FIELD(uint32_t, biClrUsed)                                      \
  FOR_FIELD(uint32_t, biClrImportant)

#define DECLARE_FIELD(type, name) type name;

struct __attribute__((packed)) bmp_header {
  FOR_BMP_HEADER(DECLARE_FIELD)
};

enum read_status from_bmp(FILE *in, struct image *img) {
  return READ_OK;
}

enum write_status to_bmp(FILE *out, struct image const *img) {
  return WRITE_OK;
}