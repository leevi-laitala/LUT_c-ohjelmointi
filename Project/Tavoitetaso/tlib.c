#ifndef TLIB_H
#define TLIB_H

/*************************************************************************/ 
/* CT60A2500 C-ohjelmoinnin perusteet  
 * Tekijä: Leevi Laitala
 * Opiskelijanumero: 0606070
 * Päivämäärä: 25.02.2022
 * Palauttamalla tämän työn arvioitavaksi vakuutan, että  
 * 1) Olen itse kirjoittanut kaiken tässä tiedostossa olevan koodin 
 * 2) En ole antanut tätä koodia kenenkään muun käyttöön 
 *  
 * Kurssin oppimateriaalien lisäksi työhön ovat vaikuttaneet seuraavat  
 * lähteet ja henkilöt, ja se näkyy koodissa seuraavissa kohdissa: 
 * - ... 
 */ 
/*************************************************************************/ 
/* Harjoitustyö - Tavoitetaso, tlib.c */ 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "lib.h"

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

// Matrix container, to keep track of it's size
typedef struct
{
    unsigned width;
    unsigned height;
    //unsigned long *matrix; // Matrices are stored as one dimensional array of long ints
    long int *matrix; // Matrices are stored as one dimensional array of long ints
} WeekMatrix;

void dataParseTime(char *str, struct tm *t) // Parses time data from string format
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
    // 
    // i is the main iterator and j is dummy iterator which keeps track of relative index of the matrix which is being copied into 
    for (unsigned i = 0, j = 0; i < MAX(width, oldW) * height; ++i)
    {
        //if (width > oldW)
        //    mx->matrix[i] = (i % width < oldW) ? copy.matrix[j++] : 0;
        //else if ((width < oldW) && (i % oldW < width))
        //    mx->matrix[j++] = copy.matrix[i];

        if (width > oldW) // Upsizing
            mx->matrix[i] = (i % width < oldW) ? copy.matrix[j++] : 0;
        else if (i % oldW < width)
        {
            if (width < oldW) // Downsizing
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
    // If indices out of bounds of the current matrix, resize it
    if (row >= mx->height || col >= mx->width)
        matrixResize(mx, MAX(col + 1, mx->width), MAX(row + 1, mx->height));
    
    // Then add it to it
    mx->matrix[mx->width * row + col] = data;
}

void matrixAddRelative(WeekMatrix *mx, unsigned row, unsigned col, unsigned long data) // Add data to matrix
{
    // If indices out of bounds of the current matrix, resize it
    if (row >= mx->height || col >= mx->width)
        matrixResize(mx, MAX(col + 1, mx->width), MAX(row + 1, mx->height));
    
    // Then add it to it
    mx->matrix[mx->width * row + col] += data;
}

unsigned long matrixGet(WeekMatrix *mx, unsigned row, unsigned col) // Access element of matrix
{
    if (row >= mx->height || col >= mx->width)
        return 0;

    return mx->matrix[row * mx->width + col];
}

void dataAnalyzeWeek(Node *head, WeekMatrix *mx)
{
    Node *iter = head; // Linked list iterator
    while (iter->next != NULL)
    {
        Data *d = iter->data;
        char w = iter->data->week - 1; // Current week, -1 for correct index

        char c = 0; // Column counter
        matrixAddRelative(mx, w, c++, d->solar);
        matrixAddRelative(mx, w, c++, d->wind);
        matrixAddRelative(mx, w, c++, d->hydro);
        matrixAddRelative(mx, w, c++, d->nuclear);
        matrixAddRelative(mx, w, c++, d->total);
        matrixAddRelative(mx, w, c++, d->thermal);

        // Jump to next node
        iter = iter->next;
    }
}

void fileWriteWeekly(WeekMatrix *mx)
{
    char fname[FN_MAX];
    fileGetFilename(fname, "Anna kirjoitettavan tiedoston nimi: ");
    
    char output[OUTPUT_MAX][LINE_MAX] = { 0 }; // Output buffer
    size_t c = 0; // Line counter

    snprintf(output[c++], LINE_MAX, "Viikko;Aurinkovoima;Tuulivoima;Vesivoima;Ydinvoima;Yhteistuotanto;Lämpövoima\n");
    for (unsigned i = 0; i < mx->width * mx->height; ++i)
    {
        char line[LINE_MAX] = { 0 }; // Temporary buffer to store single line

        if (i % mx->width == 0)
        {
            snprintf(line, LINE_MAX, "Vko %d", (int)(i / mx->width) + 1);
            strcat(output[c], line);
        }
        
        snprintf(line, LINE_MAX, ";%.2lf", (double)mx->matrix[i] / 1000000.f);

        strcat(output[c], line);

        if ((i + 1) % mx->width == 0)
            strcat(output[c++], "\n");
    }
    
    
    FILE *file;
    if ((file = fopen(fname, "w")) == NULL)
    {
        perror("Virhe tiedoston käsittelyssä.");
        exit(0);
    }

    for (size_t i = 0; i < c; ++i)
        fprintf(file, output[i]);

    fclose(file);
    printf("Tiedosto '%s' kirjoitettu.\n\n", fname);
}

#endif // TLIB_H
