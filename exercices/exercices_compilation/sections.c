// Alaf do Nascimento Santos
// 05/10/2022
// Exercice 1 : SE203 chaîne de compilation - anatomie des exécutables, page 119/123

/* 
    code basé sur le slide 92/123 du cours de chaîne de compilation 
    Où vont les variables ?
*/

#include<stdio.h>
#include<stdlib.h>

const int varRodata = 3;
int varData = 5;
int varBss;

void fonc(){
    
}

int main(){
    int varPile;
    int *varTas = malloc(sizeof(int));

    printf("text : %x\nrodata : %x\ndata : %x\nbss : %x\npile : %x\ntas : %x\n", &fonc, &varRodata, &varData, &varBss, &varPile, varTas);
    return 0;
}
