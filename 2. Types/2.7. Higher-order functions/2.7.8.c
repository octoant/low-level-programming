/*
struct list {
    int64_t value;
    struct list* next;
};
*/
void print_int64(int64_t i);

struct list* node_create( int64_t value );
void list_destroy( struct list* list );


/*  Сгенерировать список длины sz с помощью значения init и функции f
 Результат: init, f(init), f(f(init)), ... */
struct list* list_iterate( int64_t init, size_t sz, int64_t(f)(int64_t)) {
    struct list *head = NULL, *tail;
    int64_t tmp = init;
    for (size_t i = 0; i < sz; i = i + 1) {
        if (i == 0) {
            head = tail = node_create(tmp);
        } else {
            tail->next = node_create(tmp = f(tmp));
            tail = tail->next;
        }
    }
    return head;
}