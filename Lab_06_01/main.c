#include <stdio.h>
#include <string.h>
#include <ctype.h>

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
} s_tratta;

typedef enum {
    r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_fine, r_err
} comando_e;

int leggiFile(FILE *fin, s_tratta elencoTratte[MAX_T]);
int leggiComando(void);
void menuParola(s_tratta tratte[], int dim);
void strToLower(char str[]);
void stampaTratta(s_tratta tratta);
void elencoDate(s_tratta elencoTratte[], int dim, char dataI[], char dataF[]);
void elencoFermate (s_tratta elencoTratte[],int dim, char fermata[]);
void elencoDestinazione(s_tratta elencoTratte[],int dim, char destinazione[]);
void elencoRitardo(s_tratta elencoTratte[], int dim, char dataI[], char dataF[]);

int ritardoTotale(s_tratta elencoTratte[], int dim, char codice[]);
int main() {

    FILE *fin;
    s_tratta elencoTratte[MAX_T];
    int dim;

    if ((fin = fopen("../log.txt", "r")) == NULL) {
        printf("Error opening file log.txt");
        return -1;
    }

    dim = leggiFile(fin, elencoTratte);

    menuParola(elencoTratte, dim);

    return 0;
}

int leggiFile(FILE *fin, s_tratta elencoTratte[MAX_T]) {
    int dim;

    while (!feof(fin)) {
        fscanf(fin, "%d", &dim);
        if (!feof(fin)) {
            for (int i = 0; i < dim; i++) {
                fscanf(fin, "%s %s %s %s %s %s %d", &elencoTratte[i].codice, &elencoTratte[i].partenza,
                       &elencoTratte[i].destinazione, &elencoTratte[i].data, &elencoTratte[i].oraPartenza,
                       &elencoTratte[i].oraArrivo, &elencoTratte[i].ritardo);
            }
        }
    }
    return dim;
}

void menuParola(s_tratta elencoTratte[MAX_T], int dim) {
    int end = 0, comando;
    char dataI[MAX_S], dataF[MAX_S], partenza[MAX_S], capolinea[MAX_S], codice[MAX_S];
    while (!end) {
        printf("CMD 'date': elenco di tutte le corse partite in un certo intervallo di date\n"
               "CMD 'partenza': elenco di tutte le corse partite da una certa fermata\n"
               "CMD 'capolinea': elenco di tutte le corse aventi una data destinazione\n"
               "CMD 'ritardo': elenco di tutte le corse che hanno raggiunto la destinazione in ritardo, in un certo intervallo di date\n"
               "CMD 'ritardo_tot': elenco del ritardo complessivo accumulato dalle corse identificate da un certo codice di tratta\n"
               "CMD 'fine: per terminare\n\n");

        comando = leggiComando();

        switch (comando) {
            case r_date:
                printf("Inserisci un intervallo di date (yyyy/MM/dd):");
                scanf("%s %s", dataI, dataF);
                elencoDate(elencoTratte, dim, dataI, dataF);
                break;
            case r_partenza:
                printf("Inserisci la fermata di partenza:");
                scanf("%s",partenza);
                elencoFermate(elencoTratte, dim, partenza);
                break;
            case r_capolinea:
                printf("Inserisci la fermata capolinea:");
                scanf("%s",capolinea);
                elencoDestinazione(elencoTratte,dim,capolinea);
                break;
            case r_ritardo:
                printf("Inserisci un intervallo di date (yyyy/MM/dd):");
                scanf("%s %s", dataI, dataF);
                elencoRitardo(elencoTratte,dim,dataI,dataF);
                break;
            case r_ritardo_tot:
                printf("Inserisci il codice della tratta:");
                scanf("%s", codice);
                printf("Il ritardo accumulato e' di %d minuti\n\n", ritardoTotale(elencoTratte,dim,codice));
                break;
            case r_fine:
                printf("fine\n\n");
                end = 1;
                break;
            default:
                printf("\nErrore comando\n\n");
        }
    }

}

int leggiComando() {

    char comando[MAX_S];
    char tabella[6][MAX_S] = {"date", "partenza", "capolinea", "ritardo", "ritardo_tot", "fine"};

    printf("Inserire comando:");
    scanf("%s", comando);
    strToLower(comando);

    int c = r_date;
    while (c < r_err && strcmp(comando, tabella[c]) != 0)
        c++;

    return c;
}

void strToLower(char s[]) {
    int i, l = strlen(s);
    for (i = 0; i < l; i++)
        s[i] = tolower(s[i]);
}

void elencoDate(s_tratta elencoTratte[], int dim, char dataI[], char dataF[]) {
    printf("\n");
    for (int i = 0; i < dim; i++) {
        if (strcmp(elencoTratte[i].data, dataI) >= 0 && strcmp(elencoTratte[i].data, dataF) <= 0) {
            stampaTratta(elencoTratte[i]);
        }
    }
    printf("\n");
}

void elencoFermate (s_tratta elencoTratte[],int dim, char fermata[]){
    printf("\n");
    for(int i=0; i< dim;i++){
        if(strcmp(elencoTratte[i].partenza, fermata)==0){
            stampaTratta(elencoTratte[i]);
        }
    }
    printf("\n");
}

void elencoDestinazione(s_tratta elencoTratte[],int dim, char destinazione[]){
    printf("\n");
    for(int i=0; i< dim;i++){
        if(strcmp(elencoTratte[i].destinazione, destinazione)==0){
            stampaTratta(elencoTratte[i]);
        }
    }
    printf("\n");
}

void elencoRitardo(s_tratta elencoTratte[], int dim, char dataI[], char dataF[]){
    printf("\n");
    for (int i = 0; i < dim; i++) {
        if (strcmp(elencoTratte[i].data, dataI) >= 0 && strcmp(elencoTratte[i].data, dataF) <= 0) {
            if (elencoTratte[i].ritardo>0)
            stampaTratta(elencoTratte[i]);
        }
    }
    printf("\n");
}
int  ritardoTotale(s_tratta elencoTratte[], int dim, char codice[]){
    int somma;

    for(int i=0; i< dim; i++){
        if(strcmp(elencoTratte[i].codice, codice)==0){
            somma+=elencoTratte[i].ritardo;
        }
    }
    return somma;
}

void stampaTratta(s_tratta tratta) {
    printf("%s %s %s %s %s %s\n", tratta.codice, tratta.partenza, tratta.destinazione, tratta.data, tratta.oraPartenza,
           tratta.oraArrivo, tratta.ritardo);
}

