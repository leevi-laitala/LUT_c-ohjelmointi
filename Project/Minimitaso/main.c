#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FNAMEMAX 32 // Filename
#define DATESTRMAX 20 // Date attribute
#define LINELENMAX 200 // Line in a file

typedef struct Node Node;

typedef struct
{
    char date[DATESTRMAX]; // dd.mm.yyyy HH:MM
    char week;

    unsigned consumption; // kWh
    unsigned solar;
    unsigned wind;
    unsigned hydro;
    unsigned nuclear;
    unsigned total;
    unsigned thermal;
} Data;

struct Node
{
    Data *data;
    Node *next;
};

Data* parseData(char* str)
{
    char* s = ";"; // Separator
    
    Data *data;
    if ((data = malloc(sizeof(Data))) == NULL)
    {
        perror("Virhe muistin kanssa :D");
        exit(0);
    }
    
    strcpy(data->date, strtok(str, s));
    data->week          = (char)atoi(strtok(NULL, s));
    data->consumption   = (unsigned)atoi(strtok(NULL, s));
    data->solar         = (unsigned)atoi(strtok(NULL, s));
    data->wind          = (unsigned)atoi(strtok(NULL, s));
    data->hydro         = (unsigned)atoi(strtok(NULL, s));
    data->nuclear       = (unsigned)atoi(strtok(NULL, s));
    data->total         = (unsigned)atoi(strtok(NULL, s));
    data->thermal       = (unsigned)atoi(strtok(NULL, s));

    return data;
}

void addNode(Node **head, Data *data)
{
    Node *new;
    if ((new = malloc(sizeof(Node))) == NULL)
    {
        perror("Muistin käsittelyssä virhe.");
        exit(0);
    }

    new->data = data;
    new->next = *head;
    *head = new;
}

void initHead(Node **head)
{
    Data *newdata;
    if ((newdata = malloc(sizeof(Data))) == NULL)
    {
        perror("Muistin kanssa virhe.");
        exit(0);
    }
    
    strcpy(newdata->date, "");
    newdata->consumption = 0;
    newdata->solar = 0;
    newdata->wind = 0;
    newdata->hydro = 0;
    newdata->nuclear = 0;
    newdata->total = 0;
    newdata->thermal = 0;

    addNode(head, newdata);
}

void reverse(Node **head)
{
    Node *prev = NULL;
    Node *curr = *head;
    Node *next = NULL;

    while (curr != NULL)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    *head = prev;
}

void write(Node *head)
{

    char fname[FNAMEMAX];
    printf("Anna kirjoitettavan tiedoston nimi: ");
    scanf("%s", fname);

    FILE *file;
    if ((file = fopen(fname, "w")) == NULL)
    {
        perror("Virhe tiedoston käsittelyssä.");
        exit(0);
    }
    
    unsigned total = 0;
    fprintf(file, "Aikaleima;Kumulatiivinen kulutus (kWh)\n");
    reverse(&head);
    Node *iter = head->next;
    while (iter != NULL)
    {
        total += iter->data->consumption;
        fprintf(file, "%s;%u\n", iter->data->date, total);
        iter = iter->next;
    }
    
    fclose(file);
    printf("Tiedosto '%s' kirjoitettu.\n\n", fname);
    reverse(&head);
}

void read(Node **head)
{
    char fname[FNAMEMAX];

    printf("Anna luettavan tiedoston nimi: ");
    scanf("%s", fname);

    FILE *file;
    if ((file = fopen(fname, "r")) == NULL)
    {
        perror("Virhe tiedoston lukemisessa.");
        exit(0);
    }

    char line[LINELENMAX];
    unsigned linecount = 0;

    while (fgets(line, LINELENMAX, file))
    {
        if (linecount++ != 0)
        {
            Data *data = parseData(line);
            addNode(head, data);
        }
    }

    fclose(file);
    printf("Tiedosto '%s' luettu.\n\n", fname);
}

void analyze(Node *head)
{
    unsigned count = 0;
    double sum = 0;
    unsigned max = 0;
    unsigned min = -1; // Underflow so we start with huge number
    Node *maxAt = NULL;
    Node *minAt = NULL;
    
    Node *iter = head;
    while (iter->next != NULL)
    {
        sum += (double)(iter->data->consumption);
        
        if (max < iter->data->consumption)
        {
            max = iter->data->consumption;
            maxAt = iter;
        }

        if (min > iter->data->consumption)
        {
            min = iter->data->consumption;
            minAt = iter;
        }

        ++count;
        iter = iter->next;

    }

    printf("Tilastotiedot %u mittaustuloksesta:\nKulutus oli yhteensä %u kWh, ja keskimäärin %.1f kWh.\nSuurin kulutus, %u kWh, tapahtui %s.\nPienin kulutus, %u kWh, tapahtui %s.\n\n",
            count, (unsigned)sum, sum / count, max, maxAt->data->date, min, minAt->data->date);
}

void clearList(Node *head)
{
    Node *iter = head;
    Node *prev = NULL;

    while (iter != NULL)
    {
        prev = iter;
        iter = iter->next;

        free(prev->data);
        free(prev);
    }
}

int main(void)
{
    Node *head = NULL;
    initHead(&head);
    
    int exit = 0; // Boolean
    while (!exit)
    {
        int opt;
        printf("Valitse haluamasi toiminto:\n1) Lue tiedosto\n2) Analysoi ja tulosta tiedot\n3) Kirjoita tulokset\n0) Lopeta\nAnna valintasi: ");
        scanf("%d", &opt);

        switch (opt)
        {
            case 0:
                exit = 1;
                break;
            case 1:
                read(&head);
                break;
            case 2:
                analyze(head);
                break;
            case 3:
                write(head);
                break;
            default:
                printf("Tuntematon valinta.\n");
        }
    }
    
    clearList(head->next);
    free(head->data);
    free(head);
   
    printf("\nKiitos ohjelman käytöstä.\n");
    return 0;
}
