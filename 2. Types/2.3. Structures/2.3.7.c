// упакованное число 42 выводится как "Some 42"
// Ошибка выводится как None
void maybe_int64_print( struct maybe_int64 i ) {
    if (i.valid) printf("Some %" PRId64 "", i.value);
    else printf("None");
}

int64_t int_min( int64_t a, int64_t b ) {
    return a < b ? a : b;
}

// Если обе упаковки содержат ошибку, то результат ошибка
// Если ровно одна упаковка содержит ошибку, то результат -- вторая
// Если обе упаковки содержат число, то результат это минимум из двух чисел.
struct maybe_int64 maybe_int64_min(struct maybe_int64 a, struct maybe_int64 b) {
    if (! a.valid) { return b; }
    if (! b.valid) { return a; }
    return some_int64( int_min( a.value, b.value ) );
}