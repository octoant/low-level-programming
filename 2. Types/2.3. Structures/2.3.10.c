/* Вы можете пользоваться этими функциями из предыдущих заданий */
size_t read_size() { size_t i; scanf("%zu", &i); return i; }

void array_int_fill( int64_t* array, size_t sz );

struct array_int array_int_read();
struct maybe_int64 array_int_get( struct array_int a, size_t i );
bool array_int_set( struct array_int a, size_t i, int64_t value );
void array_int_print( struct array_int array );
struct maybe_int64 array_int_min( struct array_int array );
void array_int_free( struct array_int a );

void array_int_normalize( struct array_int array, int64_t m ) {
    for (size_t i = 0; i < array.size; i = i + 1) {
        array.data[i] = array.data[i] - m;
    }
}

/*  ---- maybe int[] ---- */

struct maybe_array_int {
    struct array_int value;
    bool valid;
};

struct maybe_array_int some_array_int(struct array_int array) {
    return (struct maybe_array_int) { array, true };
}
const struct maybe_array_int none_array_int = { {NULL, 0}, false };


/*  ---- int[][] ---- */

struct array_array_int {
    struct array_int* data;
    size_t size;
};

/*  --- строки ---  */

struct maybe_array_int array_array_int_get_row( struct array_array_int a, size_t i ) {
    if ( 0 <= i && i < a.size ) { return some_array_int( a.data[i] ); }
    else { return none_array_int; }
}

bool array_array_int_set_row( struct array_array_int a, size_t i, struct array_int value ) {
    if (0 <= i && i < a.size) {
        a.data[i] = value;
        return true;
    }
    else { return false; }
}

/*  --- get/set ---  */

struct maybe_int64 array_array_int_get( struct array_array_int a, size_t i, size_t j ) {
    const struct maybe_array_int cur_row = array_array_int_get_row(a, i);
    if (cur_row.valid) return array_int_get(cur_row.value, j);
    else return none_int64;
}

bool array_array_int_set( struct array_array_int a, size_t i, size_t j, int64_t value ) {
    const struct maybe_array_int cur_row = array_array_int_get_row(a, i);
    if (cur_row.valid && array_int_set(cur_row.value, j, value))
        return array_array_int_set_row(a, i, cur_row.value);
    else return false;
}

/*  --- read/print ---  */

void array_array_int_fill(struct array_int* array, size_t size) {
    for (size_t i = 0; i < size; i = i + 1) {
        array[i] = array_int_read();
    }
}

struct array_array_int array_array_int_read() {
    const size_t size = read_size();
    if (size > 0) {
        struct array_int* array = malloc(sizeof(struct array_int) * size);
        array_array_int_fill(array, size);
        return (struct array_array_int) { .data = array, .size = size };
    }
    else return (struct array_array_int) {0};
}

void println() { printf("\n"); }

void array_array_int_print( struct array_array_int array) {
    for (size_t i = 0; i < array.size; i = i + 1) {
        const struct maybe_array_int cur_row = array_array_int_get_row(array, i);
        if (cur_row.valid) array_int_print(cur_row.value);
        println();
    }
}


/*  --- min/normalize ---  */

// найти минимальный элемент в массиве массивов
struct maybe_int64 array_array_int_min( struct array_array_int array ) {
    struct maybe_int64 min = { 0 };
    for (size_t i = 0; i < array.size; i = i + 1) {
        const struct maybe_array_int cur_row = array_array_int_get_row( array, i );
        min = maybe_int64_min(min, array_int_min(cur_row.value));
    }
    return min;
}

// вычесть из всех элементов массива массивов число m
void array_array_int_normalize( struct array_array_int array, int64_t m) {
    for (size_t i = 0; i < array.size; i = i + 1) {
        const struct maybe_array_int cur_row = array_array_int_get_row( array, i );
        if (cur_row.valid) {
            array_int_normalize( cur_row.value, m );
        }
    }
}

void array_array_int_free( struct array_array_int array ) {
    for (size_t i = 0; i < array.size; i = i + 1) {
        const struct maybe_array_int cur_row = array_array_int_get_row( array, i );
        if (cur_row.valid) {
            array_int_free(cur_row.value);
        }
    }
    free(array.data);
    array.size = 0;
}