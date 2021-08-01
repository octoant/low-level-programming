// Возвращает 1 если в числе одна цифра, иначе 0
int is_single_digit(int n) {
    return 0 <= n && n <= 9;
}

// Возвращает 1 если в числе ровно две цифры, иначе 0
int is_double_digit(int n) {
    return 10 <= n && n <= 99;
}
