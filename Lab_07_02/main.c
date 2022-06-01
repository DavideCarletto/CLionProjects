#include <stdio.h>

#define MAX 100

void leggiFile(FILE *fin);
void stampaVettore(int v[MAX], int n);
void copiaVettore(int v[MAX], int v_copia[MAX], int n);

void insertionSort(int v[MAX], int n);
void selectionSort(int v[MAX], int n);
void shellSort(int v[MAX], int n);

    int main() {
    FILE *fin, *fin2;

    if((fin = fopen("../sort.txt","r"))==NULL){
        printf("Error opening file");
        return 1;
    }

    if((fin2 = fopen("../sort1.txt","r"))==NULL){
        printf("Error opening file");
        return 2;
    }

    leggiFile(fin2);

    return 0;
}

void leggiFile(FILE *fin){
    int dim,n;
    int v[MAX],v_copia[MAX];

    fscanf(fin, "%d",&dim);

    while(!feof(fin)){
        fscanf(fin,"%d",&n);
        for(int i=0; i<n; i++){
            fscanf(fin, "%d",&v[i]);
        }
        copiaVettore(v,v_copia, n);
        stampaVettore(v, n);

        insertionSort(v_copia,n);
        printf("Vettore orinato con insertion sort:");
        stampaVettore(v_copia, n);

        copiaVettore(v,v_copia, n);
        selectionSort(v_copia,n);
        printf("Vettore orinato con selection sort:");
        stampaVettore(v_copia, n);

        copiaVettore(v,v_copia, n);
        shellSort(v_copia,n);
        printf("Vettore orinato con shell sort:");
        stampaVettore(v_copia, n);
        printf("\n");
    }

}

void stampaVettore(int v[MAX], int n){
    for(int i=0; i< n;i++){
        printf(" %d ",v[i]);
    }
    printf("\n");
}

void copiaVettore(int v[MAX], int v_copia[MAX], int n){
    for(int i=0; i< n; i++){
        v_copia[i]= v[i];
    }
}
void insertionSort(int A[], int N) {
    int i, j, l=0, r=N-1, x,itEsterno=0, itInterno=0, itTot=0, scambi=0;
    printf("\n----- INSERTION SORT -----\n");
    for (i = l+1; i <= r; i++) {
        x = A[i];
        j = i - 1;
        itEsterno++;
        while (j >= l && x < A[j]){
            A[j+1] = A[j];
            j--;
            scambi++;
            itInterno++;
        }
        itTot+=itInterno;
        printf("Iterazione %d numero di iterazioni: %d\n", i,itInterno);
        itInterno=0;
        itEsterno++;
        A[j+1] = x;
    }
    itTot+= itEsterno;
    printf("Numero totale di scambi: %d\n",scambi);
    printf("Numero totale di iterazioni del ciclo esterno: %d\n",itEsterno);
    printf("Numero totale di iterazioni: %d\n",itTot);
    printf("--------------------------\n\n");
}

void selectionSort(int A[], int N) {
    int i, j, l=0, r=N-1, min,itEsterno=0, itInterno=0, itTot=0, scambi=0;
    int temp;
    printf("\n----- SELECTION SORT -----\n");
    for (i = l; i < r; i++) {
        min = i;
        for (j = i+1; j <= r; j++) {
            if (A[j] < A[min])
                min = j;
            itInterno++;
        }
        if (min != i) {
            temp = A[i];
            A[i] = A[min];
            A[min] = temp;
            scambi++;
        }
        printf("Iterazione %d numero di iterazioni: %d\n", i,itInterno);
        itTot+=itInterno;
        itInterno=0;
        itEsterno++;
    }
    itTot+=itEsterno;
    printf("Numero totale di scambi: %d\n",scambi);
    printf("Numero totale di iterazioni del ciclo esterno: %d\n",itEsterno);
    printf("Numero totale di iterazioni: %d\n",itTot);
    printf("---------------------------\n\n");
    return;

    }


void shellSort(int A[], int N) {
    int i, j, x, l=0, r=N-1, h=1,itEsterno, itInterno, itTot, scambi;
    while (h < N/3)
        h = 3*h+1;
    while(h >= 1) {
        for (i = l + h; i <= r; i++) {
            j = i;
            x = A[i];
            while(j >= l + h && x < A[j-h]) {
                A[j] = A[j-h];
                j -=h;
            }
            A[j] = x;
        }
        h = h/3;
    }
}