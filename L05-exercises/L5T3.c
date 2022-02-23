#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRSIZE 30

typedef struct {
    char name[ARRSIZE];
    unsigned age;
} Person;

int compare(Person* a, Person* b)
{
    int res = (strcmp(a->name, b->name)) ? 1 : 0;
    res |= (a->age != b->age);

    return res; // 0 if equal, 1 if not
}

void copy(Person* a, Person* b)
{
    for (unsigned i = 0; i < ARRSIZE; ++i)
        b->name[i] = a->name[i];

    b->age = a->age;
}

int main(void)
{
    Person a, b;

    Person* c;
    if ((c = malloc(sizeof(Person))) == NULL) { perror("Muistin varaus epäonnistui"); return 0; }

    printf("Anna ensimmäisen henkilön etunimi: ");
    scanf("%s", a.name);
    printf("Anna ensimmäisen henkilön ikä: ");
    scanf("%d", &a.age);

    printf("Anna toisen henkilön etunimi: ");
    scanf("%s", b.name);
    printf("Anna toisen henkilön ikä: ");
    scanf("%d", &b.age);

    printf("Annetut tiedot %s samoja.\n", compare(&a, &b) ? "eivät ole" : "ovat");

    copy(&a, c);

    printf("Kopioinnin jälkeen tietueiden tiedot %s samoja.\n", compare(&a, c) ? "eivät ole" : "ovat");
    printf("Kopioinnin jälkeen tietueiden osoitteet %s samoja.\n", (&a != c) ? "eivät ole" : "ovat");

    free(c);
    printf("Muisti vapautettu.\nKiitos ohjelman käytöstä.\n");

    return 0;
}
