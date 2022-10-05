#include <stdio.h>
#include <stdbool.h>

#define filein "../input.txt"
#define fileout "../testo.txt"

enum segni_punteggiatura {
    punto = '.', virgola = ',', puntoVirgola = ';', duePunti = ':', puntoEscl = '!', puntoInt = '?', apostrofo = '\''
};

void writeOnFile(FILE *fin, FILE *fout);

int main() {
    FILE *fin, *fout;

    if ((fin = fopen(filein, "r")) == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    if ((fout = fopen(fileout, "w")) == NULL) {
        printf("Error opening file\n");
        return 2;
    }
    printf("Leggendo il file %s...\n", filein);
    writeOnFile(fin, fout);
    printf("Terminato.");
    return 0;
}
void writeOnFile(FILE *fin, FILE *fout) {
    int count = 0,numchar = 0;
    while (!feof(fin)) {
        bool var = false;
        while(count<25){
        char c0, c1;
        c0 = fgetc(fin);
        if (!feof(fin)) {
                char punteggiatura =
                        c0 == punto | c0 == virgola | c0 == puntoVirgola | c0 == duePunti | c0 == puntoEscl |
                        c0 == puntoInt | c0  == apostrofo;
                char puntmaiusc = c0 == punto | c0 == puntoEscl | c0 == puntoInt;

                if (punteggiatura) {
                    fputc(c0, fout);
                    numchar++;
                    count++;
                    c1 = fgetc(fin);
                    if (c1 != EOF) {
                        if (c1 != ' ' && c1!='\n') {
                                fputc(' ', fout);
                                numchar++;
                                count++;
                        } else if(c1 == ' ' ){
                            while(c1 == ' '){
                                fputc(' ', fout);
                                count++;
                                numchar++;
                                c1 = fgetc(fin);
                            }
                        }else if(c1 == '\n'){
                            var = true;
                            numchar++;
                            int count2 = count;
                            while(c1 == '\n'){
                                while(count2<25) {
                                    fputc(' ', fout);
                                    count++;
                                    count2 ++;
                                }
                                fprintf(fout,"| c:%d\n", numchar);
                                c1 = fgetc(fin);
                                numchar =0;
                                count2 = 0;
                            }

                        }
                        if (puntmaiusc && c1 >= 'a' && c1 <= 'z') {
                            c1 = c1 - 32;
                        }
                        fputc(c1, fout);
                        numchar++;
                        count++;
                    }else{
                        while(count<25){
                            fputc(' ', fout);
                            count++;
                        }
                    }
                } else if (c0 >= '0' && c0 <= '9') {
                    fputc('*', fout);
                    numchar++;
                    count++;
                }
                else if (c0 == '\n'){
                    numchar++;
                    while(count<25) {
                        fputc(' ', fout);
                        count++;
                    }
                }else {
                    fputc(c0, fout);
                    numchar++;
                    count++;
                }
            }
        }
        if(var== false) {
            fprintf(fout,"| c:%d\n", numchar);
            count = 0;
            numchar =0;
        }else{
            count = 1;
            numchar = 1;
        }
    }
}