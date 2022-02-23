#include <stdio.h>

int main(void) {
    char c;
    char str[20];

    printf("Anna merkki: ");
    scanf("%c", &c);

    printf("Annoit merkin '%c'.\n", c);

    printf("Anna korkeintaan 20 merkkiä pitkä merkkijono: ");
    scanf("%s", str);

    printf("Annoit merkkijonon '%s'.\n", str);

    return 0;
}
