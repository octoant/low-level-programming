int discriminant(int a, int b, int c) {
    return b * b - 4 * a * c;
}

int root_count(int a, int b, int c) {
    int D = discriminant(a, b, c);
    return D < 0 ? 0 : D > 0 ? 2 : 1;
}

int main() {
    // Считайте три числа в локальные переменные
    int a = read_int();
    int b = read_int();
    int c = read_int();
    // выведите результат запуска root_count с аргументами a, b и c.
    printf("%d", root_count(a, b, c));
    return 0;
}