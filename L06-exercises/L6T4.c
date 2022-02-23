#include <stdlib.h>
#include <stdio.h>

typedef struct Node Node;

struct Node
{
    int val;
    Node* next;
};

void printlist(Node* head)
{
    Node* iter = head->next;

    if (iter == NULL)
    {
        printf("\n");
        return;
    }

    while (iter != NULL)
    {
        printf("%d ", iter->val);
        iter = iter->next;
    }
    printf("\n");
}

void addnode(Node *head, int val)
{
    Node *new;
    if ((new = malloc(sizeof(Node))) == NULL)
    {
        perror("Muistin varaaminen epäonnistui.\n");
        exit(0);
    }
    new->next = NULL;
    
    Node *iter = head;
    for (;;)
    {
        if (iter->next == NULL) // Find tail
        {
            iter->next = new;
            new->val = val;
            break;
        }
        iter = iter->next;
    }
}

void createlist(Node *head, int len)
{
    int initialheadval = head->val;
    for (unsigned i = 0; i < len; ++i)
    {
        addnode(head, initialheadval + i);
        head->val++;
    }

    printlist(head);
}

void pushback(Node *head)
{
    Node *iter = head;
    for (;;)
    {
        if (iter->next == NULL)
        {
            addnode(head, head->val++);
            break;
        }

        iter = iter->next;
    }
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

int main(void)
{
    Node *head;
    if ((head = malloc(sizeof(Node))) == NULL)
    {
        perror("Muistin varaaminen epäonnistui.\n");
        return 0;
    }

    head->val = 1;
    head->next = NULL;

    printf("Tämä ohjelma hallitsee listaa ja sen alkioita.\n");

    for (;;)
    {
        int opt;
        printf("1) Luo lista\n2) Lisää alkio listan loppuun\n3) Lisää alkio listan keskelle\n4) Tyhjennä lista\n5) Poista alkio listasta\n6) Tulosta lista\n0) Lopeta\nAnna valintasi: ");
        scanf("%d", &opt);

        switch(opt)
        {
            case 0:
                clearlist(head);
                free(head);
                printf("Kiitos ohjelman käytöstä.\n");
                return 0;
            case 1:
                printf("Anna listan pituus: ");
                int len;
                scanf(" %d", &len);
                createlist(head, len);
                break;
            case 2:
                pushback(head);
                printlist(head);
                break;
            case 4:
                clearlist(head);
                break;
            case 6:
                printlist(head);
                break;
            default:
                printf("Tuntematon valinta, yritä uudestaan.\n");
        }
    }

    return 0;
}
