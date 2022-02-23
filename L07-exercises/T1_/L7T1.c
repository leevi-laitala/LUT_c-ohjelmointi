#include "io.h"

int main(void)
{
    int buf[10 + 1] = { 0 }; // +1 because first index is used for sum
    int size = sizeof(buf) / sizeof(buf[0]);

    readSteps(buf, &size);

    print(buf, size);
    printf("Kiitos ohjelman käytöstä.\n");

    return 0;
}
