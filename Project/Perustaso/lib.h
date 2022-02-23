#ifndef LIB_H
#define LIB_H

/*************************************************************************/ 
/* CT60A2500 C-ohjelmoinnin perusteet  
 * Tekijä: Leevi Laitala
 * Opiskelijanumero: 0606070
 * Päivämäärä: 22.02.2022
 * Palauttamalla tämän työn arvioitavaksi vakuutan, että  
 * 1) Olen itse kirjoittanut kaiken tässä tiedostossa olevan koodin 
 * 2) En ole antanut tätä koodia kenenkään muun käyttöön 
 *  
 * Kurssin oppimateriaalien lisäksi työhön ovat vaikuttaneet seuraavat  
 * lähteet ja henkilöt, ja se näkyy koodissa seuraavissa kohdissa: 
 * - ... 
 */ 
/*************************************************************************/ 
/* Harjoitustyö - Perustaso, lib.h */ 

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LINE_MAX 200 // Line max length
#define OUTPUT_MAX 50 // Output file max length
#define FN_MAX 30 // Filename max length
#define DATE_MAX 20 // Date string max length

typedef struct
{
    char date[DATE_MAX]; // Format dd.mm.yyyy HH:MM
    char week;

    unsigned consumption;
    unsigned solar;
    unsigned wind;
    unsigned hydro;
    unsigned nuclear;
    unsigned total;
    unsigned thermal;
} Data;

typedef struct Node Node;

struct Node
{
    Data *data;
    Node *next;
};

typedef struct
{
    char month;
    unsigned long total;
} MonthData;

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

#endif // LIB_H
