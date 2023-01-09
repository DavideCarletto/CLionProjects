#include <stdio.h>
#include "Graph.h"
#include "stdlib.h"

void menu();
int main(int argc, char **argv) {

    FILE *fp;
    Graph grafo;

    if((fp = fopen(argv[1], "r")) == NULL){
        printf("Error opening file %s", argv[1]);
        return 1;
    }

    grafo = GRAPHload(fp);
    menu(grafo);
}

void menu(Graph G){
    int scelta, continua=1;

    while (continua) {
        printf("----------MENU------\n\n");
        printf("1- Elenco vertici e archi in ordine alfabetico\n"
               "2- Verifica se 3 vertici formano un sottografo completo\n"
               "3- Genera lista di adiacenza\n"
               "4- Esci\n\n"
               "Scelta:");
        scanf("%d", &scelta);

        switch (scelta) {
            case 1:
                GRAPHprint(G);
                break;
            case 2:
                if(GRAPHCheckSottografoMat(G)==1)
                    printf("I vertici sono adiacenti\n");
                else
                    printf("I vertici non sono adiacenti\n");
                break;
            case 3:
                GRAPHGeneraList(G);
                break;
            case 4:
                printf("Fine programma.");
                continua = 0;
        }
    }
}