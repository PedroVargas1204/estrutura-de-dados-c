#include <stdio.h>

int main (){
    int n;
    printf("Digite um numero de 4 digitos: ");
    scanf("%d", &n);

    int primeira_metade = n / 100;
    int segunda_metade = n % 100;
    int soma = primeira_metade + segunda_metade;

    if (soma * soma == n){
        printf("%d tem a propriedade!\n",n);
    } else{
        printf("%d nao tem a propriedade.\n",n);
    }
    return 0;

}