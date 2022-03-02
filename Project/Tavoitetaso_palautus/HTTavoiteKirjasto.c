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
/* Harjoitustyö - Tavoitetaso, HTTavoiteKirjasto.c */ 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "HTPerusKirjasto.h"

void dataParseTime(char *str, tm *t) // Parses time data from string format
{
    // Format dd.mm.yyyy HH:MM
    char buf[4] = { 0 };

    // Parse days
    buf[0] = str[0];
    buf[1] = str[1];
    t->tm_mday = atoi(buf);

    // Parse month
    buf[0] = str[3];
    buf[1] = str[4];
    t->tm_mon = atoi(buf);

    // Parse hour
    buf[0] = str[11];
    buf[1] = str[12];
    t->tm_hour = atoi(buf);

    // Parse minute
    buf[0] = str[14];
    buf[1] = str[15];
    t->tm_min = atoi(buf);

    // Parse year
    buf[0] = str[6];
    buf[1] = str[7];
    buf[2] = str[8];
    buf[3] = str[9];
    t->tm_year = atoi(buf);
}

// Analyze weekly data from list
void dataAnalyzeWeek(Node *head, WeekMatrix *mx)
{
    // Lined list iterator
    Node *iter = head; 
    while (iter->next != NULL)
    {
        Data *d = iter->data;
        char w = iter->data->week - 1; // Current week, -1 for correct index (starts at zero)

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

void fileWriteWeekly(Node *head)
{
    if (head->next == NULL) // Guard. Check if there is anything to write or analyze
    {
        printf("Ei analysoitavaa, lue tiedosto ennen analyysiä.\n\n");
        return;
    }

    // Initialize week matrix with width 6, for 6 data elements
    WeekMatrix mx = { 0, 0, NULL };
    matrixInit(&mx, 6, 1);

    // Get filename
    char fname[FN_MAX];
    fileGetFilename(fname, "Anna kirjoitettavan tiedoston nimi: ");
    
    // Analysze data from given linked list
    dataAnalyzeWeek(head, &mx);
    printf("Viikoittaiset tuotannot analysoitu.\n"); // Success
    
    // Output buffer
    char output[OUTPUT_MAX][LINE_MAX] = { 0 };
    size_t c = 0; // Line counter for output buffer

    snprintf(output[c++], LINE_MAX, "Viikko;Aurinkovoima;Tuulivoima;Vesivoima;Ydinvoima;Yhteistuotanto;Lämpövoima\n"); // Add titlerow to output
    for (unsigned i = 0; i < mx.width * mx.height; ++i) // Fill other rows with analysis results
    {
        char line[LINE_MAX] = { 0 }; // Temporary buffer to store single line

        if (i % mx.width == 0) // Check if we are in the beginning of the row
        {
            snprintf(line, LINE_MAX, "Vko %d", (int)(i / mx.width) + 1);
            strcat(output[c], line);
        }
        
        // Add numbers
        snprintf(line, LINE_MAX, ";%.2lf", (double)mx.matrix[i] / 1000000.f);
        strcat(output[c], line);

        // Add newline to the end of the row
        if ((i + 1) % mx.width == 0)
            strcat(output[c++], "\n");
    }
    
    // Open file
    FILE *file;
    if ((file = fopen(fname, "w")) == NULL)
        error("Tiedoston avaaminen epäonnistui, lopetetaan");

    // Print the whole output buffer to file
    for (size_t i = 0; i < c; ++i)
        fprintf(file, output[i]);

    // Free heap memory
    fclose(file);
    matrixClear(&mx);

    // Success
    printf("Tiedosto '%s' kirjoitettu.\n\n", fname);
}

// Allocate memoty for matrix
void matrixInit(WeekMatrix *mx, unsigned width, unsigned height)
{
    // Update matrix struct with it's new size
    mx->width = width;
    mx->height = height;
    
    // Allocate memory
    if ((mx->matrix = malloc(width * height * sizeof(long int))) == NULL)
        error("Virhe muistin käsittelyssä, lopetetaan.");

    // Initialize with zeroes
    for (unsigned i = 0; i < width * height; ++i)
        mx->matrix[i] = 0;
}

// void matrixPrint(WeekMatrix *mx)
// {
//     printf("Viikko;Aurinkovoima;Tuulivoima;Vesivoima;Ydinvoima;Yhteistuotanto;Lämpövoima\n");
//     for (unsigned i = 0; i < mx->width * mx->height; ++i)
//     {
//         if (i % mx->width == 0) printf("Vko %d", (int)(i / mx->width) + 1);
// 
//         printf(";%.2lf", (double)mx->matrix[i] / 1000000.f);
//         if ((i + 1) % mx->width == 0) printf("\n");
//     }
//     printf("\n");
// }

// Free heap allocation of given matrix
void matrixClear(WeekMatrix *mx)
{
    free(mx->matrix);
}

// Resize matrix to new size
void matrixResize(WeekMatrix *mx, unsigned width, unsigned height)
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

    // Save current matrix size
    unsigned oldW = mx->width;
    unsigned oldH = mx->height;
    
    // Update matrix container's size
    mx->width = width;
    mx->height = height;

    // Create copy of the old matrix
    WeekMatrix copy = { oldW, oldH, NULL };
    
    // Allocate memory for copy matrix
    if ((copy.matrix = malloc(oldW * oldH * sizeof(long int))) == NULL)
        error("Virhe muistin käsittelyssä, lopetetaan.");
    
    // Copy each element to the copy matrix
    for (unsigned i = 0; i < oldW * oldH; ++i) 
        copy.matrix[i] = mx->matrix[i];

    // Reallocate memory of given matrix
    if ((mx->matrix = realloc(mx->matrix, width * height * sizeof(long int))) == NULL)
        error("Virhe muistin käsittelyssä, lopetetaan.");

    // Copy data from the copy matrix back to the main matrix in previously demonstrated way
    // 
    // i is the main iterator and j is dummy iterator which keeps track of relative index of the matrix which is being copied into 
    for (unsigned i = 0, j = 0; i < MAX(width, oldW) * height; ++i)
    {
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

// Add data to matrix, more like set
void matrixAdd(WeekMatrix *mx, unsigned row, unsigned col, long int data)
{
    // If indices out of bounds of the current matrix, resize it
    if (row >= mx->height || col >= mx->width)
        matrixResize(mx, MAX(col + 1, mx->width), MAX(row + 1, mx->height));
    
    // Then add it to it
    mx->matrix[mx->width * row + col] = data;
}

// Add data to matrix
void matrixAddRelative(WeekMatrix *mx, unsigned row, unsigned col, long int data)
{
    // If indices out of bounds of the current matrix, resize it
    if (row >= mx->height || col >= mx->width)
        matrixResize(mx, MAX(col + 1, mx->width), MAX(row + 1, mx->height));
    
    // Then add it to it
    mx->matrix[mx->width * row + col] += data;
}

// Access elemest of matrix
long int matrixGet(WeekMatrix *mx, unsigned row, unsigned col)
{
    // Guard to stop invalid access
    if (row >= mx->height || col >= mx->width)
        return 0;

    return mx->matrix[row * mx->width + col];
}

