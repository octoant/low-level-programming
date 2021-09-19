void list_add_back( struct list** old, int64_t value ) {
    struct list *new = node_create(value);
    struct list *last = list_last(*old);
    if (last) last->next = new;
    else *old = new;
}