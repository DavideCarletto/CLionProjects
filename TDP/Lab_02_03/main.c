#include <stdio.h>

int comprimi(FILE *fin, FILE *fout);
int decomprimi(FILE *fin, FILE *fout);

int main(void) {
    FILE *fin, *fout;
    char operazione;

    printf("Inserire l'operazione da eseguire ('C' per comprimere, 'D' per decomprimere:");
    scanf("%c", &operazione);

    if (operazione == 'C') {
        if ((fin = fopen("../sorgente.txt", "r")) == NULL) {
            printf("Error opening file\n");
            return 1;
        }
        if ((fout = fopen("../ricodificato.txt", "w")) == NULL) {
            printf("Error opening file\n");
            return 2;
        }
        printf("comprimendo il file sorgente.txt...\n");
        printf("sono stati compressi %d caratteri", comprimi(fin, fout));
    } else if (operazione == 'D') {
        if ((fin = fopen("../ricodificato.txt", "r")) == NULL) {
            printf("Error opening file\n");
            return 1;
        }
        if ((fout = fopen("../decodificato.txt", "w")) == NULL) {
            printf("Error opening file\n");
            return 2;
        }
        printf("decomprimendo il file ricodificato.txt...\n");
        printf("sono stati decompressi %d caratteri", decomprimi(fin, fout));
    }
    return 0;
}

int comprimi(FILE *fin, FILE *fout) {
    char c0,c1,c2;
    int nchar = 0,rip =0;
    fscanf(fin,"%c",&c0);
    while (!feof(fin)) {
        if(rip == 0)
            fscanf(fin, "%c%c",&c1,&c2);
        else
            fscanf(fin,"%c",&c2);

        if(!feof(fin)){
        if(c0 == c1 && c1 == c2) {
            int count = 1;
            char corrChar;
               do{
                   fscanf(fin,"%c",&corrChar);
                   count++;
               }while(corrChar == c0 && count<9);
            fprintf(fout,"%c$%d",c0,count);
            nchar+=3;
            c0 = corrChar;
            rip = 0;
        } else{
            fprintf(fout, "%c", c0);
            nchar++;
            c0 = c1;
            c1 = c2;
            rip = 1;
        }

    }
    }
    return nchar;
}

int decomprimi(FILE *fin, FILE *fout) {
    int nchar = 0;
    char c0, c1, c2;
    while (!feof(fin)) {
        fscanf(fin, "%c", &c1);
        if (!feof(fin)) {
            if (c1 == '$' && c0 != NULL) {
                fscanf(fin, "%c", &c2);
                int count = 0;

                while (count < (c2 - '0')) {
                    fprintf(fout, "%c", c0);
                    nchar++;
                    count++;
                }
            } else {
                fprintf(fout, "%c", c1);
                nchar++;
            }
            c0 = c1;
        }
    }
    return nchar;
}