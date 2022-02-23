#include <stdio.h>

int power(int* base, int* exponent) {
    if (*base == 0 && *exponent == 0) return -1;

    int result = *base;

    for (unsigned i = 0; i < *exponent - 1; i++)
        result *= *base;

    return result;
}

int main(void) {
    int a, b;

    printf("Ohjelma laskee luvun potenssin.\nAnna kokonaisluku, jonka haluat korottaa potenssiin: ");
    scanf("%d", &a);

    printf("Anna potenssi, jonka haluat laskea: ");
    scanf("%d", &b);

    printf("%d ^ %d = %d.\n", a, b, power(&a, &b));
    printf("Kiitos ohjelman käytöstä.\n");

    return 0;
}
