#include "io.h"

int readSteps(int *buf, int *size)
{
    FILE *file;
    if ((file = fopen("askeldata.txt", "r")) == NULL)
    {
        perror("Virhe tiedoston käsittelyssä.");
        exit(0);
    }

    char line[LINELENMAX];

    for (char i = 1; i < *size; ++i)
    {
        fgets(line, LINELENMAX, file);
        strtok(line, ":");
        
        buf[i] = atoi(strtok(NULL, ":"));
        buf[0] += buf[i];
    }

    fclose(file);
}

void print(int *buf, int size)
{
    printf("Askelanalyysi\nListan askeleet: ");
    for (char i = 1; i < size; ++i)
        printf("%d ", buf[i]);

    printf("\nAskelia yhteensä: %d\n", buf[0]);
}
