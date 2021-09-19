void list_destroy( struct list* list ) {
    if (list) {
        list_destroy(list->next);
        free(list);
    }
}