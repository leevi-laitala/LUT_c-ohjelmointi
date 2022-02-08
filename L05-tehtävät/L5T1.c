#include <stdio.h>
#include <stdlib.h>

void sqr(int* num)
{
    *num *= *num;
}

int main(int argc, const char* argv[])
{
    int num;

    if (argc < 2) { printf("Et antanut lukua!\nKiitos ohjelman käytöstä.\n"); return 0; }
    if ((num = atoi(argv[1])) == 0 && *argv[1] != '0') { printf("Et antanut lukua!\nKiitos ohjelman käytöstä.\n"); return 0; }

    printf("Luku on %d.\n", num);
    sqr(&num);
    printf("Luvun neliö on %d.\nKiitos ohjelman käytöstä.\n", num);

    return 0;
}
