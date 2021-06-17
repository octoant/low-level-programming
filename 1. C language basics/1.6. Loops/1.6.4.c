int is_square(int n) {
    int i = 0;
    while (i * i < n) i++;
    return i * i == n;
}
