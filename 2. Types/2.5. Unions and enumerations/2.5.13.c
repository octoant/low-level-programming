struct heap_string {
    char* addr;
};

size_t string_size( const char *s ) {
    size_t i = 0;
    while (s[i] != '\0') i = i + 1;
    return i + 1;
}

// скопировать в кучу
struct heap_string halloc( const char* s ) {
    char* str = malloc(sizeof(s));
    for (size_t i = 0; i < string_size(s); i = i + 1) {
        str[i] = s[i];
    }
    return (struct heap_string) { str };
}

// освободить память
void heap_string_free( struct heap_string h ) {
    free(h.addr);
}