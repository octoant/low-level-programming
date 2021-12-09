#include "file.h"

enum open_status file_open(FILE **file, const char *path, const char *mode) {
  return OPEN_OK;
}

enum close_status file_close(FILE **file) {
  return CLOSE_OK;
}
