#include <stdio.h>
#include "Titolo.h"
#include "TitoliList.h"
#include "QuotazioneBST.h"
#define MAX_C 30
void menu();

int main(int argc, char **argv) {
    menu();
    return 0;
}

void menu(){
    int scelta, continua =1, altezzaMax, altezzaMIn;
    float soglia, rapporto;
    LIST list = LISTInit();
    char codice[MAX_C], fileName[MAX_C];
    data_t dataCerca1, dataCerca2;
    titolo_t titoloCerca;
    quotazione_t quotazioneMin,quotazioneMax;
    FILE *fp;


    while (continua){
        dataCerca1.anno = -1;
        dataCerca2.anno = -1;

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
                printf("Inserire il nome del file da leggere: ");
                scanf("%s",fileName);

                if((fp = fopen(fileName, "r"))==NULL){
                    printf("File non trovato.");
                    break;
                }

                LISTLeggiTitoli(list, fp);
                LISTPrint(list);
                LISTCreaTitoliBST(list);
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

                printf("Immettere il codice del titolo da ricercare:");
                scanf("%s",codice);

                if((titoloCerca = LISTGetTitoloByCodice(list, codice))!=NULL){
                    printf("E' stato trovato un titolo corrispondente:\n");
                    TITOLOPrint(titoloCerca);
                } else{
                    printf("Non e' stato trovato un titolo corrispondente.\n");
                    break;
                }
                printf("Inserire la data su in cui cercare la quotazione:");
                scanf("%d/%d/%d",&dataCerca1.anno, &dataCerca1.mese,&dataCerca1.giorno);

                quotazione_t  quotazione = BSTSearch(TITOLOGetBST(titoloCerca),dataCerca1);

                if(quotazione.nTitoli!=-1)
                    QUOTAZIONEPrint(quotazione);
                else
                    printf("Non e' stata trovata alcuna quotazione alla data selezionata.\n");
                break;
            case 4:
                printf("Immettere il codice del titolo da ricercare:");
                scanf("%s",codice);

                if((titoloCerca = LISTGetTitoloByCodice(list, codice))!=NULL){
                    printf("E' stato trovato un titolo corrispondente:\n");
                    TITOLOPrint(titoloCerca);
                } else{
                    printf("Non e' stato trovato un titolo corrispondente.\n");
                    break;
                }

                printf("Inserire l'intervallo di date su in cui cercare la quotazione minima e massima:");
                scanf("%d/%d/%d %d/%d/%d",&dataCerca1.anno, &dataCerca1.mese,&dataCerca1.giorno, &dataCerca2.anno, &dataCerca2.mese,&dataCerca2.giorno);

                quotazioneMax = TITOLOCercaQuotazioneMax(titoloCerca, dataCerca1, dataCerca2);
                quotazioneMin = TITOLOCercaQuotazioneMin(titoloCerca, dataCerca1, dataCerca2);

                if(quotazioneMax.nTitoli != -1 &&  quotazioneMin.nTitoli != -1) {
                    printf("Quotazione massima Trovata. ");
                    QUOTAZIONEPrint(quotazioneMax);
                    printf("Quotazione minima Trovata. ");
                    QUOTAZIONEPrint(quotazioneMin);
                }

                else
                    printf("Impossibile trovare una quotazione massima/minima per le date selezionate.\n");
                break;
            case 5:

                printf("Immettere il codice del titolo da ricercare:");
                scanf("%s",codice);

                if((titoloCerca = LISTGetTitoloByCodice(list, codice))!=NULL){
                    printf("E' stato trovato un titolo corrispondente:\n");
                    TITOLOPrint(titoloCerca);
                } else{
                    printf("Non e' stato trovato un titolo corrispondente.\n");
                    break;
                }
                dataCerca1 = TITOLOGetDataMin(titoloCerca);
                dataCerca2 = TITOLOGetDataMax(titoloCerca);

                quotazioneMax = TITOLOCercaQuotazioneMax(titoloCerca, dataCerca1, dataCerca2);
                quotazioneMin = TITOLOCercaQuotazioneMin(titoloCerca, dataCerca1, dataCerca2);

                if(quotazioneMax.nTitoli != -1 &&  quotazioneMin.nTitoli != -1) {
                    printf("Quotazione massima Trovata. ");
                    QUOTAZIONEPrint(quotazioneMax);
                    printf("Quotazione minima Trovata. ");
                    QUOTAZIONEPrint(quotazioneMin);
                }
                else
                    printf("Impossibile trovare una quotazione massima/minima per le date selezionate.\n");
                break;
            case 6:
                if((fp = fopen("../F3.txt", "r"))==NULL){
                    printf("File non trovato.");
                    break;
                }
                LISTLeggiTitoli(list, fp);
                LISTPrint(list);
                LISTCreaTitoliBST(list);
                printf("Immettere il codice del titolo da ricercare:");
                scanf("%s",codice);

                if((titoloCerca = LISTGetTitoloByCodice(list, codice))!=NULL){
                    printf("E' stato trovato un titolo corrispondente:\n");
                    TITOLOPrint(titoloCerca);
                } else{
                    printf("Non e' stato trovato un titolo corrispondente.\n");
                    break;
                }
                printf("Inserire il valore della soglia che deve superare il rapporto tra il cammino massimo e quello minimo:");
                scanf("%f",&soglia);

                altezzaMIn = BSTAltezzaMin(TITOLOGetBST(titoloCerca));
                altezzaMax = BSTAltezzaMax(TITOLOGetBST(titoloCerca));

                rapporto = (float)altezzaMax/(float)altezzaMIn;

                if(rapporto>soglia) {
                    BSTBilancia(TITOLOGetBST(titoloCerca));
                    printf("Albero bilanciato correttamente.\n\n");
                } else{
                    printf("Il rapporto vale %f, il quale non supera la soglia selezionata.\n\n",rapporto);
                }
                break;
            default:
                fclose(fp);
        }
    }
}