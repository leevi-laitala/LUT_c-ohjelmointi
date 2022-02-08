#include <stdio.h>

int main(void) {
    int a, b, cmd;
    printf("Anna kaksi kokonaislukua: ");
    scanf("%d%d", &a, &b);

    printf("\nValikko\n1) Summaa luvut yhteen.\n2) Kerro luvut keskenään.\nValitse: ");
    scanf("%d", &cmd);

    if (cmd == 1)
        a = a + b;
    else if (cmd == 2)
        a = a * b;
    else {
        printf("\nTuntematon valinta.\n");
        return 0;
    }
    
    printf("\nLuvut %s. Tulos = %d.\n", (cmd == 1) ? "laskettiin yhteen" : "kerrottiin keskenään", a);

    return 0;
}
