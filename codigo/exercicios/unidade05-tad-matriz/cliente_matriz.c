#include <stdio.h>
#include "matriz.h"

int main(void) {
    Matriz a = matriz_zeros(2, 3);
    a.elementos[0][0] = 1; a.elementos[0][1] = 2; a.elementos[0][2] = 3;
    a.elementos[1][0] = 4; a.elementos[1][1] = 5; a.elementos[1][2] = 6;

    printf("A (2x3):\n");
    matriz_imprime(a);

    Matriz at = matriz_transposta(a);
    printf("\nA^T (3x2):\n");
    matriz_imprime(at);

    Matriz prod = matriz_multiplica(a, at);
    printf("\nA * A^T (2x2):\n");
    matriz_imprime(prod);

    Matriz id3 = matriz_identidade(3);
    Matriz a_vezes_id = matriz_multiplica(a, id3);
    printf("\nA * I(3) == A ?  %d\n", matriz_iguais(a_vezes_id, a));

    printf("\n--- casos INVALIDOS ---\n");

    Matriz soma_invalida = matriz_adiciona(a, id3);
    printf("A(2x3) + I(3)    -> ");
    matriz_imprime(soma_invalida);

    Matriz mult_invalida = matriz_multiplica(a, a);
    printf("A(2x3) * A(2x3)  -> ");
    matriz_imprime(mult_invalida);

    Matriz zeros_invalida = matriz_zeros(0, 5);
    printf("matriz_zeros(0,5)-> ");
    matriz_imprime(zeros_invalida);

    return 0;
}
