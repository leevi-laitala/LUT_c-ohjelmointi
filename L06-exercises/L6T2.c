#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN_NAME 20

typedef struct
{
    char name[LEN_NAME];
    unsigned year;
} Car;

typedef struct Node Node;

struct Node
{
    Car car;
    Node* next;
};

void addnode(Node *head, char name[], unsigned year)
{
    Node *new;
    if ((new = malloc(sizeof(Node))) == NULL) { perror("Muisin varaus epäonnistui"); exit(0); }
    new->next = NULL;
    strcpy(new->car.name, name);
    new->car.year = year;

    Node *iter = head;
    while (iter->next != NULL)
        iter = iter->next;

    iter->next = new;
}

void quit(const char* str)
{
    printf("%s\nKiitos ohjelman käytöstä.\n", str);
    exit(0);
}

int main(int argc, const char* argv[])
{
    if (argc != 2) { quit("Et antanut tiedoston nimeä."); }
    printf("Luetaan tiedot tiedostosta %s.\n", argv[1]);
    FILE *file;
    if ((file = fopen(argv[1], "r")) == NULL) { quit("Tiedoston avaus epäonnistui."); }

    Node* head;
    if ((head = malloc(sizeof(Node))) == NULL) { quit("Muistin varaaminen epäonnistui."); }
    head->next = NULL;
    
    const unsigned LEN = 50;
    char line[LEN];
    
    while (fgets(line, LEN, file))
    {
        char *name = strtok(line, " ");
        char *year = strtok(NULL, " ");
        if (year && name) addnode(head, name, (unsigned)atoi(year));
    }

    printf("Tiedot luettu linkitettyyn listaan.\n");

    Node *iter = head->next;
    Node *prev = NULL;
    unsigned index = 1;
    while (iter != NULL)
    {
        printf("%d. ajoneuvo: %s vuosimalli %d.\n", index++, iter->car.name, iter->car.year);
        prev = iter;
        iter = iter->next;
        free(prev);
    }
    
    free(head);
    fclose(file);

    printf("Muisti vapautettu.\nKiitos ohjelman käytöstä.\n");
    return 0;
}
