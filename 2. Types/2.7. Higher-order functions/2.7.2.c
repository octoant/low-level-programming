/*
struct list {
    int64_t value;
    struct list* next;
};
*/

/* Запустить функцию f на каждом элементе списка  */
void list_foreach( const struct list *list, void (f)(int64_t)) {
    while (list) {
        f(list->value);
        list = list->next;
    }
}

/* Вывести список с помощью foreach и дополнительной функции */
void list_print( const struct list *list ) {
    while (list) {
        printf("%" PRId64 " ", list->value);
        list = list->next;
    }
}