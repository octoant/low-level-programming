#include "mem.h"
#include "mem_internals.h"

int main(int argc, char *argv[]) {

  heap_init(REGION_MIN_SIZE);

  FILE *file = fopen("output.txt", "wb");
  if (file != NULL) {
    debug_heap(file, HEAP_START);

    int64_t *int64 = _malloc(8);
    *int64 = -1;                                // FFFFFFFF
    debug_heap(file, HEAP_START);

    int64_t *int32 = _malloc(4);
    *int32 = 0x12345;                           // 0x54321 (little endian)
    debug_heap(file, HEAP_START);

    char *str = _malloc(100);
    str = "Hello World!\0";                     // ... '!', 'd', 'l' ... 'H' (little endian)
    debug_heap(file, HEAP_START);

    _free(int32);
    debug_heap(file, HEAP_START);

    _free(int64);
    debug_heap(file, HEAP_START);
  }
  fclose(file);

  return 0;
}
