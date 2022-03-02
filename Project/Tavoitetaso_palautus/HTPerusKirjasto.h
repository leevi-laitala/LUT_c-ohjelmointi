#ifndef HTPERUSKIRJASTO_H
#define HTPERUSKIRJASTO_H

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
/* Harjoitustyö - Tavoitetaso, HTPerusKirjasto.h */ 

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define LINE_MAX 200 // Line max length
#define OUTPUT_MAX 100 // Output file max length
#define FN_MAX 30 // Filename max length
#define DATE_MAX 20 // Date string max length

// Handy macros
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

typedef struct tm tm;

// Datatype where files are parsed
typedef struct
{
    char date[DATE_MAX]; // Format dd.mm.yyyy HH:MM
    tm time;
    char week;

    unsigned consumption;
    unsigned solar;
    unsigned wind;
    unsigned hydro;
    unsigned nuclear;
    unsigned total;
    int thermal; // Can be negative
} Data;

// Linked list node
typedef struct Node Node;

struct Node
{
    Data *data;
    Node *next;
};

// Month and it's sum
typedef struct
{
    char month;
    unsigned long total;
} MonthData;

// Container for analysis results
typedef struct
{
    unsigned amount;
    unsigned long total;
    double average;
    unsigned min;
    unsigned max;
    Data *minAt;
    Data *maxAt;
    MonthData monthdata[12];
} AnalysisResult;

// Matrix container, to keep track of it's size
typedef struct
{
    unsigned width;
    unsigned height;
    //unsigned long *matrix; // Matrices are stored as one dimensional array of long ints
    long int *matrix; // Matrices are stored as one dimensional array of long ints
} WeekMatrix;

// File IO
void fileGetFilename(char buf[FN_MAX], char *prompt);
void fileRead(Node **head);
void fileWrite(AnalysisResult *res);

// Linked list functionality
void listInit(Node **head);
void listAdd(Node **head, Data *data);
//void listReverse(Node **head);
void listClear(Node *head);

// Data analysis
Data* dataParse(char *str);
void dataAnalyze(Node *head, AnalysisResult *res);

// Misc
void error(char *msg);

//
// *** Tavotietaso function forward declarations ***
//
void dataParseTime(char *str, tm *t);
void dataAnalyzeWeek(Node *head, WeekMatrix *mx);

void fileWriteWeekly(Node *head);

void matrixInit(WeekMatrix *mx, unsigned width, unsigned height);
void matrixPrint(WeekMatrix *mx);
void matrixClear(WeekMatrix *mx);
void matrixResize(WeekMatrix *mx, unsigned width, unsigned height);
void matrixAdd(WeekMatrix *mx, unsigned row, unsigned col, long int data);
void matrixAddRelative(WeekMatrix *mx, unsigned row, unsigned col, long int data);
long int matrixGet(WeekMatrix *mx, unsigned row, unsigned col);

#endif // HTPERUSKIRJASTO_H
