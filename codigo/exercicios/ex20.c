#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comeca_com_vogal(char *s){
    if (s == NULL || s[0] == '\0')
        return 0;
    
    char c = s[0];
    return (c == 'a' || c == 'A' ||
            c == 'e' || c == 'E' ||
            c == 'i' || c == 'I' ||
            c == 'o' || c == 'O' ||
            c == 'u' || c == 'U'); 
}

int main(){
    char *palavra = malloc(20 * sizeof(char));
    if (palavra == NULL)
        return 1;
    
    strcpy(palavra, "abacaxi");

    if (comeca_com_vogal(palavra)) {
        printf("Comeca com vogal!");
    } else {
        printf("Nao comeca com vogal.");
    }
    free(palavra);
    return 0

}