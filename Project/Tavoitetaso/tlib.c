#ifndef TLIB_H
#define TLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "lib.h"

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

// Matrix container, to keep track of it's size
typedef struct
{
    unsigned width;
    unsigned height;
    unsigned long *matrix;
} WeekMatrix;

typedef struct tm tm;

void dataParseTime(char *str, tm *t) // Parses time data from string format
{
    // Format dd.mm.yyyy HH:MM
    char buf[4] = { 0 };

    // Parse days
    buf[0] = str[0];
    buf[1] = str[1];
    t->tm_mday = atoi(buf);
    //printf("Parsing date: %s : Day: %s, ", str, buf);

    // Parse month
    buf[0] = str[3];
    buf[1] = str[4];
    t->tm_mon = atoi(buf);
    //printf("Month: %s, ", buf);

    // Parse hour
    buf[0] = str[11];
    buf[1] = str[12];
    t->tm_hour = atoi(buf);
    //printf("Hour: %s, ", buf);

    // Parse minute
    buf[0] = str[14];
    buf[1] = str[15];
    t->tm_min = atoi(buf);
    //printf("Minute: %s, ", buf);

    // Parse year
    buf[0] = str[6];
    buf[1] = str[7];
    buf[2] = str[8];
    buf[3] = str[9];
    t->tm_year = atoi(buf);
    //printf("Year: %s\n", buf);
}

void matrixInit(WeekMatrix *mx, unsigned width, unsigned height) // Allocates memory for matrix
{
    mx->width = width;
    mx->height = height;

    if ((mx->matrix = malloc(width * height * sizeof(unsigned long))) == NULL)
    {
        perror("Virhe muistin käsittelyssä, lopetetaan.");
        exit(0);
    }

    for (unsigned i = 0; i < width * height; ++i) // Initialize with zeros
        mx->matrix[i] = 0;
}

//void matrixPrint(WeekMatrix *mx) // Prints matrix
//{
//    for (unsigned i = 0; i < mx->width * mx->height; ++i)
//    {
//        printf("%lu ", mx->matrix[i]);
//        if ((i + 1) % mx->width == 0) printf("\n");
//    }
//    printf("\n");
//}

void matrixPrint(WeekMatrix *mx) // Prints matrix
{
    printf("Viikko;Aurinkovoima;Tuulivoima;Vesivoima;Ydinvoima;Yhteistuotanto;Lämpövoima\n");
    for (unsigned i = 0; i < mx->width * mx->height; ++i)
    {
        if (i % mx->width == 0) printf("Vko %d", (int)(i / mx->width) + 1);

        printf(";%.2lf", (double)mx->matrix[i] / 1000000.f);
        if ((i + 1) % mx->width == 0) printf("\n");
    }
    printf("\n");
}

void matrixClear(WeekMatrix *mx) // Free matrix
{
    free(mx->matrix);
}

void matrixResize(WeekMatrix *mx, unsigned width, unsigned height) // Resizes matrix to new size
{
    // Matrices are anchored to top left corner
    //
    // 3x3 matrix downsized to 2x2 looks like this:
    //  
    //  1 2 3        1 2    
    //  4 5 6   -->  4 5
    //  7 8 9
    //
    // 2x2 matrix resized to 3x3 looks like this:
    //
    //  1 2          1 2 0 
    //  3 4     -->  3 4 0
    //               0 0 0
    //

    unsigned oldW = mx->width; // Current matrix size, before resize
    unsigned oldH = mx->height;

    mx->width = width; // Update matrix container's size
    mx->height = height;

    WeekMatrix copy = { oldW, oldH, NULL }; // Create copy of the old matrix

    if ((copy.matrix = malloc(oldW * oldH * sizeof(unsigned long))) == NULL)
    {
        perror("Virhe muistin käsittelyssä, lopetetaan.");
        exit(0);
    }

    for (unsigned i = 0; i < oldW * oldH; ++i) // Copy each element to the copy
        copy.matrix[i] = mx->matrix[i];

    if ((mx->matrix = realloc(mx->matrix, width * height * sizeof(unsigned long))) == NULL)
    {
        perror("Virhe muistin käsittelyssä, lopetetaan.");
        exit(0);
    }

    // Copy data from the copy matrix back to the main matrix in previously demonstrated way
    for (unsigned i = 0, j = 0; i < MAX(width, oldW) * height; ++i)
    {
        //if (width > oldW)
        //    mx->matrix[i] = (i % width < oldW) ? copy.matrix[j++] : 0;
        //else if ((width < oldW) && (i % oldW < width))
        //    mx->matrix[j++] = copy.matrix[i];
        if (width > oldW)
            mx->matrix[i] = (i % width < oldW) ? copy.matrix[j++] : 0;
        else if (i % oldW < width)
        {
            if (width < oldW) 
                mx->matrix[j++] = copy.matrix[i];
            else
                mx->matrix[i] = 0;
        }
    }

    // Free copy matrix heap allocation
    matrixClear(&copy);
}

void matrixAdd(WeekMatrix *mx, unsigned row, unsigned col, unsigned long data) // Add data to matrix
{
    // If coordinates out of bounds of the current matrix, resize it
    if (row + 1 > mx->height || col + 1 > mx->width)
        matrixResize(mx, MAX(col + 1, mx->width), MAX(row + 1, mx->height));
    
    // Then add it to it
    mx->matrix[mx->width * row + col] = data;
}

unsigned long matrixGet(WeekMatrix *mx, unsigned row, unsigned col) // Access element of matrix
{
    return mx->matrix[row * mx->width + col];
}

void dataAnalyzeWeek(Node *head, WeekMatrix *mx)
{
    Node *iter = head;

    while (iter->next != NULL)
    {
        Data *d = iter->data;
        char w = iter->data->week; // Current week

        matrixAdd(mx, w - 1, 0, d->solar   + matrixGet(mx, w - 1, 0));
        matrixAdd(mx, w - 1, 1, d->wind    + matrixGet(mx, w - 1, 1));
        matrixAdd(mx, w - 1, 2, d->hydro   + matrixGet(mx, w - 1, 2));
        matrixAdd(mx, w - 1, 3, d->nuclear + matrixGet(mx, w - 1, 3));
        matrixAdd(mx, w - 1, 4, d->total   + matrixGet(mx, w - 1, 4));
        matrixAdd(mx, w - 1, 5, d->thermal + matrixGet(mx, w - 1, 5));

        iter = iter->next;
    }

    matrixPrint(mx);
}

#endif // TLIB_H
