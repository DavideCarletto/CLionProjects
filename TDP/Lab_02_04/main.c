#include <stdio.h>
#include <string.h>
#include <ctype.h>

int codifica(FILE *fin, FILE *fout);

int decodifica(FILE *fin, FILE *fout);

int main(void) {
    FILE *fin, *fout;
    char operazione;

    printf("Inserire l'operazione da eseguire ('C' per comprimere, 'D' per decomprimere):");
    scanf("%c", &operazione);

    if (operazione == 'C') {
        if ((fin = fopen("../sorgente.txt", "r")) == NULL) {
            printf("Error opening file\n");
            return 1;
        }
        if ((fout = fopen("../codifica.txt", "w")) == NULL) {
            printf("Error opening file\n");
            return 2;
        }
        printf("codificando il file sorgente.txt...\n");
        codifica(fin, fout);
    } else if (operazione == 'D') {
        if ((fin = fopen("../codifica.txt", "r")) == NULL) {
            printf("Error opening file\n");
            return 1;
        }
        if ((fout = fopen("../decodifica.txt", "w")) == NULL) {
            printf("Error opening file\n");
            return 2;
        }
        printf("decodificando il file codifica.txt...\n");
        decodifica(fin, fout);
    }
    return 0;
}
//#region codifica
int codifica(FILE *fin, FILE *fout) {

    int numCount = 0;
    char startChar = 'a', rifChar = 'a';

    while (!feof(fin)) {
        char line[100];
        fgets(line, 100, fin);
        if (!feof(fin)) {
            for (int i = 0; i < strlen(line); i++) {

                if (isdigit(line[i])) {
                    int num = line[i] - '0';
                    if (numCount == 10) {
                        numCount = 0;
                    }
                    num += numCount;
                    fputc(num + '0', fout);
                    numCount++;
                } else if (isalpha((line[i]))) {
                    if (isalpha(line[i - 1])) {
                        char c0 = line[i], charFin;
                        int numSpost = c0 - startChar;
                        if ((int) rifChar + numSpost > (int) 'z') {
                            numSpost = numSpost - ((int) 'z' - (int) rifChar)-1;
                            rifChar = 'a';
                        }
                        charFin = (int) rifChar + numSpost;
                        fputc(charFin, fout);
                        rifChar = charFin;
                    } else {
                        fputc(line[i], fout);
                        rifChar = tolower(line[i]);
                    }
                } else{
                    fputc(line[i], fout);

                }
            }
        }
    }
    return 0;
}
//#endregion

//#region decodifica
int decodifica(FILE *fin, FILE *fout) {


    return 0;

}
//#endregion