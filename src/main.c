#include <sys/resource.h>
#include <stdio.h>
#include <inttypes.h>

#include "bmp.h"
#include "file.h"
#include "image.h"
#include "sepia.h"
#include "utils.h"

#define OUT stderr

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
  fprintf(OUT, "Usage: ./" EXECUTABLE " <source-image>\n");
}

static void test_avg_time(struct image, int, FILE *);

int main(int argc, char *argv[]) {
  if (argc != 2) usage();
  if (argc < 2) err("Not enough arguments\n");
  if (argc > 2) err("Too many arguments\n");

  FILE *in, *out_c, *out_asm;
  if (file_open(&in, argv[1], "rb") != 0 ||
      file_open(&out_c, "sepia_out_c.bmp", "wb") != 0 ||
      file_open(&out_asm, "sepia_out_asm.bmp", "wb") != 0) {
    err("Could not open the file for reading\n");
  }
  struct image source = {0};

  enum read_status rstat = from_bmp(in, &source);
  file_close(&in);
  if (rstat != READ_OK) {
    fprintf(OUT, "%s\n", r_msg[rstat]);
    return rstat;
  }

  struct image img_c = sepia_c_inplace(source);
  struct image img_asm = sepia_sse(source);

  enum write_status wstat_c = to_bmp(out_c, &img_c);
  file_close(&out_c);
  if (wstat_c != WRITE_OK) {
    image_destroy(&img_c);
    fprintf(OUT, "%s\n", w_msg[wstat_c]);
  }
  enum write_status wstat_asm = to_bmp(out_asm, &img_asm);
  file_close(&out_asm);
  if (wstat_asm != WRITE_OK) {
    image_destroy(&img_asm);
    fprintf(OUT, "%s\n", w_msg[wstat_asm]);
  }

  fprintf(OUT, "Image size: %" PRId32 "x%" PRId32 "\n", source.dims.width, source.dims.height);

  test_avg_time(source, 64, OUT);

  image_destroy(&source);
  image_destroy(&img_c);
  image_destroy(&img_asm);

  return 0;
}

static void test_avg_time(struct image img, int n, FILE *file) {
  struct rusage r;
  struct timeval start, middle, end;
  long total_c = 0, total_asm = 0;
  for (int i = 0; i < n; i++) {
    getrusage(RUSAGE_SELF, &r);
    start = r.ru_utime;
    struct image img_c = sepia_c_inplace(img);
    getrusage(RUSAGE_SELF, &r);
    middle = r.ru_utime;
    struct image img_asm = sepia_sse(img);
    getrusage(RUSAGE_SELF, &r);
    end = r.ru_utime;
    total_c += ((middle.tv_sec - start.tv_sec) * 1000000L) + middle.tv_usec - start.tv_usec;
    total_asm += ((end.tv_sec - middle.tv_sec) * 1000000L) + end.tv_usec - middle.tv_usec;
    image_destroy(&img_c);
    image_destroy(&img_asm);
  }
  fprintf(file, "Avg time elapsed in microseconds for c: %ld\n", total_c / n);
  fprintf(file, "Avg time elapsed in microseconds for asm: %ld\n", total_asm / n);
}
