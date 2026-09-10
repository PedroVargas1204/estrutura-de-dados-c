#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (){
    char *s = malloc(30 * sizeof(char));
    if (s == NULL)
        return 1;
    
    strcpy(s, "Programação em C");
    printf("%s\n", s);

    free(s)
    return 0;
}