enum move_dir { MD_UP, MD_RIGHT, MD_DOWN, MD_LEFT, MD_NONE };

// Робот и его callback'и
// callback'ов может быть неограниченное количество
struct robot {
    const char* name;
    struct list *callbacks;
};

// Определите тип обработчика событий move_callback с помощью typedef
typedef void (move_callback)(enum move_dir);

// Реализация связанной списки
struct list {
    move_callback *callback;
    struct list *next;
};

struct list* node(move_callback new_cb) {
    struct list *tmp = malloc(sizeof(struct list));
    tmp->callback = new_cb;
    tmp->next = NULL;
    return tmp;
}

void list_add( struct list **old, move_callback new_cb ) {
    struct list *new = node(new_cb);
    if (old != NULL) {
        new->next = *old;
        *old = new;
    }
}

void list_destroy( struct list* list ) {
    if (list) {
        list_destroy(list->next);
        free(list);
    }
}

// Добавить callback к роботу, чтобы он вызывался при движении
// В callback будет передаваться направление движения
void register_callback(struct robot* robot, move_callback new_cb) {
    list_add(&(robot->callbacks), new_cb);
}

// Отменить все подписки на события.
// Это нужно чтобы освободить зарезервированные ресурсы
// например, выделенную в куче память
void unregister_all_callbacks(struct robot* robot) {
    list_destroy(robot->callbacks);
}

// Вызывается когда робот движется
// Эта функция должна вызвать все обработчики событий
void move(struct robot* robot, enum move_dir dir) {
    struct list *list = robot->callbacks;
    while (list) {
        list->callback(dir);
        list = list->next;
    }
}