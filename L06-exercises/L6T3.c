#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node
{
    int val;
    Node *next;
};

void addnode(Node *head, int val)
{
    Node *new;
    if ((new = malloc(sizeof(Node))) == NULL) { perror("Muisin varaus epäonnistui"); exit(0); }
    new->next = NULL;
    new->val = val;

    Node *iter = head;
    while (iter->next != NULL)
        iter = iter->next;

    iter->next = new;
}

void printlist(Node *head)
{
    if (head->next == NULL) { printf("Lista on tyhjä.\n"); return; }
    Node *iter = head->next;

    printf("Listassa on seuraavat luvut: \n");
    
    while (iter != NULL)
    {
        printf("%d ", iter->val);
        iter = iter->next;
    }

    printf("\n");
}

void clearlist(Node *head)
{
    Node *iter = head->next;
    Node *prev = NULL;

    while (iter != NULL)
    {
        prev = iter;
        iter = iter->next;
        free(prev);
    }

    head->next = NULL;
}

void createlist(Node *head, int len)
{
    if (head->next != NULL) clearlist(head);

    for (unsigned i = 0; i < len; ++i)
        addnode(head, i);
}

int main(void)
{
    Node *head;
    if ((head = malloc(sizeof(Node))) == NULL) { perror("Muistin varaus epäonnistui"); return 0; }
    head->next = NULL;
    head->val = 0;

    char opt;
    for (;;)
    {
        printf("1) Tulosta listan alkiot\n2) Muuta listan pituutta\n0) Lopeta\nAnna valintasi: ");
        scanf(" %c", &opt);

        switch (opt)
        {
        case '0':
            clearlist(head);
            free(head);
            printf("Kiitos ohjelman käytöstä.\n");
            return 0;
        case '1':
            printlist(head);
            break;
        case '2':
            printf("Anna listan uusi pituus: ");

            int len = 0;
            scanf("%d", &len);
            if (len < 0) { printf("Listan pituus ei voi olla negatiivinen.\n"); break; }

            createlist(head, len);
            break;
        default:
            printf("Tuntematon valinta, yritä uudestaan.\n");
        }
    }

    return 0;
}
