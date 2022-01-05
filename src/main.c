#include <stdio.h>

#include "bmp.h"
#include "file.h"
#include "image.h"
#include "transform.h"
#include "utils.h"

#define EXECUTABLE "image-transformer"

static const char *r_msg[] = {
    [READ_INVALID_SIGNATURE] ="Invalid bitmap signature",
    [READ_INVALID_BITS] = "Invalid number of bits",
    [READ_INVALID_HEADER] = "Invalid bitmap header"
};
static const char *w_msg[] = {
    [WRITE_ERROR] = "Error while writing"
};

void usage() {
  fprintf(stderr,
          "Usage: ./" EXECUTABLE " <source-image> <transformed-image>\n");
}

int main(int argc, char *argv[]) {
  if (argc != 3) usage();
  if (argc < 3) err("Not enough arguments\n");
  if (argc > 3) err("Too many arguments\n");

  FILE *in, *out;
  if (file_open(&in, argv[1], "rb") != 0) {
    err("Could not open the file for reading\n");
  }
  if (file_open(&out, argv[2], "wb") != 0) {
    file_close(&in);
    err("Could not create a file for writing\n");
  }

  struct image source = {0};

  enum read_status rstat = from_bmp(in, &source);
  file_close(&in);
  if (rstat != READ_OK) {
    fprintf(stderr, "%s\n", r_msg[rstat]);
    return rstat;
  }

  struct image transformed = rotate_left(source);

  enum write_status wstat = to_bmp(out, &transformed);
  file_close(&out);
  if (wstat != WRITE_OK) {
    image_destroy(&source);
    image_destroy(&transformed);
    fprintf(stderr, "%s\n", w_msg[wstat]);
    return wstat;
  }

  image_destroy(&source);
  image_destroy(&transformed);

  return 0;
}
