#include <stdio.h>

#define SIZE 2

void printMatrix(int m[SIZE][SIZE], char* name) {
    printf("\n%s:\n", name);
    for (unsigned i = 0; i < SIZE * SIZE; ++i) {
        printf("%4d ", m[(unsigned)(i / SIZE)][i % SIZE]);
        if (i % SIZE == 1) printf("\n");
    }
}

int main(void) {
    int m1[SIZE][SIZE], m2[SIZE][SIZE], m3[SIZE][SIZE];
    char* names[3] = { "Matriisi 1", "Matriisi 2", "Summamatriisi" };
    
    printf("Anna arvot yhteenlaskettaville matriiseille:\nMatriisin 1 alkiot:\n");
    for (unsigned i = 0; i < SIZE * SIZE; ++i) {
        printf("Rivi %d alkio %d: ", (unsigned)(i / SIZE) + 1, i % SIZE + 1);
        scanf("%d", &m1[(unsigned)(i / SIZE)][i % SIZE]);
    }
    
    printMatrix(m1, names[0]);

    printf("\nMatriisin 2 alkiot:\n");
    for (unsigned i = 0; i < SIZE * SIZE; ++i) {
        printf("Rivi %d alkio %d: ", (unsigned)(i / SIZE) + 1, i % SIZE + 1);
        scanf("%d", &m2[(unsigned)(i / SIZE)][i % SIZE]);
    }
    
    printMatrix(m2, names[1]);

    // Sum
    for (unsigned i = 0; i < SIZE * SIZE; ++i)
        m3[(unsigned)(i / SIZE)][i % SIZE] = m1[(unsigned)(i / SIZE)][i % SIZE] + m2[(unsigned)(i / SIZE)][i % SIZE];

    printMatrix(m3, names[2]);
    
    printf("\nKiitos ohjelman käytöstä.\n");

    return 0;
}
