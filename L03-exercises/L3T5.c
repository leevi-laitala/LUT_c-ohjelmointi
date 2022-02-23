#include <stdio.h>
#include <stdlib.h>

#define NUMS 20

void read(char* fname) {
    FILE* file;

    int num;

    if ((file = fopen(fname, "rb")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }

    printf("Tiedostossa on seuraavat luvut:\n");

    for (unsigned i = 0; i < NUMS; ++i) {
        fread(&num, sizeof(int), 1, file);
        printf("%d ", num);
    }
    
    printf("\nTiedoston lukeminen onnistui.\n");

    fclose(file);
}

void write(char* fname, int* seed) {
    FILE* file;

    if ((file = fopen(fname, "wb")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }
    
    srand(*seed);
    
    for (unsigned i = 0; i < NUMS; ++i) {
        int num = rand() % 1000;
        fwrite(&num, sizeof(int), 1, file);
    }
    
    printf("Tiedoston kirjoitus onnistui.\n");
    fclose(file);
}

int main(void) {
    int rands[NUMS];
    char fname[20];
    int seed;


    printf("Anna käsiteltävän tiedoston nimi: ");
    scanf("%s", fname);

    printf("Anna satunnaisluvuille lähtöarvo: ");
    scanf("%d", &seed);

    write(fname, &seed);
    read(fname);
    
    printf("Kiitos ohjelman käytöstä.\n");

    return 0;
}
