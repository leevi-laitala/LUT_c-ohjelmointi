#include <stdio.h>
#include <stdlib.h>

#define LEN 50

typedef struct {
    char user[LEN];
    char secret[LEN];
    unsigned id;
} User;

int menu() {
    int opt;

    printf("Valitse haluamasi toiminto:\n1) Lisää uusi tunnus\n2) Tulosta tunnukset\n0) Lopeta\nValintasi: ");
    scanf("%d", &opt);
    printf("\n");

    return (opt < 0 || opt > 2) ? -1 : opt;
}

int main(void) {
    printf("Käyttäjätunnusten hallinta.\n");
    User users[LEN];
    unsigned cur = 0;

    for (;;) {
        int opt = menu();

        switch (opt) {
            case 0:
                printf("Kiitos ohjelman käytöstä.\n");
                exit(0);
            case 1:
                printf("Anna käyttäjätunnus: ");
                scanf("%s", users[cur].user);

                printf("Anna salasana: ");
                scanf("%s", users[cur].secret);
                users[cur].id = cur;
                
                printf("Tunnus '%s' lisättiin listaan.\n\n", users[cur].user);
                cur++;
                break;
            case 2:
                printf("Listalla olevat tunnukset:\n");
                for (unsigned i = 0; i < cur; ++i)
                    printf("%d. tunnus '%s', salasana '%s', ID '%d'.\n", i + 1, users[i].user, users[i].secret, users[i].id);
                printf("\n");
                break;
            default:
                printf("Tuntematon valinta.\n");
        }
    }

    return 0; 
}
