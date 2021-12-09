#ifndef FILE_H
#define FILE_H

#include <stdio.h>

enum open_status { OPEN_OK = 0, OPEN_ERROR };
enum open_status file_open(FILE **, const char *, const char *);

enum close_status { CLOSE_OK = 0, CLOSE_ERROR };
enum close_status file_close(FILE **);

#endif
