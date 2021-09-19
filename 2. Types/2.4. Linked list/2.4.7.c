struct list* list_last( struct list * list ) {
    struct list *tmp = NULL;
    while (list) {
        tmp = list;
        list = list->next;
    }
    return tmp;
}