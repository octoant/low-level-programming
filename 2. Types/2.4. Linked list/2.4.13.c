struct list* list_read() {
    struct list* list = NULL;
    struct maybe_int64 t = maybe_read_int64();
    if (t.valid) {
        list = node_create(t.value);
        list->next = list_read();
    }
    return list;
}