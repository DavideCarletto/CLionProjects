#include <stdio.h>
#include <string.h>

int printReservation(FILE *fp);
int dayToNumber(char * name);
char * numberToDay(int number);

struct giorniSettimana{
    int prenotazioni, clienti;
    float media;
};
int main() {
    FILE *fp;

    if ((fp = fopen("../ristorante.txt","r"))==NULL){
        printf("Error");
        return -1;
    }

    int res = printReservation(fp);

    printf("%d",res);
    return 0;
}

int printReservation(FILE *fp) {
    struct giorniSettimana elencoGiorni[7]; //modifica: da struct giorniSettimana [7]

    int max=0; // modifica: prima era dentro al while;

    for(int i=0; i< 7; i++){ //modifica: non avevo ancora inizializzato
        elencoGiorni[i].clienti=0;
        elencoGiorni[i].prenotazioni=0;
        elencoGiorni[i].media=0;
    }

    while (!feof(fp)) {// modifica: da fp!=EOF
        char giorno[50];
        int prenotazioni = 0;

        fscanf(fp, "%s %d", giorno, &prenotazioni); //modifica: da giorno,prenotazioni

        elencoGiorni[dayToNumber(giorno)].clienti += prenotazioni;
        elencoGiorni[dayToNumber(giorno)].prenotazioni++;
    }
        for (int i = 0; i < 7; i++) {
            if(elencoGiorni[i].prenotazioni>0)
                elencoGiorni[i].media = (float)elencoGiorni[i].clienti/(float)elencoGiorni[i].prenotazioni;

            printf("%s:%d prenotazioni,%.2f clienti in media per tavolo\n", numberToDay(i), elencoGiorni[i].prenotazioni,elencoGiorni[i].media);
            if (elencoGiorni[i].clienti > max)
                max = elencoGiorni[i].clienti; //modifica; da max = elencoGiorni[i]
        }

    return max;
}

int dayToNumber(char * name) {
    if (!strcmp(name, "Lunedi"))
        return 0;
    if (!strcmp(name, "Martedi"))
        return 1;
    if (!strcmp(name, "Mercoledi"))
        return 2;
    if (!strcmp(name, "Giovedi"))
        return 3;
    if (!strcmp(name, "Venerdi"))
        return 4;
    if (!strcmp(name, "Sabato"))
        return 5;
    if (!strcmp(name, "Domenica"))
        return 6;
    else
        return -1;
}

char * numberToDay(int number) {
    switch (number) {
        case 0:
            return "Lunedi";
        case 1:
            return "Martedi";
        case 2:
            return "Mercoledi";
        case 3:
            return "Giovedi";
        case 4:
            return "Venerdi";
        case 5:
            return "Sabato";
        case 6:
            return "Domenica";
        default:
            return NULL;
    }
}