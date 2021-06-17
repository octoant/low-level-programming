// position -- адрес указателя на первый элемент E в массиве,
// для которого predicate(E) выполняется.
// Функция возвращает 0 если элемент не найден.
int array_contains(int* array, int* limit, int** position) {
    for (int i = 0; i < limit - array; i++)
        if (predicate(array[i])) {
            *position = &array[i];
            return 1;
        }
    return 0;
}