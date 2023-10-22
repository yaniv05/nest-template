/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_2.c
 
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>

// Variable globale qui détermine si la boucle doit continuer à s'exécuter
volatile bool running = true;

// Gestionnaire pour le signal SIGINT
void stop_handler(int sig) {
    printf("Signal reçu : %d\n", sig);
    printf("Arrêt demandé \n");
    running = false;
}

void exit_message(void) {
    printf("Message à la fin du programme.\n");
}

int main()
{
    // Initialisation du générateur de nombres aléatoires
    srand(time(NULL));

    struct sigaction sa;
    sa.sa_handler = stop_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    //Gestion de SIGINT
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Erreur lors de l'installation du gestionnaire pour SIGINT");
        exit(EXIT_FAILURE);
    }

    //Gestion de SIGTERM
    if (sigaction(SIGTERM, &sa, NULL) == -1) {
        perror("Erreur d'installation du gestionnaire pour SIGTERM");
        exit(EXIT_FAILURE);
    }

    //Message en fin de programme
    if (atexit(exit_message) != 0) {
        perror("Erreur d'installation de la fonction exit_message");
        exit(EXIT_FAILURE);
    }
    //Affichage du premier message
    printf("Début du TP1 : Hello World \n");

    while(running){
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
Réponses aux questions

1) Le message est bien affiché : 
^CSignal reçu : 2
Arrêt demandé 
Fin du programme 

2) Le message est bien affiché avec l'option -s INT, mais n'est pas affiché sans option. 

3)En ajoutant la gestion pour SIGTERM on a bien le message affiché :
Signal reçu : 15
Arrêt demandé 
Fin du programme 

3)Le message n'est pas affiché, on obtient : zsh: killed     ./server_2
En lisant la doc o nse rend compte que ce n'est pas possible d'afficher le message puisque -s KILL tue le processus sans délai et sans le laisser terminer
En utilisant kill sans option sur le processus père on remarque que le processus fils ne s'arrête pas. Si le signal était géré d'une manière spécifique côté père on aurait eu un message associé.
En utilisant l'option -s KILL, on obtient: [Opération terminée] mais il semble que le processus ne s'arrête pas réellement.

4)Enfaisant controle C, on obtient bien le message de gestion mais le processus ne s'arrête pas, la boucle infinie continue puisque la variable vaut toujours 1.
En faisant kill on obtient : 
Signal reçu : 15
Arrêt demandé 
Si on avait pas géré le cas SIGTERM, le gestionnaire par défaut aurait arrêté le programme
Mais le programme ne s'arrête toujours pas. 
Par contre le kill -9 arrête bien le programme.

5)Le message est affiché pour un CTRL C et un kill mais pas pour un kill -9 car comme nous l'avons dit, le kill -9 tue imméiatement le programme rien ne s'execute ensuite.
*/


