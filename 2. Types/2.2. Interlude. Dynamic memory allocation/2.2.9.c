// эти функции вы уже реализовали на предыдущих шагах
int64_t* array_int_read( size_t* size );
int64_t* array_int_min( int64_t* array, size_t size);
void array_int_print( int64_t* array, size_t size);

void perform() {
    size_t size;
    int64_t *array = array_int_read(&size);
    int64_t *min = array_int_min(array, size);
    if (min) printf("%" PRId64, *min);
    else printf("None");
    free(array);
}
