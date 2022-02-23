#include <stdio.h>

int main(void) {
    char first[10];
    char last[20];
    int age;
    float weight;

    printf("Anna etunimesi: ");
    scanf("%s", first);

    printf("Anna sukunimesi: ");
    scanf("%s", last);

    printf("Anna ikäsi: ");
    scanf("%d", &age);

    printf("Anna painosi: ");
    scanf("%f", &weight);

    printf("Nimesi on %s %s, ikäsi on %d vuotta ja painat %0.1f kg.\n", first, last, age, weight);

    return 0;
}
