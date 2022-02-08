#include <stdio.h>

unsigned long fib(unsigned long n) {
    return (n == 1 || n == 0) ? n : fib(n - 1) + fib(n - 2);
}

int main(void) {
    unsigned long n;
    printf("Anna luku, jolle lasketaan Fibonaccin luku: ");
    scanf("%lu", &n);
    printf("Luvun %lu Fibonaccin luku on %lu.\nKiitos ohjelman käytöstä.\n", n, fib(n));

    return 0;
}
