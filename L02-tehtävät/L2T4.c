#include <stdio.h>

#define PI 3.141

int main(void) {
    float a, res;
    int cmd;

    printf("Anna liukuluku: ");
    scanf("%f", &a);

    printf("\nValikko\n1) Kerro piin arvo luvulla %.3f.\n2) Jaa piin arvo luvulla %.3f.\nValitse: ", a, a);
    scanf("%d", &cmd);

    switch (cmd) {
        case 1:
            printf("\nPii * %.3f = %.3f.\n", a, PI * a);
            break;
        case 2:
            printf("\nPii / %.3f = %.3f.\n", a, PI / a);
            break;
        default:
            printf("\nTuntematon valinta.\n");
    }

    return 0;
}
