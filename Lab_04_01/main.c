#include <stdio.h>

#define MAX 30
typedef  struct sottoVettore{
    int i0, i, length;
}sottoVettore;

void sottoSequenze(int v[], int n);

int main() {
   int v[MAX], n,count;

    do {
        printf("Inserire la dimensione del vettore (<=30):");
        scanf("%d", &n);
    } while (n>30);

    while(count<n){
        printf("Inserire il %d valore intero",count+1);
        scanf("%d",&v[count]);
        count++;
    }
    sottoSequenze(v,n);
}

void sottoSequenze(int v[], int n){
    int max, l, i0 = -1, count =0;
    struct sottoVettore sottoVettori[10];

    for(int i  = 0; i < n; i++) {
        if(v[i] == 0){
            l = (i-i0)-1;
            sottoVettori[count].i = i-1;
            sottoVettori[count].i0 = i0+1;
            sottoVettori[count].length = l;
            count++;
            if(l> max)
                max = l;
            i0 = i;
        }
    }

    printf("Sottovettori: \n",max, count);
    for(int i =0; i< count;i++){
        if(sottoVettori[i].length == max){
            printf("[");
            for(int j = sottoVettori[i].i0; j<=sottoVettori[i].i;j++) {
                printf(" %d ",v[j]);
            }
            printf("] ");
        }
    }

}
