#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char* argv[]) {
    float a, b, c;
    char o;

    if (argc == 1) { printf("Et antanut syötteitä.\nKiitos ohjelman käytöstä.\n"); exit(0); }
    if (argc != 4) { printf("Virheellinen syöte.\nKiitos ohjelman käytöstä.\n"); exit(0); }

    a = atof(argv[1]);
    b = atof(argv[3]);
    o = *argv[2];

    if (o == '+')
        c = a + b;
    else if (o == '-')
        c = a - b;
    else if (o == 'x')
        c = a * b;
    else if (o == '/')
        c = a / b;
    else { printf("Virheellinen syöte.\nKiitos ohjelman käytöstä.\n"); exit(0); }

    printf("%s %c %s = %.2f\nKiitos ohjelman käytöstä.\n", argv[1], o, argv[3], c);

    return 0;
}
