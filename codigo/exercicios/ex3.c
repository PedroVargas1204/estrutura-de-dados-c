#include <stdio.h>

int main (){
    int a, b, aux;

    printf("Digite o valor de a: ");
    scanf("%d", &a);

    printf("Digite o valor de b: ");
    scanf("%d", &b);

    aux = a;
    a = b;
    b = aux;

    printf("Depois da troca:\n");
    printf("a = %d\n",a);
    printf("b = %d\n",b);
    
    return 0;
}