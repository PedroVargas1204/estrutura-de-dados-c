#include <stdio.h>

int main(){
    int n;

    printf("Digite um numero inteiro: ");
    scanf("%d", &n);

    if (!(n % 3 == 0 || n % 5 == 0)){
       printf("%d nao e multiplo de 3 nem de 5\n", n);
    } else {
        printf("%d e multiplo de 3 ou de 5\n", n);
    }

    return 0;
}