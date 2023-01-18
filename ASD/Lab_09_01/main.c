#include <stdio.h>
#include "Graph.h"

void menu();
Edge *trovaBsol(int nArchiRmv, int k, Edge **elencoArchiRmv);

int main() {
    menu();
    return 0;
}

void menu(){
    int continua =1, scelta, back, nArchiRmv=0,*cur_sol, countArchi, found =0,k, source;
    FILE *fp;
    Graph G;
    Edge *elencoArchi,**sol,*b_sol;


    if((fp = fopen("../grafo5.txt","r"))==NULL){
        printf("Error opening file...");
        return;
    }

    G = GRAPHLoad(fp, &elencoArchi, &countArchi);
    GRAPHPrint(G);
    cur_sol = malloc(countArchi*sizeof (int));
    sol = (Edge **) malloc(countArchi*sizeof (Edge*));

    for(int i=0; i<countArchi;i++){
        sol[i] = malloc(countArchi*sizeof (Edge));
    }

    while (continua){
        printf("-------MENU------\n\n"
               "0- Termina programma\n"
               "1- Individuazione di tutti gli insiemi di archi di cardinalita' minima la cui rimozione renda il grafo un DAG\n"
               "2- Costruzione di un DAG rimuovendo, tra tutti gli insiemi di archi generati al passo precedente, quelli dell'insieme a peso massimo.\n"
               "3- Calcolo delle distanze massime da ogni nodo sorgente verso ogni nodo del DAG costruito\n\n");
        printf("Scegli:");
        scanf("%d",&scelta);

        switch (scelta) {
            case 0:
                printf("Fine programma.");
                continua =0;
                GRAPHfree(G);
                break;
            case 1:
                back = GRAPHextendedDfs(G,0);
                if(back!=0){
                    printf("%d Archi back, il grafo non e' un DAG\n\n",back);

                    for(k=1; k<countArchi && !found;k++){
                        comb_semplici(G, elencoArchi,cur_sol ,sol, &found,countArchi,0,0,k, &nArchiRmv);
                    }
                } else{
                    printf("Il grafo e' gia' un DAG\n\n");
                    break;
                }
//                GRAPHPrint(G);
                break;
            case 2:
                if(nArchiRmv>0) {
                    b_sol = trovaBsol(nArchiRmv, (k - 1), sol);
                    printf("Soluzione migliore con rimozione degli archi:\n\n");
                    for (int i = 0; i < (k - 1); i++) {
                        EDGEPrint(b_sol[i], G);
                        GRAPHRemoveE(G, b_sol[i]);
                    }
                    printf("\n");
                } else{
                    printf("Errore, nessun arco da rimuovere.\n\n");
                }
                break;
            case 3:
                source = DAGrts(G);
                DAGGetLongestPath(G, source);
        }
    }
}

Edge *trovaBsol(int nArchiRmv, int k, Edge **elencoArchiRmv){
    int max=INT_MIN,curMax, indexCurMax;
    for(int i=0; i<nArchiRmv;i++){
        if((curMax = GRAPHGetTotWeight(elencoArchiRmv[i],k))>max) {
            max = curMax;
            indexCurMax = i;
        }
    }
    return elencoArchiRmv[indexCurMax];
}

