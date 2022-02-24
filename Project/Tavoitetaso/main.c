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
/* Harjoitustyö - Perustaso, main.c */ 

#include "lib.h"
#include "tlib.c"

int main(void)
{
    // Init head of linked list
    Node *head = NULL;
    listInit(&head);

    // Init analysis result container
    AnalysisResult analysisResult = {
        0, // Amount
        0, // Total (sum) 
        0.0, // Average
        0, // Max
        (unsigned)-1, // Min
        NULL, // Pointer to max node
        NULL, // Pointer to min node
        {{ 0 }} // Initialize array with zeroes
    };

    WeekMatrix weekMatrix = { 0, 0, NULL };
    matrixInit(&weekMatrix, 6, 1); // Init with 1x6 matrix, 6 for 6 data elements


    char exit = 0; // If non zero, exit from while
    char opt[1]; // Container for user option
    while (!exit)
    {
        printf("Valitse haluamasi toiminto:\n1) Lue tiedosto\n2) Analysoi tiedot\n3) Kirjoita tulokset\n4) Laske viikottaiset tulokset\n0) Lopeta\nAnna valintasi: ");
        scanf("%s", opt);

        switch (opt[0])
        {
            case '0':
                ++exit; // Makes exit non zero, so while loop will break
                break;
            case '1':
                fileRead(&head);
                break;
            case '2':
                // Clear current analysis
                analysisResult = (AnalysisResult){ 0, 0, 0.0, 0, (unsigned)-1, NULL, NULL, {{ 0 }} };
                dataAnalyze(head, &analysisResult);
                break;
            case '3':
                fileWrite(&analysisResult);
                break;
            case '4':
                dataAnalyzeWeek(head, &weekMatrix);
                break;
            default:
                printf("Tuntematon valinta.\n\n");
        }
    }

    listClear(head); // Free heap allocations
    matrixClear(&weekMatrix);
    printf("\nKiitos ohjelman käytöstä.\n");

    return 0;
}
