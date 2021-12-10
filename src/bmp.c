#include "bmp.h"

#define FOR_HEADER(FOR_FIELD)                                                  \
  FOR_FIELD(uint16_t, bfType)                                                  \
  FOR_FIELD(uint32_t, bfileSize)                                               \
  FOR_FIELD(uint32_t, bfReserved)                                              \
  FOR_FIELD(uint32_t, bOffBits)                                                \
  FOR_FIELD(uint32_t, biSize)                                                  \
  FOR_FIELD(uint32_t, biWidth)                                                 \
  FOR_FIELD(uint32_t, biHeight)                                                \
  FOR_FIELD(uint16_t, biPlanes)                                                \
  FOR_FIELD(uint16_t, biBitCount)                                              \
  FOR_FIELD(uint32_t, biCompression)                                           \
  FOR_FIELD(uint32_t, biSizeImage)                                             \
  FOR_FIELD(uint32_t, biXPelsPerMeter)                                         \
  FOR_FIELD(uint32_t, biYPelsPerMeter)                                         \
  FOR_FIELD(uint32_t, biClrUsed)                                               \
  FOR_FIELD(uint32_t, biClrImportant)

#define DECLARE_FIELD(type, name) type name;

struct __attribute__((packed)) header {
  FOR_HEADER(DECLARE_FIELD)
};

#undef FOR_HEADER
#undef DECLARE_FIELD

static const uint16_t SIGNATURE = 0x4d42;
static const uint32_t HEADER_INFO_SIZE = 40;
static const uint16_t BITS_PER_PIXEL = 24;

static uint32_t get_padding(uint32_t width) { return width % 4; }

static enum read_status read_header(FILE *in, struct header *head) {
  enum read_status retval = READ_OK;
  if (fread(head, sizeof(struct header), 1, in) < 1 ||
      head->biSize != HEADER_INFO_SIZE || head->biPlanes != 1 ||
      head->biBitCount != BITS_PER_PIXEL || head->biCompression != 0)
    retval = READ_INVALID_HEADER;
  else if (head->bfType != SIGNATURE)
    retval = READ_INVALID_SIGNATURE;
  return retval;
}

static enum read_status read_image(FILE *in, struct image *img) {
  enum read_status retval = READ_OK;
  const uint32_t width = img->dims.width, padding = get_padding(width);
  for (uint32_t i = 0; i < img->dims.height; i++) {
    if (fread(&img->data[i * width], sizeof(struct pixel), width, in) <
            width || fseek(in, padding, SEEK_CUR) != 0) {
      retval = READ_INVALID_BITS;
      break;
    }
  }
  return retval;
}

enum read_status from_bmp(FILE *in, struct image *img) {
  enum read_status retval = READ_OK;
  /* read the header of bitmap file */
  struct header head = {0};
  if ((retval = read_header(in, &head)) != 0)
    return retval;
  /* set file pointer to data section of a bitmap file */
  if (fseek(in, head.bOffBits, SEEK_SET) != 0)
    return READ_INVALID_BITS;
  /* read the image from the data section of a bitmap file  */
  *img = image_create(dimensions_create(head.biWidth, head.biHeight));
  if ((retval = read_image(in, img)) != 0)
    image_destroy(img);
  return retval;
}

enum write_status to_bmp(FILE *out, struct image const *img) {
  enum write_status retval = WRITE_OK;
  return retval;
}
