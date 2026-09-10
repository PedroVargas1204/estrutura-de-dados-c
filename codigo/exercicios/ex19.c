#include <stdio.h>
#include <stdlib.h>

int main(){
    int n;
    printf("Digite um numero inteiro positivo: ");

    if (scanf("%d", &n) != 1) {
        printf("Entrada invalida.\n");
        return 1;
    }

    if (n <= 0) {
        printf("O numero deve ser maior que zero.\n");
        return 1;
    }

    int *v = malloc(n * sizeof(int));
    if (v == NULL) {
        printf("Erro: memoria insuficiente.\n");
        return 1;
    }

    int soma = 0;
    for (int i = 0; i < n; i++){
        v[i] = (i + 1) * (i + 1);
        soma += v[i];
    }
    printf("Soma: %d\n", soma);

    free(v);
    return 0;
}