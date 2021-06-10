size_t count_zeroes(const void *data, size_t sz )
{
    const int8_t *ptr = data;
    size_t zeroes = 0;
    for (size_t i = 0; i < sz; i = i + 1) {
        if (*ptr == 0) zeroes += 1;
        ptr += 1;
    }
    return zeroes;
}
