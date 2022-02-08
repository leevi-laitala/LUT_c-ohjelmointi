#include <stdio.h>
#include <stdlib.h>

#define MAXLEN 48

int menu() {
    int opt;

    printf("Valitse alla olevista valinnoista\n1) Lisää uusi nimi\n2) Tulosta nimet\n0) Lopeta\nAnna valintasi: ");
    scanf(" %d", &opt);

    return (opt > 2 || opt < 0) ? -1 : opt;
}

void read(char* fname) {
    FILE* file;
    char buf[MAXLEN];
    file = fopen(fname, "r");

    if (file == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }
        
    printf("Tiedostossa olevat nimet:\n");
    while (fgets(buf, MAXLEN, file) != NULL) {
        printf("%s", buf);
    }

    fclose(file);
    printf("Tiedosto luettu ja tulostettu.\n\n");
}

void write(char* fname) {
    FILE* file;
    char buf[MAXLEN];
    file = fopen(fname, "a");

    if (file == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }
    
    printf("Anna lisättävä nimi: ");
    scanf(" %s", buf);

    fprintf(file, "%s\n", buf);
    fclose(file);

    printf("Nimi lisätty tiedostoon.\n\n");
}

int main(void) {
    char fname[MAXLEN];

    printf("Tämä ohjelma lisää nimiä tiedostoon ja lukee ne.\nAnna käsiteltävän tiedoston nimi: ");
    scanf("%s", fname);
    
    int opt;

    for (;;) {
        opt = menu();
        
        if (opt == 0) {
            break;
        } else if (opt == 1) {
            write(fname);
        } else if (opt == 2 ) {
            read(fname);
        } else {
            printf("Tuntematon valinta.\n");
        }
    }

    printf("Kiitos ohjelman käytöstä.\n");

    return 0;
}
