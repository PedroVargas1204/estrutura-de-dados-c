#include <stdio.h>

void dobrar(int *n){
    *n = *n *2;
}

int main(){
    int x = 4;
    dobrar(&x);

    printf("%d", x);

    return 0;

}