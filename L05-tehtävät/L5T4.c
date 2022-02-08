#include <stdio.h>
#include <stdlib.h>

int* allocateMemory(int* ptr, int size)
{
    if (ptr == NULL)
    {
        if ((ptr = malloc(size * sizeof(int))) == NULL)
        { 
            perror("Muisin varaus epäonnistui");
            exit(0);
        }
    } else
    {
        ptr = realloc(ptr, size * sizeof(int));
    }

    for (int i = 0; i < size; ++i) 
        ptr[i] = i;

    return ptr;
}

void printArr(int* ptr, int size)
{
    if (size == 0)
        printf("Taulukko on tyhjä.\n");
    else
    {
        printf("Taulukon alkiot ovat: ");
        for (int i = 0; i < size; ++i)
            printf("%d ", ptr[i]);
        printf("\n");
    }
}

int main(void)
{
    int* ptr = NULL;
    int size = 0;

    char opt;
    for (;;)
    {
        printf("1) Tulosta taulukon alkiot\n2) Muuta taulukon kokoa\n0) Lopeta\nAnna valintasi: ");
        scanf(" %c", &opt);

        switch (opt)
        {
        case '0':
            free(ptr);
            printf("Muisti vapautettu.\nKiitos ohjelman käytöstä.\n");
            return 0;
        case '1':
            printArr(ptr, size);
            break;
        case '2':
            printf("Anna taulukon uusi koko: ");
            int newsize = 0;
            scanf("%d", &newsize);
            if (newsize < 0)
            {
                printf("Taulukon koko ei voi olla negatiivinen.\n");
                break;
            }
            size = newsize;
            ptr = allocateMemory(ptr, size);
            break;
        default:
            printf("Tuntematon valinta, yritä uudestaan.\n");
        }
    }

    return 0;
}
