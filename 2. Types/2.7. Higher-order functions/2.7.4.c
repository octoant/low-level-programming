/*
struct list {
    int64_t value;
    struct list* next;
};
*/
/* Вы можете пользоваться следующими функциями */
void print_int64(int64_t i);
struct list* node_create( int64_t value );
void list_destroy( struct list* list );

int64_t int64_nope(int64_t n) { return n; }
int64_t int64_abs(int64_t n) { if (n >= 0) return n; else return (-n); }

/*  Создать новый список, в котором каждый элемент получен из соответствующего
    элемента списка l путём применения функции f */
struct list* list_map( const struct list *list, int64_t (f) (int64_t))  {
    struct list *head = NULL, *tail;
    while (list) {
        if (!head) {
            head = tail = node_create(f(list->value));
        } else {
            tail->next = node_create(f(list->value));
            tail = tail->next;
        }
        list = list->next;
    }
    return head;
}

struct list* list_copy( const struct list *list ) {
    return list_map(list, int64_nope);
}

struct list* list_abs( const struct list *list ) {
    return list_map(list, int64_abs);
}