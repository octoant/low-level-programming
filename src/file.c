#include "file.h"

enum open_status file_open(FILE **file, const char *pathname,
                           const char *mode) {
  if ((*file = fopen(pathname, mode)) != NULL) {
    return OPEN_OK;
  } else {
    return OPEN_ERROR;
  }
}

enum close_status file_close(FILE **file) {
  if (fclose(*file) != EOF) {
    return CLOSE_OK;
  } else {
    return CLOSE_ERROR;
  }
}
