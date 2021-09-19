// Вам доступна функция
struct list* node_create( int64_t value );

void list_add_front( struct list **old, int64_t value ) {
    struct list *new = node_create(value);
    if (old != NULL) {
        new->next = *old;
        *old = new;
    }
}