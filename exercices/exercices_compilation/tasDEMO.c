#include<stdio.h>
#include<stdlib.h>

int main(){

    int * premier  = malloc(sizeof(int));
    int * deuxieme = malloc(sizeof(int));
    int * troisieme = malloc(sizeof(int));

    printf("%x, %x, %x\n", &premier, &deuxieme, &troisieme);

    free(premier);
    free(deuxieme);
    free(troisieme);
    return 0;
}