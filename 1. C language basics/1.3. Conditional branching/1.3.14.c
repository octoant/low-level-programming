void fizzbuzz(int a) {
    if (a <= 0) printf("no\n");
    else if (a % 3 == 0 && a % 5 == 0) printf("fizzbuzz\n");
    else if (a % 3 == 0) printf("fizz\n");
    else if (a % 5 == 0) printf("buzz\n");
}
