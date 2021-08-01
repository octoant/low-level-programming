// вы можете реализовать эти функции для более удобного считывания чисел
int64_t read_int64()
{
    int64_t number;
    scanf("%" SCNd64, &number);
    return number;
}
size_t read_size()
{
    size_t size;
    scanf("%zu", &size);
    return size;
}

// заполнить уже выделенный массив array размера size числами
void array_int_fill( int64_t* array, size_t size )
{
    for (size_t i = 0; i < size; i += 1)
        array[i] = read_int64();
}

// Считать размер массива в *size, выделить память под массив и заполнить его числами.
int64_t* array_int_read( size_t* size )
{
    *size = read_size();
    int64_t *array = malloc(*size * sizeof(int64_t));
    array_int_fill(array, *size);
    return array;
}