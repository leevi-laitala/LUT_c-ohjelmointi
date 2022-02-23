#include <stdio.h>

#define LEN 50

typedef struct {
    char name[LEN];
    unsigned year;
    unsigned shelf;
} Book;

int main(void) {
    Book book;
    
    printf("Anna kirjan nimi: ");
    fgets(book.name, LEN, stdin);

    unsigned len = 0;
    while (book.name[++len] != '\0') {}
    book.name[len - 1] = '\0';

    printf("Anna kirjan painovuosi: ");
    scanf("%d", &book.year);

    printf("Anna kirjan hyllypaikka: ");
    scanf("%d", &book.shelf);

    printf("Kirjan nimi on '%s', painovuosi %d ja hyllypaikka %d.\nKiitos ohjelman käytöstä.\n", book.name, book.year, book.shelf);

    return 0;
}
