#include <stdio.h>

void menu();

int main() {
    menu();
    return 0;
}

void menu(){
    int scelta, continua =1;

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
                break;
            case 2:
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