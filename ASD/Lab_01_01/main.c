#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *cercaRegexp(char *src, char *regexp);
int isInString(char c, char *str);
char *findSub(int init, char fin, char *str, int len);

int main() {
    char *src = "AcaRnd", *regexp = "A[^f]\\anR.d";
    cercaRegexp(src, regexp);

    //char *finalstring = findSub(0,'o',"ciaocomevasperotuttobene",10);
    //printf("%s", finalstring);

    return 0;
}

char *cercaRegexp(char *src, char *regexp){
    char corrCharRegexp, corrCharSrc, finalString[100];
    int  indexRegexp = 0, countFinalString=0;


    for (int i=0; i< strlen(src);i++){
        int indexSub = i,maxSub;
        char *sub;
        corrCharSrc = src[i];
        corrCharRegexp = regexp[indexRegexp];

        switch (corrCharRegexp) {
            case '.':
                finalString[countFinalString++] = corrCharSrc;
                break;
            case '[':
                sub = findSub(indexRegexp+1,']',regexp, strlen(regexp)-indexRegexp);

                if(sub[0]!='^'){
                    if(isInString(corrCharSrc,sub)){
                        finalString[countFinalString++] = corrCharSrc;
                        printf("%c", corrCharSrc);
                    }
                }else{
                    if(!isInString(corrCharSrc,sub)){
                        finalString[countFinalString++] = corrCharSrc;
                        printf("%c", corrCharSrc);
                    }
                }
                //printf("%s",sub);
                indexRegexp+= (strlen(sub)+1);
                break;

            case '\\':
                printf("%c", corrCharRegexp);
                break;
            default:
                if (corrCharRegexp == corrCharSrc) {
                    printf("%c", corrCharRegexp);
                }
                break;
        }
        indexRegexp++;
    }
}

int isInString(char c, char *str){
    for (int i=0; i< strlen(str);i++){
        if(c == str[i])
            return 1;
    }
    return 0;
}

char *findSub(int init, char fin,char *str, int len){
    char *finString = (char*)malloc(sizeof(char) * (len   + 1)); //alloca una parte di memoria per ospitare gli elementi del vettore
    int count = 0;

    for(int i = init; str[i]!= fin; i++){
        finString[count++] = str[i];
    }
    finString[count] = '\0';
    finString = realloc(finString,count+1); //rialloca memoria in funzione della lunghezza della stringa

    return finString;
}

