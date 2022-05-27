#include <stdio.h>

#define pathFileIn "../numeri.txt"
/*
E’ data una sequenza di numeri interi, contenuta in un file testo (numeri.txt, definito con #define), nel
quale gli interi sono separati da spazio o a-capo. Occorre verificare che l’i-esimo numero xi (con i ≥2)
sia, rispetto ai due numeri precedenti (xi-1 e xi-2), pari alla loro somma (xi-2 + xi-1), differenza (xi-2 - xi-1),
prodotto (xi-2 * xi-1) o quoziente (xi-2 / xi-1) (attenzione a evitare le divisioni per 0!). Se un dato non è
corretto, va scartato e si passa a verificare il successivo (ignorando il dato scartato). Occorre inoltre
individuare il massimo e il minimo tra i dati della sequenza (ignorando i dati eventualmente scartati).
Al termine stampare a video:
1. il risultato della verifica, cioè se tutti i dati rispettano la regola o se qualcuno (indicare quanti) sia
stato scartato
2. I valori massimo e minimo tra i numeri in sequenza, escludendo quelli eventualmente scartati.
 */

int readFile(FILE *fin);
int findMax(int max,int x0,int x1,int x2);
int findMin(int min,int x0,int x1,int x2);

int main() {

    FILE *fin;

    if ((fin = fopen(pathFileIn, "r")) == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    readFile(fin);

}

int readFile(FILE *fin){
    int x0 =0, x1 =0,x2 =0, max =0, min =0, op=0, count =0;

    while(!feof(fin)){
        if(op == 0){
            fscanf(fin," %d%d", &x0, &x1);
        }
        fscanf(fin, "%d", &x2);

        max = findMax(max, x0,x1,x2);
        min = findMin(min,x0,x1,x2);

        if((x0 /x1 != x2)&&(x0+x1 != x2)&&(x0*x1 != x2)&&(x0-x1 != x2)){
            count++;
            op = 1;
            }else {
            op = 0;
        }
    }
    printf("Numero massimo: %d\nNumero minimo: %d\nNumeri scartati: %d",max,min,count);

}

int findMax(int max,int x0,int x1,int x2){
    if(max <x0)
        max = x0;
    else if (max <x1)
        max = x1;
    else if (max< x2)
        max = x2;
    return max;
}
int findMin(int min,int x0,int x1,int x2){
    if(min >x0)
        min = x0;
    else if (min >x1)
        min = x1;
    else if (min> x2)
        min = x2;
    return min;
}