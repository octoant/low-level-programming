void list_add_front( struct list** old, int64_t value );

// создать перевернутую копию списка
struct list* list_reverse( const struct list *list ) {
    struct list *tmp = NULL;
    while (list) {
        list_add_front(&tmp, list->value);
        list = list->next;
    }
    return tmp;
}