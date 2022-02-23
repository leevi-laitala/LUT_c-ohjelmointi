#ifndef IO_H
#define IO_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LINELENMAX 20

int readSteps(int *buf, int *size);
void print(int *buf, int size);

#endif
