# Outils, langages et pratique des systèmes à microprocesseurs (partie I) - SE203

## Alaf do Nascimento Santos

Le 09/09/2022, **Chaîne de compilation**

## Page 49

### Exercice 1 : 
**Traduire en assembleur ARM le code suivant :**
```
uint32_t a; // global variable
...
for (uint8_t i=0; i<=a; i++)
    g();
```
**Réponse :**

```
.data
.word a

.text
ldr r2, =a /* global variable a */
mov r3, #0 /* i = 0 */

startLoop:
	cmp r3, r2 	/* to compare a and i */
	bgt endLoop /* BRANCH GREATER THAN */
	bl g		/* g(); */
	add r3, r3, #1  /* i++; */
	b startLoop /* next iteration */
endLoop: b endLoop

g:
	bx	lr /* return to the function call point */
```

**Même question si i est un unsigned int. Conclusion ?**

Une variable de type *uint8_t* occupe, dans l'architecture ARM donnée, 1 byte d'espace mémoire, qui est la plus petite unité de mémoire adressable. Dans ce cas là, la variable **a** a une valeur de 32 bits et **i** a une valeur de 8 bits, donc il faut vérifier si la boucle va s'arreter (est-ce que **i** peut avoir la même valeur que **a** ?). Si la variable i était de type *unsigned int*,  nous aurions 4 bytes de mémoire réservés et pour celà il ne faut pas vérifier si la boucle est elle possible parce que **a** et **i** on la même valeur maximale (255 en base 10).


> Indice : pour voir ce que produit GCC pour ARM :
```
uint32_t a; // global variable
__attribute__((naked)) void f() {
 for (uint8_t i=0; i<=a; i++)
 g();
}
```
> Puis : arm-none-eabi-gcc -Os -S t.c 

### Exercice 2 :
Traduire en assembleur ARM le code suivant :
```
// Global variables
uint32_t *a;
uint32_t *b;
uint32_t *c;
…
*a += *c;
*b += *c;
```

**Réponse :**

```
.global _start

.text
_start:

ldr r0, .ap @ uint32_t *a;
ldr r1, .bp @ uint32_t *b;
ldr r2, .cp @ uint32_t *c;

ldr r3, [r0]
ldr r4, [r2]
add r3,r3,r4
str r3,[r0]

ldr r3, [r1]
ldr r4, [r2]
add r3,r3,r4
str r3,[r1]

end : b end

.ap :
	.global a
	.word 0x00001000

.bp :
	.global b
	.word 0x00002000

.cp :
	.global c
	.word 0x00003000

```

### Exercice 2 (suite) :

Comparez avec ce que produit GCC, ainsi :
```
// Global variables
uint32_t *a;
uint32_t *b;
uint32_t *c;
__attribute__((naked)) void f() {
 *a += *c;
 *b += *c;
}
```
Puis : arm-none-eabi-gcc -O2 -S t.c

**Pourquoi GCC charge-t-il deux fois le contenu de \*c au lieu d'une seule ?**

Parce que si les pointeurs **\*a** et **\*c** pointent vers la même adresse mémoire, après la première somme effectuée, la valeur contenue dans l'adresse de **\*a** et **\*c** seront modifiée et donc il faut charger une deuxième fois le contenu de **\*c** avant de l'utiliser dans la deuxième opération de somme.


## Page 119

### Exercice 1 :

**1) Sur un PC Linux x86_64 actuel et par adresses croissantes, dans quel ordre sont stockées les sections suivantes : text, data\*, rodata\*, bss, pile et tas au moment de l’exécution ?**
L'ordre par adresses croissantes: text, rodata, data, bss, tas, pile.

Exemple :

```
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
```
Sortie :
> text   : 81ac5145
> rodata : 81ac6008
> data   : 81ac8038
> bss    : 81ac8040
> tas    : 834042a0
> pile   : 94859114



**2) Dans quel sens croît la pile ?**
Décroissant, de façon où le registre SP devrait toujours indiquer le dessus de la pile.

On peut vérifier ça on faisant les exemples suivantes :

```
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
```
**Sortie :** 2ee3488, 2ee3480, 2ee3478

Les adresses diminuent (sens décroissant) comme prévu. C'est ça que se passe avec la pile quand on appele une fonction. Comme dans l'exemple il est utilisée le malloc, on a sur le tas. 

Dans le cas de la pile, l'appel de fonction est effectué, comme suit dans l'exemple :


```
#include<stdio.h>
#include<stdint.h>

uint32_t * pos[2];

void h(){
    int c;
    printf("%x, %x, %x\n", pos[0], pos[1], &c);
}

void g(){
    int b;
    pos[1] = &b;
    h();
}

void f(){
    int a;
    pos[0] = &a;
    g();
}

int main(){
    f();
    return 0;
}
```

> **Sortie :** 43e9ea4c, 43e9ea2c, 43e9ea0c (sens décroissant)


### Exercice 2 :

**1) Compilez sans édition de lien ce code-ci (http://bit.ly/2ApXoDl) pour ARM avec une chaîne récente, et avec les optimisations suivantes : Os, O0, O1 et O2. Pour chaque niveau d'optimisation, justifiez la taille des sections de données que vous obtenez.**

En utilisant la commande << arm-none-eabi-gcc -Os -c ex3.c >> et après << size ex3.o >> :


| text | data | bss | dec |
| -------- | -------- | -------- | -------- |
| 163     | 4     | 5     | 172 |

En utilisant la commande << arm-none-eabi-gcc -O0 -c ex3.c >> et après << size ex3.o >> :


| text | data | bss | dec |
| -------- | -------- | -------- | -------- |
| 248     | 4     | 5     | 257 |


En utilisant la commande << arm-none-eabi-gcc -O1 -c ex3.c >> et après << size ex3.o >> :


| text | data | bss | dec |
| -------- | -------- | -------- | -------- |
| 170     | 4     | 5     | 179 |

En utilisant la commande << arm-none-eabi-gcc -O2 -c ex3.c >> et après << size ex3.o >> :


| text | data | bss | dec |
| -------- | -------- | -------- | -------- |
| 170     | 4     | 5     | 179 |


Pour chaque optimisation, on peut vérifier que seulement la taille de la section text qui change, puisque les données restent les mêmes toujours, l'optimisation agira sur le nombre d'instructions exécutées (text section).

**2) Remplacez const char mesg[] par static const char mesg[]. Expliquez les différences dans les sections de données par rapport à la question précédente (elles dépendent ici aussi des optimisations).**

Comme il s'agit d'une variable globale, en utilisant static, on indique que le nom ne sera pas exporté par l'éditeur de liens. Mais le spécificateur const fait que la variable soit stockée dans .rodata et .text. Cela peut changer si par exemple l'optimisation fait une suppression du static.

**3) Remplacez const char mesg[] par const char \*mesg. puis par const char * const mesg. Expliquez les différences dans le code généré et les sections de données par rapport à la question 2.**

Lorsqu'on déclare un pointeur constant, il sera stocké dans rodata.