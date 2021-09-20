/*
struct list {
    int64_t value;
    struct list* next;
};
*/

/* Изменить каждый элемент списка с помощью функции f  */
void list_map_mut(struct list *list, int64_t (f) (int64_t))  {
    while (list) {
        list->value = f(list->value);
        list = list->next;
    }
}


static int64_t triple( int64_t x ) { return x * 3; }

/* Используя list_map_mut умножьте все элементы списка на 3 */
void list_triple(struct list *list ) {
    list_map_mut(list, triple);
}