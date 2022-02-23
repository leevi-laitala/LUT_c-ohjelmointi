#include <stdio.h>
#include <string.h>

int cmp(float a, float b) {
    return (a < b) ? 0 : ((a > b) ? 1 : 2);
}

int main(void) {
    int a[3];
    float b[3];
    char c[3][20];
    char* res[6] = { "Luku %d on suurempi ja %d pienempi.\n", "Luvut %d ja %d ovat yhtä suuria.\n",
        "Luku %5.2f on suurempi ja %5.2f pienempi.\n", "Luvut %5.2f ja %5.2f ovat yhtä suuria.\n",
        "Merkkijonona '%s' on suurempi ja '%s' pienempi.\n", "Merkkijonona '%s' ja '%s' ovat yhtä suuria.\n"
    };

    printf("Anna kaksi kokonaislukua:\nLuku 1: ");
    scanf("%d", &a[0]);
    printf("Luku 2: ");
    scanf("%d", &a[1]);
    a[2] = a[1];

    printf(res[cmp(a[0], a[1]) == 2], a[(cmp(a[1], a[0]))], a[cmp(a[0], a[1])]);

    printf("Anna kaksi desimaalilukua:\nLuku 1: ");
    scanf("%f", &b[0]);
    printf("Luku 2: ");
    scanf("%f", &b[1]);
    b[2] = b[1];

    printf(res[(cmp(b[0], b[1]) == 2) + 2], b[cmp(b[1], b[0])], b[cmp(b[0], b[1])]);

    printf("Anna kaksi nimeä:\nNimi 1: ");
    scanf("%s", c[0]);
    printf("Nimi 2: ");
    scanf("%s", c[1]);

    printf(res[(strcmp(c[0], c[1]) == 0) + 4], c[strcmp(c[0], c[1]) < 0], c[strcmp(c[0], c[1]) > 0]);
    printf("Kiitos ohjelman käytöstä.\n");

    return 0;
}

