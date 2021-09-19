size_t list_length( const struct list* list ) {
    size_t size = 0;
    while (list) {
        size = size + 1;
        list = list->next;
    }
    return size;
}