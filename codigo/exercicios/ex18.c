#include <stdio.h>
#include <string.h>

int contar_vogais(char *s) {
    int count = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        char c = s[i];
        if (c == 'a' || c == 'A' ||
            c == 'e' || c == 'E' ||
            c == 'i' || c == 'I' ||
            c == 'o' || c == 'O' ||
            c == 'u' || c == 'U') {
            count++;
        }
    }
    return count;
}

int main() {
    char frase[100];

    printf("Digite uma frase: ");
    scanf("%99[^\n]", frase);

    printf("Vogais: %d\n", contar_vogais(frase));

    return 0;
}