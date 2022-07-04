#include <stdio.h>
#include <string.h>

void compressString(char *testo );
int main() {
    char string[50] = "aaaBBBBbbbbbAAAcbcba";
    compressString(string);
    return 0;
}

void compressString(char *testo){


    for (int i=0; i< strlen(testo); i++){
        int count =1; // modifica: dichiarazione di variabile all'interno del cicloe inizializzata col valore 1
        char charCorr = testo[i];

        if(charCorr== testo[i+1]){
            while (charCorr == testo[i+count]) { //modifica: da testo [i+1] a testo[i+count]
                count++;
            }
            printf("%c%d",charCorr,count);
        } else
            printf("%c",charCorr);

        i+=(count-1); // modifica: da i+= count a i+= count-1
    }
}
