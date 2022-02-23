#include <stdio.h>
#include <stdlib.h>

int checkInput(int* argc, const char* argv)
{
    int size;

    if ((*argc < 2) || ((size = atoi(argv)) == 0 && *argv != '0')) 
    {
        printf("Et antanut taulukon kokoa.\n");
        size = 0;
    } else if (size <= 0)
    {
        printf("Parametri ei ollut positiivinen kokonaisluku.\n");
        size = 0;
    }

    return size;
}

int* allocateMemory(int size)
{
    int* ptr;
    if ((ptr = malloc(size * sizeof(int))) == NULL)
    {
        perror("Muisin varaus epäonnistui");
        exit(0);
    }

    printf("Muistin varaus onnistui.\nTaulukossa on tilaa %d alkiolle.\n", size);

    return ptr;
}

void fill(int* ptr, int size)
{
    int num;

    for (unsigned i = 0; i < size; ++i)
    {
        printf("Anna %d. luku: ", i + 1);
        scanf("%d", &num);
        
        ptr[i] = num;
    }

    printf("Taulukko täytetty.\nTaulukossa on luvut: ");
    for (unsigned i = 0; i < size; ++i)
        printf("%d ", ptr[i]);

    printf("\nTaulukko tulostettu.\n");
}

void freeMemory(int* ptr)
{
    free(ptr);
    printf("Muisti vapautettu.\n");
}

int main(int argc, const char* argv[])
{   
    int size = checkInput(&argc, argv[1]);
    
    if (size == 0) return 0;

    int* arr = allocateMemory(size);

    fill(arr, size);

    freeMemory(arr);
    
    printf("Kiitos ohjelman käytöstä.\n");

    return 0;
}
