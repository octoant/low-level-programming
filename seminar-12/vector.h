#ifndef VECTOR_H
#define VECTOR_H

#include "maybe_int.h"
#include <stddef.h>

struct vector_int;

struct vector_int *vector_int_create();
void vector_int_destroy(struct vector_int *);

struct maybe_int vector_int_get(struct vector_int const *, size_t);
bool vector_int_set(struct vector_int *, size_t, int64_t);
void vector_int_push_back(struct vector_int *, int64_t);

size_t vector_int_count(struct vector_int const *);
size_t vector_int_size(struct vector_int const *);

void vector_int_for_each(const struct vector_int *, void (*f)(int64_t));

#endif
