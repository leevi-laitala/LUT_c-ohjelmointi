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
/* Harjoitustyö - Tavoitetaso, HTPerusKirjasto.c */ 

#include "HTPerusKirjasto.h"

//
//  *** File IO ***
//

void fileGetFilename(char buf[FN_MAX], char *prompt)
{
    printf(prompt);
    fflush(stdout);
    fgets(buf, FN_MAX, stdin);
    
    size_t s = strlen(buf);
    buf[s - 1] = '\0';
}

void fileRead(Node **head)
{
    // Clear list 
    listClear(*head);
    *head = NULL;
    listInit(head);

    // Get filename
    char fname[FN_MAX];
    fileGetFilename(fname, "Anna luettavan tiedoston nimi: ");
    
    // Open file stream
    FILE *file;
    if ((file = fopen(fname, "r")) == NULL)
        error("Tiedoston avaaminen epäonnistui, lopetetaan");
    
    // Init line buffer
    char line[LINE_MAX];
    unsigned c = 0; // Line counter, used to skip title row on the file

    while (fgets(line, LINE_MAX, file)) // Iterate through lines in given file
    {
        if (c++ != 0) // Skip first line
        {
            Data *data = dataParse(line); // Parse line
            listAdd(head, data); // Add parsed data to new node in linked list
        }
    }
    
    // Close file and print success message
    fclose(file);
    printf("Tiedosto '%s' luettu.\n\n", fname);
}

void fileWrite(AnalysisResult *res)
{
    if (res->amount == 0)
    {
        printf("Ei kirjoitettavia tietoja, analysoi tiedot ennen tallennusta.\n\n");
        return;
    }

    // Get filename
    char fname[FN_MAX] = { 0 };
    fileGetFilename(fname, "Anna kirjoitettavan tiedoston nimi: ");

    size_t c = 0; // Init output buffer line counter

    char output[OUTPUT_MAX][LINE_MAX] = { 0 }; // Init output buffer

    // Fill output buffer
    snprintf(output[c++], LINE_MAX, "Tilastotiedot %d mittaustuloksesta:\n", res->amount);
    snprintf(output[c++], LINE_MAX, "Kulutus oli yhteensä %lu kWh, ja keskimäärin %.1f kWh.\n", res->total, res->average);
    snprintf(output[c++], LINE_MAX, "Suurin kulutus, %u kWh, tapahtui %s.\n", res->max, res->maxAt->date);
    snprintf(output[c++], LINE_MAX, "Pienin kulutus, %u kWh, tapahtui %s.\n", res->min, res->minAt->date);
    snprintf(output[c++], LINE_MAX, "\n");
    snprintf(output[c++], LINE_MAX, "Pvm;Tuotanto (GWh)\n");
    for (size_t i = 0; i < 12; ++i) // Iterate month data, and calculate averages in the printf function
        snprintf(output[c++], LINE_MAX, "Kk %u;%.2f\n", res->monthdata[i].month, res->monthdata[i].total / 1000000.f);

    // Iterate through output buffer
    for (size_t i = 0; i < c; ++i)
        printf(output[i]); // Print output buffer's contents to stdout

    // Open file stream
    FILE *file;
    if ((file = fopen(fname, "w")) == NULL)
        error("Tiedoston avaaminen epäonnistui, lopetetaan");

    // Iterate through output buffer
    for (size_t i = 0; i < c; ++i)
        fprintf(file, output[i]); // Print to file stream
    
    // Close file and print success message
    fclose(file);
    printf("Tiedosto '%s' kirjoitettu.\n\n", fname);
}


//
//  *** Linked list functionality ***
//

void listInit(Node **head) // Initialize linked list
{
    // Create empty data node
    Data *emptydata;
    if ((emptydata = malloc(sizeof(Data))) == NULL)
        error("Muistinvaraus epäonnistui, lopetetaan");
    
    strcpy(emptydata->date, "");
    emptydata->consumption = 0;
    emptydata->solar = 0;
    emptydata->wind = 0;
    emptydata->hydro = 0;
    emptydata->nuclear = 0;
    emptydata->total = 0;
    emptydata->thermal = 0;
    
    // Add node with empty data
    listAdd(head, emptydata);
}

