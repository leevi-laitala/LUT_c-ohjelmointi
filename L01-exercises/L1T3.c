#include <stdio.h>

int main(void) {
    int a, b;
    
    printf("Anna ensimmäinen kokonaisluku: ");
    scanf("%d", &a);

    printf("Anna toinen kokonaisluku: ");
    scanf("%d", &b);

    printf("(%d + %d) * %d = %d\n", a, b, 2, (a + b) * 2);
    printf("(%d / %d) - %d = %d\n", a, b, 3, (a / b) - 3);
    printf("%d %% %d = %d\n",       a, b, (++a % --b));

    return 0;
}
