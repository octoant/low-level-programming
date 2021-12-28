#include <stdarg.h>

#define _DEFAULT_SOURCE

#include <unistd.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>

#include "mem.h"
#include "mem_internals.h"
#include "utils.h"

void debug_block(struct block_header *block, const char *fmt, ...);
void debug(const char *fmt, ...);

extern size_t bheader_get_offset();

extern inline block_size size_from_capacity(block_capacity capacity);
extern inline block_capacity capacity_from_size(block_size size);

static bool block_is_big_enough(size_t query, struct block_header *block) {
  return block->capacity.bytes >= query;
}
static size_t pages_count(size_t mem) {
  return mem / getpagesize() + ((mem % getpagesize()) > 0);
}
static size_t round_pages(size_t mem) {
  return getpagesize() * pages_count(mem);
}

static void block_init(void *restrict addr, block_size size,
                       void *restrict next) {
  *((struct block_header *) addr) = (struct block_header) {
      .next = next,
      .capacity = capacity_from_size(size),
      .is_free = true
  };
}
static size_t region_actual_size(size_t query) {
  return size_max(round_pages(query), REGION_MIN_SIZE);
}
extern inline bool region_is_invalid(const struct region *region);

static void *map_pages(void const *addr, size_t length, int additional_flags) {
  return mmap((void*) addr, length, PROT_READ | PROT_WRITE,
              MAP_PRIVATE | MAP_ANONYMOUS | additional_flags, 0, 0);
}
/* аллоцировать регион памяти и инитиализировать его блоком */
static struct region alloc_region(void const *addr, size_t query) {
  query = region_actual_size(query);
  void *raddr = map_pages(addr, query, MAP_FIXED_NOREPLACE);
  if (raddr == MAP_FAILED) {
    raddr = map_pages(addr, query, 0);
  }
  block_init(raddr, (block_size) { query }, NULL);
  return (struct region) {
    .addr = raddr, .size = query, .extends = false
  };
}
static void *block_after(struct block_header const *block);

void *heap_init(size_t initial) {
  const struct region region = alloc_region(HEAP_START, initial);
  if (region_is_invalid(&region)) {
    return NULL;
  }
  return region.addr;
}

#define BLOCK_MIN_CAPACITY 24

/* Разделение блоков (если найденный свободный блок слишком большой) */
static bool block_splittable(struct block_header *restrict block, size_t query) {
  return block->is_free && query + bheader_get_offset() + BLOCK_MIN_CAPACITY
                               <= block->capacity.bytes;
}
static bool split_if_too_big(struct block_header *block, size_t query) {
  if (block_splittable(block, query)) {
    void *addr = (void *) ((uint8_t *) block + bheader_get_offset() + query);
    block_init(addr, (block_size){block->capacity.bytes - query}, NULL);
    block->next = addr;
    block->capacity.bytes = query;
    return true;
  } else {
    return false;
  }
}

/* Слияние соседных свободных блоков */
static void *block_after(struct block_header const *block) {
  return (void *) (block->contents + block->capacity.bytes);
}
static bool blocks_continuous(struct block_header const *fst,
                              struct block_header const *snd) {
  return (void *) snd == block_after(fst);
}
static bool mergeable(struct block_header const *restrict fst,
                      struct block_header const *restrict snd) {
  return fst->is_free && snd->is_free && blocks_continuous(fst, snd);
}
static bool try_merge_with_next(struct block_header *block) {
  struct block_header *other = block->next;
  if (other != NULL && mergeable(block, other)) {
    block->next = other->next;
    block->capacity.bytes += size_from_capacity(other->capacity).bytes;
    return true;
  } else {
    return false;
  }
}
/* ... если размер кучи хватает */
struct block_search_result {
  enum {
    BSR_FOUND_GOOD_BLOCK,
    BSR_REACHED_END_NOT_FOUND
    /* BSR_CORRUPTED */
  } type;
  struct block_header *block;
};
static struct block_search_result find_good_or_last(
    struct block_header *restrict block, size_t size)
{
  struct block_header *last;
  while (block != NULL) {
    while (try_merge_with_next(block));
    if (block->is_free && block_is_big_enough(size, block))
      return (struct block_search_result) {
          BSR_FOUND_GOOD_BLOCK, block
      };
    last = block;
    block = block->next;
  }
  return (struct block_search_result) {
      BSR_REACHED_END_NOT_FOUND, last
  };
}

/* Попробовать выделить память в кучи начиная с блока `блока` не пытаясь
 * расшерить кучу. Можно переиспользовать как только кучу расширили. */
static struct block_search_result try_memalloc_existing(
    size_t query, struct block_header *block)
{
  struct block_search_result result = find_good_or_last(block, query);
  if (result.type == BSR_FOUND_GOOD_BLOCK) {
    split_if_too_big(result.block, query);
  }
  return result;
}
static struct block_header *grow_heap(
    struct block_header *restrict last, size_t query) {
  last->next = alloc_region(block_after(last), query).addr;
  return last;
}

/* Реализует основную логику malloc и возвращает заголовок выделенного блока */
static struct block_header *memalloc(
    size_t query, struct block_header *heap_start)
{
  struct block_search_result result
      = try_memalloc_existing(query, heap_start);
  if (result.type != BSR_FOUND_GOOD_BLOCK) {
    result = try_memalloc_existing(query, grow_heap(result.block, query));
  }
  return result.block;
}
void *_malloc(size_t query) {
  struct block_header *const addr = memalloc(query,
      (struct block_header *) HEAP_START);
  if (addr) {
    addr->is_free = false;
    return addr->contents;
  }
  else return NULL;
}

static struct block_header *block_get_header(void *contents) {
  return (struct block_header *) (((uint8_t *) contents) - bheader_get_offset());
}
void _free(void *mem) {
  if (!mem) return;
  struct block_header *header = block_get_header(mem);
  header->is_free = true;
  while (try_merge_with_next(header));
}