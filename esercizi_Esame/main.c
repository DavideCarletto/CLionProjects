#include <stdio.h>
#include <string.h>

#define MAXR  50
#define  MAXC  50
int	isvowel(char	c);
void	countAndPrint(char	str[],	int	n);
int buildMatrix(int v[], int n, int M[MAXR][MAXC], int nr, int nc);
void stampaMatrice(int mappa[MAXR][MAXC],int nr,int nc);

int main() {
    //countAndPrint("forExample", 4);

    int nr = 3, nc = 5, N = 14;
    int V[50] = {1, 2, 17, 2, 3, 1, 8, 4, 6, 1, 7, 3, 5, 2};
    int M[MAXR][MAXC];
    buildMatrix(V,N,M,nr,nc);
    stampaMatrice(M,nr,nc);
    return 0;
}

int	isvowel(char	c)	{
    char	vowels[]	=	"aeiouAEIOU";
    int	i,	nv=strlen(vowels);
    for(i=0;i<nv;i++)
        if	(c	==	vowels[i])
            return	1;
    return	0;
}
void countAndPrint(char	str[],	int	n) {
    int i, j, len = strlen(str);
    for (i = 0; i < len - n; i++) {
        int cnt = 0;
        for (j = i; j < i + n; j++) {
            if (isvowel(str[j])) cnt++;
        }
        if (cnt == 2) {
            int count = i;
            while (count < j) {
                printf("%c", str[count]);
                count++;
            }
            printf("\n");
        }
    }
}


    int buildMatrix(int v[], int n, int M[MAXR][MAXC], int nr, int nc) {
        int c=0, r=0;

        for(int i=0; i< n; i+=2){
            int num = v[i];
            int num_rip = v[i+1];

            for(int j=0; j<num_rip && j<nc; j++,c++){
                M[r][c] = num;
            }
            if(c==nc){
                c=0;
                r++;
            }

        }
        return 0;
    }


void stampaMatrice(int mappa[MAXR][MAXC],int nr,int nc){
    for(int i=0; i<nr; i++){
        for(int j=0; j < nc; j++){
            printf("%d ",mappa[i][j]);
        }
        printf("\n");
    }
}