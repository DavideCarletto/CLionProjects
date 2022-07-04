#include <stdio.h>
#include <string.h>

#define MAX 5
struct cliente{
    char codice[50];
    float saldo;
};
void analyseBill(FILE *fp, int *num);
int main() {
    FILE *fp;
    int num=0;
    fp = fopen("../bills.txt","r");
    if(fp == NULL){
        printf("Error");
        return -1;
    }
    analyseBill(fp, &num);
    printf("Number of customers: %d\n", num);
    return 0;
}
void analyseBill(FILE *fp, int *num){
    struct  cliente clienti[MAX]; //modifica: da struct cliente[Max]

    while(!feof(fp)){ //Modifica: da fp!= EOF
        char codice[50];
        float cifra;
        int trovato =0;

        fscanf(fp,"%s %f",codice,&cifra);
        for(int i=0; i< MAX;i++) {
            if (strcmp(clienti[i].codice, codice) == 0) {
                clienti[i].saldo += cifra;
                trovato = 1;
                //c'era un *num++ di troppo
            }
        }
            if(trovato==0){
                strcpy(clienti[*num].codice,codice); // modifica: da clienti[*num].codice = codice
                clienti[*num].saldo=cifra; // modifica: avevo messo =0
                (*num)++; // non avevo messo le parentesi e avevo usato ancora count
        }
    }
    float max=0;
    int indiceMax;

    for (int i = 0; i < *num; i++) {
        printf("Customer %s: %.2f\n",clienti[i].codice,clienti[i].saldo);
        if(clienti[i].saldo>max){
            max = clienti[i].saldo;
            indiceMax =i;
        }
    }
    printf("Customer with highest debt: %s, %.2f\n",clienti[indiceMax].codice,max);
}
