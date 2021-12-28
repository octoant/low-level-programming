#include <stdio.h>
#include <stdarg.h>

#include "mem.h"
#include "mem_internals.h"

void debug_struct_info(FILE *file, void const *addr) {
  struct block_header const *header = addr;
  fprintf(file, "%10p %10zu %8s   ", addr,
          header->capacity.bytes,
          header->is_free ? "free" : "taken");
  for (size_t i = 0; i < DEBUG_FIRST_BYTES &&
                     i < header->capacity.bytes; i++) {
    fprintf(file, "%hhX", header->contents[i]);
  }
  fprintf(file, "\n");
}

void debug_heap(FILE *file, void const *ptr) {
  fprintf(file, " --- Heap --- \n");
  fprintf(file, "%10s %10s %8s 10%s\n",
          "start", "capacity", "status", "contents");
  for (struct block_header const *header = ptr; header;
       header = header->next) {
    debug_struct_info(file, header);
  }
}

void debug_block(struct block_header *block,
                 const char *fmt, ...) {
#ifdef DEBUG
  va_list args;
  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  memalloc_debug_struct_info(stderr, block);
  va_end(args);
#else
  (void) block;
  (void) fmt;
#endif
}

void debug(const char *fmt, ...) {
#ifdef DEBUG
  va_list args;
  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  va_end(args);
#else
  (void) fmt;
#endif
}