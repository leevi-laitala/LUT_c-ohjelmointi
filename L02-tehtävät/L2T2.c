#include <stdio.h>

int main(void) {
    int num;
    int sum = 0;

    printf("Anna jokin luku väliltä 10 - 200: ");
    scanf("%d", &num);

    if (num < 10 | num > 200) {
        printf("Antamasi luku ei ole annetulla välillä.\n");
        return 0;
    }

    for (int i = 0; i <= num; i++)
        sum += i;

    printf("Lukujen 0 - %d summa on %d.\n", num, sum);

    return 0;
}
