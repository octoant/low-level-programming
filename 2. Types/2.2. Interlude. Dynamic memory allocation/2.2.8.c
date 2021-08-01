int64_t* array_int_min( int64_t* array, size_t size ) {
    if ( array == NULL || size < 1 ) return NULL;
    int64_t* min = array;
    for (int64_t* ptr = array; ptr != array+size; ++ptr) {
        if ( *ptr < *min ) min = ptr;
    }
    return min;
}
