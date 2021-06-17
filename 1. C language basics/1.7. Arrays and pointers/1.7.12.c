void array_fib(int* array, int* limit) {
    int* cur = array;
    if (cur < limit) { *cur = 1; cur = cur + 1; }
    if (cur < limit) { *cur = 1; cur = cur + 1; }
    for( ; cur < limit; cur = cur + 1 )
        *cur = cur[-2] + cur[-1];
}