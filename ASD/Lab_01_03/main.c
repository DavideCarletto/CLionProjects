#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_S 30
#define MAX_T 1000

typedef struct {
    char codice[MAX_S];
    char partenza[MAX_S];
    char destinazione[MAX_S];
    char data[MAX_S];
    char oraPartenza[MAX_S];
    char oraArrivo[MAX_S];
    int ritardo;
    char stringhe[4][MAX_S];
} s_tratta;

typedef enum {
    stampa, o_data, o_codice, o_partenza, o_arrivo, r_partenza, r_fine, r_err
}comando;

int leggiFile(FILE *fin, s_tratta *elencoTratte);
void menuTratte(s_tratta *elencoTratte, int dim);
int leggiComando();
void stampaTratte(s_tratta *elencoTratte, int dim);
void ordina(s_tratta elencoTratte[], int dim, int orderBy);

int main() {

    FILE *fin;
    s_tratta *elencoTratte = (s_tratta*) malloc(sizeof(s_tratta)*MAX_T);

    int dim;

    if ((fin = fopen("../corse.txt", "r")) == NULL) {
        printf("Error opening file corse.txt");
        return -1;
    }

    dim = leggiFile(fin, elencoTratte);
    elencoTratte = (s_tratta*) realloc(elencoTratte,sizeof (s_tratta)*(dim));
    menuTratte(elencoTratte,dim);

    return 0;
}

int leggiFile(FILE *fin, s_tratta *elencoTratte) {
    int dim;

    while (!feof(fin)) {
        fscanf(fin, "%d", &dim);
        if (!feof(fin)) {
            for (int i = 0; i < dim; i++) {
                fscanf(fin, "%s %s %s %s %s %s %d", &elencoTratte[i].codice, &elencoTratte[i].partenza,&elencoTratte[i].destinazione, &elencoTratte[i].data, &elencoTratte[i].oraPartenza,&elencoTratte[i].oraArrivo, &elencoTratte[i].ritardo);
                strcpy(elencoTratte[i].stringhe[0],elencoTratte[i].data);
                strcpy(elencoTratte[i].stringhe[1], elencoTratte[i].codice);
                strcpy(elencoTratte[i].stringhe[2], elencoTratte[i].partenza);
                strcpy(elencoTratte[i].stringhe[3], elencoTratte[i].destinazione);
            }
        }
    }
    return dim;
}

void menuTratte(s_tratta *elencoTratte, int dim){
    int continua = 1, comando =0;

    while(continua){
        printf("CMD 'stampa': stampa le tratte\n"
               "CMD 'o_data': ordina le tratte per data\n"
               "CMD 'o_codice': ordina le tratte per codice\n"
               "CMD 'o_partenza': ordina le tratte per stazione di partenza\n"
               "CMD 'o_arrivo': ordina le tratte per stazione di arrivo\n"
               "CMD 'r_partenza': ricerca di una tratta per stazione di partenza\n"
               "CMD 'fine: per terminare\n\n");

        comando = leggiComando();

        switch (comando) {
            char *codice;
            case stampa:
                stampaTratte(elencoTratte,dim);
                printf("\n");
                break;
            case o_data:
                ordina(elencoTratte,dim, comando-1);
                stampaTratte(elencoTratte,dim);
                break;
            case o_codice:
                ordina(elencoTratte,dim, comando-1);
                stampaTratte(elencoTratte,dim);
                break;
            case o_partenza:
                ordina(elencoTratte,dim, comando-1);
                stampaTratte(elencoTratte,dim);
                break;
            case o_arrivo:
                ordina(elencoTratte,dim, comando-1);
                stampaTratte(elencoTratte,dim);
                break;
            case r_partenza:
                break;
            case r_fine:
                printf("Done");
                continua = 0;
                break;
            case r_err:
                printf("Errore comando");
                continua = 0;
                break;
            default:
                break;
        }
    }
}

int leggiComando(){
    char comando[MAX_S];
    char tabella[7][MAX_S] = {"stampa", "o_data", "o_codice", "o_partenza", "o_arrivo", "r_partenza", "fine"};

    printf("Inserire comando: ");
    scanf("%s", comando);

    int c = stampa;
    while (c < r_err && strcmp(comando, tabella[c]) != 0)
        c++;

    return c;
}

void ordina(s_tratta elencoTratte[], int dim, int orderBy) {
    int i, j, l=0, r=dim-1;
    s_tratta curr;

    for (i = l+1; i <= r; i++) {
        curr = elencoTratte[i];

        for(int k = 0; k<4; k++){
            strcpy(curr.stringhe[k],elencoTratte[i].stringhe[k]);
        }

        if(orderBy == o_data-1)
            strcat(curr.stringhe[orderBy], elencoTratte[i].oraPartenza);

        j = i - 1;
        while (j >= l && strcmp(curr.stringhe[orderBy], elencoTratte[j].stringhe[orderBy]) < 0){
            elencoTratte[j + 1] = elencoTratte[j];
            j--;
        }
        elencoTratte[j + 1] = curr;
    }
}

void stampaTratte(s_tratta *elencoTratte, int dim){
    for(int i=0; i< dim; i++){
        printf("%s %s %s %s %s %s %d\n", elencoTratte[i].codice, elencoTratte[i].partenza,
                elencoTratte[i].destinazione, elencoTratte[i].data, elencoTratte[i].oraPartenza,
                elencoTratte[i].oraArrivo, elencoTratte[i].ritardo);
    }
}




