struct list {
    int64_t value;
    struct list* next;
};

struct list* node_create( int64_t value ) {
    struct list *tmp = malloc(sizeof(struct list));
    tmp->value = value;
    tmp->next = NULL;
    return tmp;
}