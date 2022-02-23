#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node
{
    int value;
    Node* next;
};

int main(void)
{
    Node* head = NULL;
    Node* iter;

    printf("Anna listan luvut.\n");

    for (;;)
    {
        int num;
        printf("Anna positiivinen kokonaisluku, 0 lopettaa: ");
        scanf("%d", &num);
        if (!num) break;

        Node* new = malloc(sizeof(Node));

        new->value = num;
        new->next = NULL;

        if (!head) { head = new; continue; }

        iter = head;
        for (;;)
        {
            if (iter->next == NULL) // Find tail
            {
                iter->next = new;
                break;
            }

            iter = iter->next;
        }
    }

    iter = head;
    Node* prev = NULL;
    printf("Listassa on seuraavat luvut: ");
    while (iter != NULL)
    {
        prev = iter;
        printf("%d ", iter->value);
        iter = iter->next;

        free(prev);
    }

    printf("\nKiitos ohjelman käytöstä.\n");

    return 0;
}
