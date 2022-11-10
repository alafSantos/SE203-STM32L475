# Outils, langages et pratique des systèmes à microprocesseurs
## Alaf do Nascimento Santos

## TD : Assembleur ARM

### Exercice 1 : Initialisation d’une zone mémoire
**Écrire un programme qui permet de remplir une zone mémoire avec un motif prédéfini.**

> Le motif 0xdeadbeef
> La zone mémoire commencera à l’adresse 0x10000000
> La taille de la zone mémoire 256 octets (64 mots)

**Réponse :** TD01.s

### Exercice 2 : Copie du contenu d’une zone mémoire
**Ajouter au programme précédent de quoi copier la zone pré-remplie à une autre position.**

> L’adresse de la nouvelle position 0x10000300
> Taille de la zone à copier 256 octets
> Le programme de copie ne doit pas faire d’hypothèse sur le motif ayant servi à initialiser la première zone. Il devra donc lire puis écrire chaque élément.

**Réponse :** TD02.s

### Exercice 3 : Procédures réutilisables
**Nous voulons pouvoir réutiliser le code d’initialisation et de copie avec des motifs, adresses et tailles de zones différents. Modifier le code précédent pour avoir une procédure principale qui fait appel au code d’initialisation puis de copie, plusieurs fois, avec des paramètres différents.**

**Réponse :** TD03.s

### Exercice 4 : Manipulation d’une chaine de caractère
**En utilisant une directive, inclure à la fin d’un programme la chaine de caractère "Bonjour le monde!". Comme en C, il faudra garantir qu’en mémoire, la chaine se terminera par un octet nul.**

**Écrire un programme qui copie cette chaine plusieurs fois à différents endroits en mémoire.**

**Ce programme sera structuré comme suit:**

* une procédure principale où on récupère l’adresse de la chaine ainsi que l’adresse de destination,
* une procédure dans laquelle s’effectue la copie qui sera appelée plusieurs fois à partir de la procédure principale.

**Réponse :** TD04.s
