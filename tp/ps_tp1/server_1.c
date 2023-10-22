/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_1.c
 */

// for printf()
#include <stdio.h>
// For rand(), srand(), sleep(), EXIT_SUCCESS
#include <stdlib.h>
// For time()
#include <time.h>
// For getpid(), getppid()
#include <unistd.h>

int main()
{
    // Initialisation du générateur de nombres aléatoires
    srand(time(NULL));

    //Affichage du premier message
    printf("Début du TP1 : Hello World \n");

    while(1){
        // Affichage des IDs des processus
        printf("ID du processus : %d, ID du processus père : %d, ID du groupe : %d\n", getpid(), getppid(), getpgrp());

        // Affichage d'un nombre aléatoire entre 0 et 99
        printf("Nombre aléatoire entre 0 et 99 : %d\n", rand() % 100);

        // Pause d'une seconde
        sleep(1);

    }
    //Message non affiché car boucle infinie
    printf("Fin du programme \n");
        
    return EXIT_SUCCESS;
}
/*
Réponses aux questions : 
Extrait d'un affichage du terminal 1 : 
ID du processus : 89040, ID du processus père : 88254, ID du groupe : 89040
Nombre aléatoire entre 0 et 99 : 52

1) On remarque que l'ID' du groupe est le même que celui du processus

2)On le retrouve bien dans le terminal 2 :
yanivbenchetrit 89040 88254 89040      0    1 S+   s004    0:00.01 ./server_1

3) Après kill "id du processus", le processus s'arrête bien et la console renvoie : zsh: terminated  ./server_1.

On remarque aussi que l'ID du processus père est toujours le même lorsqu'on relance le programme bien que l'ID du processus lui même est différend.

*/