void listAdd(Node **head, Data *data) // Add node to linked list
{
    // Create new node
    Node *new;
    if ((new = malloc(sizeof(Node))) == NULL)
        error("Muistinvaraus epäonnistui, lopetetaan");

    // Add node to list
    new->data = data;
    new->next = *head;
    *head = new; 
}

// void listReverse(Node **head) // Reverse list
// {
//     Node *prev = NULL;
//     Node *curr = *head;
//     Node *next = NULL;
// 
//     while (curr != NULL)
//     {
//         next = curr->next;
//         curr->next = prev;
//         prev = curr;
//         curr = next;
//     }
//     *head = prev;
// }

void listClear(Node *head) // Clear list and free memory
{
    Node *iter = head;
    Node *prev = NULL; // Keeps track of where we currently stand

    while (iter != NULL)
    {
        prev = iter; // Save current node to variable, and jump to next
        iter = iter->next;

        free(prev->data); // Free saved current node
        free(prev);
    }
}

//
//  *** Data Analysis ***
//

Data* dataParse(char *str) // Parses data from string
{
    char* s = ";"; // Separator, used by strtok()
    
    // Create new data block
    Data *data;
    if ((data = malloc(sizeof(Data))) == NULL)
        error("Muistinvaraus epäonnistui, lopetetaan");
    
    // Split string into "columns" using strtok,
    // and save each "column" to their own variables
    strcpy(data->date, strtok(str, s));
    data->week          = (char)atoi(strtok(NULL, s));

    data->consumption   = (unsigned)atoi(strtok(NULL, s));
    data->solar         = (unsigned)atoi(strtok(NULL, s));
    data->wind          = (unsigned)atoi(strtok(NULL, s));
    data->hydro         = (unsigned)atoi(strtok(NULL, s));
    data->nuclear       = (unsigned)atoi(strtok(NULL, s));
    data->total         = (unsigned)atoi(strtok(NULL, s));
    data->thermal       = (unsigned)atoi(strtok(NULL, s));

    return data; // Return pointer to created data block
}

void dataAnalyze(Node *head, AnalysisResult *res) // Analyzes data in linked list
{
    if (head->next == NULL)
    {
        printf("Ei analysoitavaa, lue tiedosto ennen analyysiä.\n\n");
        return;
    }

    // For comparisons init max with small value, and min with large value
    res->max = 0;
    res->min = -1; // Underflow to make number huge
    
    Node *iter = head; // Init iterating node to begin from head
    while (iter->next != NULL)
    {
        dataParseTime(iter->data->date, &iter->data->time); // Parse date

        res->total += iter->data->consumption; // Add total consumption to sum
        
        if (res->max < iter->data->consumption) // Compare consumption to previous max
        {
            res->max = iter->data->consumption; // If greater, set new max
            res->maxAt = iter->data; // And save the data node, so we can later get it's date
        }

        if (res->min > iter->data->consumption) // Same thing to min
        {
            res->min = iter->data->consumption;
            res->minAt = iter->data;
        }
        
        for (size_t i = 0; i < 12; ++i) // Initialize each node's month array to contain month numbers
            res->monthdata[i].month = i + 1;

        unsigned index = iter->data->time.tm_mon - 1;

        Data *cur = iter->data; // Alias for sum calculation

        res->monthdata[index].total += cur->solar + cur->wind + cur->hydro + cur->nuclear + cur->total + cur->thermal;

        res->amount++; // Amount tells how many nodes has been processed
        iter = iter->next; // Jump to next node
    }

    // Calculate average after we know how many nodes there were
    res->average = (double)(res->total) / res->amount;

    // Print success message
    printf("Analysoitu %u mittaustulosta.\nKokonaiskulutus oli yhteensä %lu kWh.\nKuukausittaiset tuotannot analysoitu.\n\n",
            res->amount, res->total);
}

//
// *** Misc ***
//

void error(char *msg) // Unnecessary, but makes error cheks faster to write
{
    perror(msg);
    exit(0);
}
