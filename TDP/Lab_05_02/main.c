#include <stdio.h>
#include <string.h>

#define  MAX 200

typedef struct dizionario {
    char codifica[MAX];
    char originale[MAX]
} dizionario;

void leggiDiz(FILE *fin, struct dizionario dizionario[MAX], int dim);

void leggiFile(FILE *fin_s, FILE *fout, struct dizionario dizionario[MAX], int dim);

int getIndiceSubstring(char str[], char s[]);

void sostituisci(char parola[], int index, char codifica[], int lenSub,FILE *fout);

int main() {
    FILE *fin, *fin_s, *fout;
    struct dizionario dizionario[MAX];
    int dim;

    if ((fin = fopen("../dizionario.txt", "r")) == NULL) {
        printf("Error opening file: dizionario.txt");
        return 1;
    }
    if ((fin_s = fopen("../sorgente.txt", "r")) == NULL) {
        printf("Error opening file: sorgente.txt");
        return 2;
    }
    if ((fout = fopen("../ricodificato.txt", "w")) == NULL) {
        printf("Error opening file ricodificato.txt");
        return -1;
    }
    fscanf(fin, "%d", &dim);
    leggiDiz(fin, dizionario, dim);

    leggiFile(fin_s, fout, dizionario, dim);

    fclose(fin);
    fclose(fin_s);
    fclose(fout);

    return 0;
}


void leggiDiz(FILE *fin, struct dizionario dizionario[MAX], int dim) {
    for (int i = 0; i < dim; i++) {
        fscanf(fin, "%s %s", &dizionario[i].codifica, &dizionario[i].originale);
    }
}

void leggiFile(FILE *fin_s, FILE *fout, struct dizionario dizionario[MAX], int dim) {
    while (!feof(fin_s)) {
        char line[MAX];
        int count = 0;
        fgets(line, sizeof line, fin_s);
        if (!feof(fin_s)) {
            for (int i = 0; i < strlen(line); i++) {
                char parola[MAX];
                while(line[i]!= ' ' && line[i]!='\n'){
                    parola[count] = line[i];
                    count++;
                    i++;
                }
                int indice;
                for (int j = 0; j < dim; j++) {
                    if ((indice = (getIndiceSubstring(parola, dizionario[j].originale))) != -1) {
                         sostituisci(parola,indice, dizionario[j].codifica, strlen(dizionario[j].originale),fout);
                         break;
                    }
                }
                fprintf(fout,"%s", parola);
                if(line[i]!= '\n'){
                    fputc(' ',fout);
                }
                count =0;
                memset(parola,0,MAX);
            }
            fputc('\n',fout);
        }
    }
}


int getIndiceSubstring(char str[], char s[]) {
    int i, j, k, len;

    len = strlen(s);

    for (i = 0; str[i + len - 1]; i++) {
        k = i;
        for (j = 0; j < len; j++) {
            if (str[k] != s[j])
                break;
            k++;
        }
        if (j == len)
            return i;
    }
    return -1;
}

void sostituisci(char parola[], int index, char codifica[], int lenSub,FILE *fout){
    char strCodificata[MAX];
    int count =0;
    for(int i=0; i< MAX; i++){
        if(i<index || i >=(index+lenSub-1)) {
            strCodificata[count] = parola[i];
            count++;
        }
        else{
            for(int j =0; j<strlen(codifica);j++){
                strCodificata[count] = codifica[j];
                count++;
            }
            i+= lenSub-1;
        }
    }
    strcpy(parola, strCodificata);
    fprintf(fout,"%s", strCodificata);
    memset(strCodificata,0,MAX);
    memset(parola,0,MAX);
}