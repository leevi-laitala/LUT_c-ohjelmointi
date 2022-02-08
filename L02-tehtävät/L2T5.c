#include <stdio.h>

#define LEN 200

int main(void) {
    char str[LEN];
    char* curLen = str;
    char input;

    for (;;) {
        printf("\nValikko\n1) Lisää uusi merkki\n2) Tyhjennä merkkijono\n3) Tulosta merkkijono\n0) Lopeta\nValintasi: ");
        char cmd;
        scanf(" %s", &cmd);

        switch (cmd) {
            case '1': // Add character
                if (curLen == str + LEN) {
                    printf("\nMerkkijonoon ei mahdu enempää merkkejä.\n\n");
                    break;
                }

                printf("\nAnna jokin merkki: ");
                scanf(" %s", &input);
                
                *curLen = input;
                curLen++;
                break;
            case '2': // Clear characters
                for (unsigned i = 0; i < LEN; i++)
                    str[i] = 0;
                curLen = str;

                printf("\nMerkkijono on tyhjennetty.\n");
                break;
            case '3': // Print characters
                if (curLen == str)
                    printf("\nMerkkijono on tyhjä.\n");
                else
                    printf("\nMerkkijono: %s\n", str);
                break;
            case '0': // Quit
                printf("\nOhjelman lopetus.\n");
                return 0;
            default: // None of above
                printf("\nTuntematon valinta.\n");
        }
    }

    return 0;
}
