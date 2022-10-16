#include <stdio.h>

int gcd(int a, int b);

int main() {
    int a, b;

    printf("Inserire i due numeri su cui si vuole calcolare il massimo comun divisore:\n");
    scanf("%d %d", &a, &b);

    printf("massimo comun divisore: %d",gcd(a,b));
    return 0;
}

int gcd(int a, int b){

    if(a<b){
        int temp = a;
        a = b;
        b = temp;
    }

    if(b==0)
        return a;


    if(a%2==0 && b%2==0)
        return 2*gcd(a/2,b/2);

    else if(a%2 != 0 && b%2==0 )
        return gcd(a,b/2);

    else if (a%2 != 0 && b%2!=0 )
        return gcd((a-b)/2, b);

    else if (a%2 == 0 && b%2!=0 )
        return gcd(a/2, b);
}