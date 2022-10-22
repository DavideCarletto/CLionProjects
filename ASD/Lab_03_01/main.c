#include <stdio.h>

#define MAX 100
int majority( int *a, int N);
int countMajority(int *a, int N, int majority);

int main() {
    int a[MAX] = {  3, 3, 9, 4, 3, 5, 3};

    printf("%d",majority(a, 7));
    return 0;

}

int majority(int *a, int N){
    int mid, majorityLeft, majorityRight;
    if( N == 1 )
        return a[0] ;

     mid = N/2 ;
     majorityLeft = majority( a, mid ) ;
     majorityRight = majority(a+mid, N-mid ) ;

    if( majorityLeft == majorityRight )
        return majorityLeft ;
    if(countMajority(a,N,majorityLeft)>N/2)
        return majorityLeft;
    if(countMajority(a,N,majorityRight)>N/2)
        return majorityRight;

    return -1 ;
}

int countMajority(int *a,int N, int majority){
    int count=0;
    for(int i =0; i<N;i++){
        if(a[i]==majority)
            count++;
    }
    return count;
}
