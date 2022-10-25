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
    char stringhe[4][MAX_S]; //questa struttura aiuta a decifrare il criterio di ordinamento.
} s_tratta;

typedef enum {
    stampa, o_data, o_codice, o_partenza, o_arrivo, r_partenza, r_fine, r_err
}comando;

int leggiFile(FILE *fin, s_tratta *elencoTratte);
void menuTratte(s_tratta *elencoTratte, int dim);
int leggiComando();
void stampaTratte(s_tratta *elencoTratte, int dim);
void ordina(s_tratta elencoTratte[], int dim, int orderBy);
int ricercaBinaria(s_tratta *elencoTratte, s_tratta *tratteTrovate,int l, int r, char* partenza);
int ricercaLineare(s_tratta *elencoTratte, s_tratta *tratteTrovate, int dim, char* partenza);


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
    int continua = 1, comando =0, orderBy = 0,n = 0, ricerca =0;
    s_tratta *c_elencoTratte = malloc(dim*sizeof (*elencoTratte)), *tratteTrovate = malloc(dim*sizeof (*elencoTratte));
    char *partenza = (char*)malloc(sizeof(char) * (MAX_S   + 1));

    while(continua){
        printf("CMD 'stampa': stampa le tratte\n"
               "CMD 'o_data': ordina le tratte per data\n"
               "CMD 'o_codice': ordina le tratte per codice\n"
               "CMD 'o_partenza': ordina le tratte per stazione di partenza\n"
               "CMD 'o_arrivo': ordina le tratte per stazione di arrivo\n"
               "CMD 'r_partenza': ricerca di una tratta per stazione di partenza\n"
               "CMD 'fine: per terminare\n\n");

        comando = leggiComando();
        orderBy = comando-1;

        switch (comando) {
            case stampa:
                stampaTratte(elencoTratte,dim);
                break;
            case o_data: case o_codice: case o_partenza: case o_arrivo:
                ordina(elencoTratte,dim, orderBy);
                stampaTratte(elencoTratte,dim);
                break;

            case r_partenza:
                memcpy(c_elencoTratte, elencoTratte, dim * sizeof(*elencoTratte));
                ordina(c_elencoTratte,dim, o_partenza-1);

                printf("Inserire la fermata di partenza da cercare:");
                scanf("%s",partenza);
                printf("Si vuole ordinare secondo ricerca lineare(0) o binaria(1)?");
                scanf("%d",&ricerca);

                if(ricerca == 0)
                    n= ricercaLineare(c_elencoTratte,tratteTrovate,dim,partenza);
                else if(ricerca == 1)
                    n = ricercaBinaria(c_elencoTratte,tratteTrovate,0, dim, partenza);
                else
                    printf("Comando non valido");

                if(n == 0)
                    printf("Non sono state trovate tratte la cui stazione di partenza corrisponde alla stazione: %s\n", partenza);
                else {
                    printf("Trovate %d tratte la cui stazione di partenza e' %s\n", n,partenza);
                    stampaTratte(tratteTrovate, n);
                }
                break;
            case r_fine:
                printf("Finito");
                continua = 0;
                break;
            case r_err:
                printf("Errore comando");
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

void ordina(s_tratta elencoTratte[], int dim, int orderBy) { //Per stabilità Utilizzato l'insertion sort
    int i, j, l=0, r=dim-1;
    s_tratta curr;

    for (i = l+1; i <= r; i++) {
        curr = elencoTratte[i];

        for(int k = 0; k<4; k++){
            strcpy(curr.stringhe[k],elencoTratte[i].stringhe[k]); //copio il contenuto delle stringhe di cui è possibile fare l'ordinamento in curr.
        }

        if(orderBy == o_data-1)
            strcat(curr.stringhe[orderBy], elencoTratte[i].oraPartenza); //nel caso di ordinamento per data, concateno la data all'ora della partenza. In questo modo nel caso ci siano due date uguali si ordina per ora.

        j = i - 1;
        while (j >= l && strcmp(curr.stringhe[orderBy], elencoTratte[j].stringhe[orderBy]) < 0){ //utilizzo la variabile della struct contenente le stringhe su cui è possibile fare l'ordinamento. Per capire il criterio utilizzato, basta usare orderBy.
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
    printf("\n");
}

int ricercaBinaria(s_tratta *elencoTratte, s_tratta *tratteTrovate, int l, int r, char* partenza){
    int count = 0;

    while (l <= r) {
        int m = l + (r - l) / 2;

        if (strcmp(elencoTratte[m].partenza, partenza)== 0)
            tratteTrovate[count++] = elencoTratte[m];

        if (strcmp(elencoTratte[m].partenza, partenza) < 0)
            l = m + 1;

        else
            r = m - 1;
    }
    return count;
}

int ricercaLineare(s_tratta *elencoTratte, s_tratta *tratteTrovate, int dim, char* partenza){
    int count =0;

    for(int i=0; i<dim; i++){
        if (strcmp(elencoTratte[i].partenza, partenza)== 0)
            tratteTrovate[count++] = elencoTratte[i];
    }
    return count;
}