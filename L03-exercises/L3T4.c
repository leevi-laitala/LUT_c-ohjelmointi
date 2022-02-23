#include <stdio.h>

#define MAXSTRLEN 100

unsigned stringlen(char* str) {
    unsigned i = 0;
    while (str[++i] != '\0') {}
    return i;
}

void stringcopy(char* from, char* o_to) {
    unsigned len = stringlen(from);
    for (unsigned i = 0; i <= len; ++i)
        o_to[i] = from[i];
}

int main(void) {
    char c[2][MAXSTRLEN] = { 0 };
    
    printf("Anna kopioitava merkkijono: ");
    fgets(c[0], MAXSTRLEN, stdin);
    c[0][stringlen(c[0]) - 1] = '\0';

    stringcopy(c[0], c[1]);

    printf("Merkkijono 1 on '%s'.\nMerkkijono 2 on '%s'.\nKiitos ohjelman käytöstä.\n", c[0], c[1]);

    return 0;
}
