#include <stdio.h>


int main(void) {
    int a;
    float b;

    printf("Anna kokonaisluku: ");
    scanf("%d", &a);
    printf("Anna liukuluku: ");
    scanf("%f", &b);

    printf("Annoit luvut %d ja %0.2f.\n", a, b);

    return 0;
}
