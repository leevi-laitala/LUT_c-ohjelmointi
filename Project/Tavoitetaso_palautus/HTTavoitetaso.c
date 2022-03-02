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
/* Harjoitustyö - Tavoitetaso, HTTavoitetaso.c */ 

#include "HTPerusKirjasto.h"

int main(void)
{
    // Init head of linked list
    Node *head = NULL;
    listInit(&head);

    // Init analysis result container
    AnalysisResult analysisResult = { 0, 0, 0.0, 0, (unsigned)-1, NULL, NULL, {{ 0 }} };

    // Used for while loop. If non zero, exit from loop
    char exit = 0;

    // User input
    char buf[FN_MAX] = { 0 };

    while (!exit)
    {
        printf("Valitse haluamasi toiminto:\n1) Lue tiedosto\n2) Analysoi tiedot\n3) Kirjoita tulokset\n4) Laske viikoittaiset tulokset\n0) Lopeta\nAnna valintasi: ");

        fflush(stdout);
        fgets(buf, sizeof(buf) / sizeof(buf[0]), stdin);

        switch (buf[0])
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
                fileWriteWeekly(head);
                break;
            default:
                printf("Tuntematon valinta, yritä uudestaan.\n\n");
        }
    }

    listClear(head); // Free list's heap allocations
    printf("\nKiitos ohjelman käytöstä.\n");

    return 0;
}
