#include <stdio.h>
#include "Item.h"
#include <string.h>

#define MAX_NF 100

typedef  enum {inserisci_t, inserisci_f,ricerca_c,cancella_c,cancella_d, stampa, fine, err} comando;

void leggiFile(FILE *fp, link *head);
void menu(link *head);
int leggiComando(char *cmd);


int main() {
    FILE *fp = NULL;
    link head = NULL,x;

    if((fp = fopen("../E2/anag1.txt","r"))==NULL){
        printf("Error opening file...");
        return 1;
    }

    leggiFile(fp, &head);
    menu(&head);
    return 0;
}

void leggiFile(FILE *fp, link* head){
    Item val;

    while(!feof(fp)){
            fscanf(fp, "%s %s %s %s %s %s %d\n", &val.codice[0], &val.nome[0], &val.cognome[0], &val.dataNascita[0],
                   &val.via[0], &val.citta[0], &val.cap);
            formatDate(&val);
            (*head) = SortListIns(*head, val);
    }

}

void menu(link *head){
    char comando[MAX_S], fileName[MAX_NF] = "../E2/anag2.txt", codice[MAX_S];
    int cmd=0;
    Item val;
    FILE *fp = NULL;
    link founded = NULL;


    while(cmd!= fine) {
        printf("CMD inserisci_t: acquisizione e inserimento ordinato di un nuovo elemento in lista (da tastiera)\n"
               "CMD inserisci_f: acquisizione e inserimento ordinato di un nuovo elemento in lista (da file)\n"
               "CMD ricerca_c: ricerca, per codice, di un elemento\n"
               "CMD cancella_c: cancellazione di un elemento dalla lista per codice\n"
               "CMD cancella_d: cancellazione di tutti gli elementi con date comprese tra 2 date\n"
               "CMD stampa: stampa della lista su file\n"
               "CMD fine: per terminare\n");

        printf("Inserire comando:");
        scanf("%s", comando);

        cmd = leggiComando(comando);

        switch (cmd){
            case inserisci_t:
                printf("Inserire l'elemento nel formato: <codice> <nome> <cognome> <data_di_nascita> <via> <citta'> <cap>:\n");
                scanf("%s %s %s %s %s %s %d", &val.codice, &val.nome, &val.cognome, &val.dataNascita, &val.via, &val.citta, &val.cap);
                formatDate(&val);
                (*head) = SortListIns(*head, val);
                printList(*head);
                break;

            case inserisci_f:
                printf("Inserire il nome del file: ");
                scanf( "%s",fileName);

                if((fp = fopen(fileName, "r"))== NULL) {
                    printf("Error opening file...");
                    break;
                }

                leggiFile(fp, head);
                printList(*head);
                break;
            case ricerca_c:
                printf("Inserire il codice da ricercare:");
                scanf("%s",codice);

                founded = listSearch(*head, codice);

                if(founded!= NULL) {
                    printf("\nTrovato elemento corrispondente:\n");
                    printItem(founded);
                }
                else
                    printf("\nNessuna corrispondenza trovata.\n\n");
                break;
            case cancella_c:
                break;
            case cancella_d:
                break;
            case stampa:
                printList(*head);
                break;
            case fine:
                printf("Programma terminato.");
                break;
            case err:
                printf("Errore comando...\n");
                break;
        }
    }
}

int leggiComando(char *comando){

    char tab[8][MAX_S] = {"inserisci_t", "inserisci_f","ricerca_c","cancella_c","cancella_d", "stampa", "fine", "err"};
    int c =0;

    while(c <err && strcmp(comando, tab[c])!=0)
        c++;

    return c;
}
