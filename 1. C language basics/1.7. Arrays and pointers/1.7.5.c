void normalize(int *n) {
    if (*n > 0) while (*n % 2 == 0) *n /= 2;
}
