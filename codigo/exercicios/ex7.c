#include <stdio.h>

int main(){
    int idade;
    printf("Digite sua idade: ");
    scanf("%d", &idade);

    int maior_e_ativo = (idade >= 18) && (idade <= 65);
    printf("Maior e ativo: %d\n", maior_e_ativo);

    return 0;
}