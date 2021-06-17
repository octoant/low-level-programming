void factorize( int n, int* a, int* b )
{
    *a = 1;
    *b = n;
    for (int i = 2; i <= n / 2; i++)
        if (n % i == 0) {
            *a = i;
            *b = n / i;
            break;
        }
}
