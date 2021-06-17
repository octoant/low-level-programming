void array_reverse(int* array, int size) {
    int tmp[size];
    for (int i = 0; i < size; i++)
        tmp[i] = array[i];
    for (int i = 0; i < size; i++)
        array[i] = tmp[size-1-i];
}

void array_reverse_ptr(int* array, int* limit) {
    int tmp[limit-array];
    int j = 0;
    for (int *i = array; i < limit; i += 1)
        tmp[j++] = *i;
    for (int *i = array; i < limit; i += 1)
        *i = tmp[--j];
}