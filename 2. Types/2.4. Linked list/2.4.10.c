struct maybe_int64 list_at( const struct list *list, size_t idx ) {
    size_t i = 0;
    while (list) {
        if (idx == i) return some_int64(list->value);
        i = i + 1;
        list = list->next;
    }
    return none_int64;
}