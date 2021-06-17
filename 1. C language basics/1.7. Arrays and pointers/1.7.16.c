int is_whitespace(char c) { return c == ' ' || c == '\t' || c == '\n'; }

int string_count(char* str) {
    int i = 0, res = 0;
    while (str[i++] != 0) res++;
    return res;
}

int string_words(char* str)  {
    int i = 0, res = 0, len = 0;
    while (str[i] != 0) {
        if (is_whitespace(str[i])) {
            if (len > 0) res++, len = 0;
        } else len++;
        i++;
    }
    if (len > 0) res++;
    return res;
}