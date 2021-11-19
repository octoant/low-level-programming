#include "vector.h"
#include <malloc.h>

struct vector_int {
  int64_t *data;
  size_t count;
  size_t capacity;
};

static const size_t MIN_CAPACITY = 16;

static struct vector_int vector_int_init(size_t capacity) {
  return (struct vector_int) {
    .capacity = capacity,
    .count = 0,
    .data = malloc(sizeof(int64_t) * capacity)
  };
}

struct vector_int *vector_int_create() {
  struct vector_int *result = malloc(sizeof(struct vector_int));
  *result = vector_int_init(MIN_CAPACITY);
  return result;
}

void vector_int_destroy(struct vector_int *v) {
  if (v) free(v->data);
  free(v);
}

static bool index_valid(struct vector_int const *v, size_t i) {
  return i < v->count;
}

struct maybe_int vector_int_get(struct vector_int const *v, size_t idx) {
  if (!v || !index_valid(v, idx))
    return none_int;
  return some_int(v->data[idx]);
}

bool vector_int_set(struct vector_int *v, size_t idx, int64_t value) {
  if (!v || !index_valid(v, idx))
    return false;
    v->data[idx] = value;
  return true;
}

static bool vector_int_full(struct vector_int const *v) {
  return v->capacity == v->count;
}

static size_t grow_capacity(size_t capacity) {
  return capacity + capacity / 2;
}

static void vector_int_grow(struct vector_int *v) {
  v->capacity = grow_capacity(v->capacity);
  v->data = realloc(v->data, v->capacity * sizeof(int64_t));
}

void vector_int_push_back(struct vector_int *v, int64_t value) {
  if (vector_int_full(v))
    vector_int_grow(v);
  v->data[v->count] = value;
  v->count++;
}

size_t vector_int_count(struct vector_int const *v) {
  return v->count;
}

size_t vector_int_size(struct vector_int const *v) {
  return v->count * sizeof(int64_t);
}

void vector_int_for_each(const struct vector_int *v, void (*callback)(int64_t)) {
  for (size_t i = 0; i < vector_int_count(v); i++) {
    callback(v->data[i]);
  }
}
