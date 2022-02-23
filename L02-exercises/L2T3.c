#include <stdio.h>

int main(void) {
    int a, b = 0;
    printf("Anna jokin kokonaisluku väliltä 1-10: ");
    scanf("%d", &a);

    if (a < 1 | a > 10) {
        printf("Antamasi luku ei ole välillä 1-10.\n");
        return 0;
    }

    while (a != b)
        printf("%d kierros.\n", ++b);

    return 0;
}
