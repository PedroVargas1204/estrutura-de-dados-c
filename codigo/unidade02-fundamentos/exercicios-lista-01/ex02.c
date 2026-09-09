#include <stdio.h>

int main (){
    int n, original, reverso = 0, resto;
    printf("Digite um numero inteiro: ");
    scanf("%d", &n);

    original = n;
    
    while (n > 0){
        resto = n % 10;
        reverso = reverso * 10 + resto;
        n = n / 10;
    }

    if (reverso == original){
        printf("%d e capicua.\n", original);
    } else{
        printf("%d nao e capicua.\n", original);
    }
    return 0;
    
}