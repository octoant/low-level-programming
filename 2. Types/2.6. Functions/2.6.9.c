// Мы хотим, чтобы в структуре user хранились ссылки только на строчки из кучи.
typedef struct { char* addr; } string_heap ;

/*  Тип для идентификаторов пользователей
    и его спецификаторы ввода и вывода для printf */
typedef uint64_t uid;
#define PRI_uid PRIu64
#define SCN_uid SCNu64

enum city {C_SARATOV, C_MOSCOW, C_PARIS, C_LOS_ANGELES, C_OTHER};

/*  Массив, где элементам перечисления сопоставляются их текстовые представления */
const char* city_string[] = {
        [C_SARATOV] = "Saratov",
        [C_MOSCOW] = "Moscow",
        [C_PARIS] = "Paris",
        [C_LOS_ANGELES] = "Los Angeles",
        [C_OTHER] = "Other"
};


struct user {
    const uid id;
    const string_heap name;
    enum city city;
};

/* Сортировать массив пользователей по полю uid по возрастанию */

int cmp_by_uid(const struct user *a, const struct user *b) {
    if (a->id < b->id) return -1;
    if (a->id > b->id) return  1;
    return  0;
}

int cmp_void_by_uid(const void *a, const void *b) {
    return cmp_by_uid(a, b);
}

void users_sort_uid(struct user users[], size_t sz) {
    if (users) qsort(users, sz, sizeof(struct user), cmp_void_by_uid);
}

/* Сортировать массив пользователей по полю name */
/* Порядок строк лексикографический; можно использовать компаратор 
   строк -- стандартную функцию strcmp */

int cmp_by_name(const struct user *a, const struct user *b) {
    return strcmp(a->name.addr, b->name.addr);
}

int cmp_void_by_name(const void *a, const void *b) {
    return cmp_by_name(a, b);
}

void users_sort_name(struct user users[], size_t sz) {
    if (users) qsort(users, sz, sizeof(struct user), cmp_void_by_name);
}

/* Сортировать массив по _текстовому представлению_ города */

int cmp_by_city(const struct user *a, const struct user *b) {
    return strcmp(city_string[a->city], city_string[b->city]);
}

int cmp_void_by_city(const void *a, const void *b) {
    return cmp_by_city(a, b);
}

void users_sort_city(struct user users[], size_t sz) {
    if (users) qsort(users, sz, sizeof(struct user), cmp_void_by_city);
}