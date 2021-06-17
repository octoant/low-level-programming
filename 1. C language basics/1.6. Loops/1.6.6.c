void f(int n) {
    printf("%d: ", n);
    for (int i = 2; i <= n; i++)
        if (n % i == 0) printf("%d ", i);
    printf("\n");
}

int main() {
    int t = 1;
    while (t <= 100) f(t++);
    return 0;
}
