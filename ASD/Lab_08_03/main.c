#include <stdio.h>
#include "Titolo.h"
#include "TitoliList.h"
#include "QuotazioneBST.h"

#define MAX_C 30
void menu();

int main(int argc, char **argv) {
    FILE *fp;

    if((fp = fopen(argv[1], "r"))==NULL){
        printf("Error Opening file %s", argv[1]);
        return 1;
    }

    menu(fp);
    return 0;
}

void menu(FILE *fp){
    int scelta, continua =1;
    LIST list = LISTInit();
    quotazioneBST bst = BSTInit();
    char codice[MAX_C];
    titolo_t titoloCerca;


    while (continua){
        printf("-------MENU-------\n\n"
               "0- Fine\n"
               "1- Leggi transizioni da file\n"
               "2- Cerca un titolo azionario\n"
               "3- Ricerca della quotazione di un titolo\n"
               "4- Ricerca della quotazione minima e massima entro un intervallo di tempo di un titolo\n"
               "5- Ricerca della quotazione minima e massima lungo tutto il periodo\n"
               "6- Bilanciamento dell'albero delle quotazioni\n\n");
        printf("Scegli: ");
        scanf("%d",&scelta);

        switch (scelta) {
            case 0:
                printf("Fine programma.");
                continua = 0;
                break;
            case 1:
                LISTLeggiTitoli(list, fp);
                LISTPrint(list);
                BSTLoad(bst, list);
                break;
            case 2:
                printf("Immettere il codice del titolo da ricercare:");
                scanf("%s",codice);

                if((titoloCerca = LISTGetTitoloByCodice(list, codice))!=NULL){
                    printf("E' stato trovato un titolo corrispondente:\n");
                    TITOLOPrint(titoloCerca);
                } else{
                    printf("Non e' stato trovato un titolo corrispondente.\n");
                }
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;

        }
    }
}