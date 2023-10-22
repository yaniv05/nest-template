/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_3.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>

// Variables globales
volatile bool running = true;
pid_t child_pid;

// Gestionnaire pour le signal SIGINT
void stop_handler(int sig) {
    if (getpid() != child_pid) { // Père
        printf("[Père] Signal %d reçu. Arrêt du père...\n", sig);
        if (running) {
            kill(child_pid, SIGINT);  // Tuer le fils uniquement si running est vrai
            printf("Arrêt du fils suite à l'arrêt du père ...\n");
        }
    } else {  // Fils
        printf("[Fils] Signal %d reçu. Arrêt en cours...\n", sig);
    }
    running = 0;
}

void child_exit_handler(int sig) {
    printf("[Père] Le fils a terminé. Arrêt en cours...\n");
    running = 0;
}

void exit_message(void) {
    printf("Message à la fin du programme %s.\n", getpid() == getpgid(0) ? "Père" : "Fils" );
}

int main()
{
    // Initialisation du générateur de nombres aléatoires
    srand(time(NULL));

    struct sigaction sa;
    sa.sa_handler = stop_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    //Pour gerer le signal arret du fils
    struct sigaction sa_child;
    sa_child.sa_handler = child_exit_handler;
    sigemptyset(&sa_child.sa_mask);
    sa_child.sa_flags = 0;
    sigaction(SIGCHLD, &sa_child, NULL);

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

    child_pid = fork();

    if (child_pid == 0) {  // Fils
        while (running) {
            printf("[Fils] PID: %d, PPID: %d, PGID: %d\n", getpid(), getppid(), getpgid(0));
            printf("Nombre aléatoire entre 0 et 99 : %d\n", rand() % 100);
            sleep(1);
        }
    } else if (child_pid > 0) {  // Père
        while (running) {
            printf("[Père] PID: %d, PPID: %d, PGID: %d\n", getpid(), getppid(), getpgid(0));
            printf("Nombre aléatoire entre 0 et 99 : %d\n", rand() % 100);
            sleep(1);
        }
    } else {
        perror("Erreur avec fork");
        exit(EXIT_FAILURE);
    }

    printf("Fin du programme, %s se termine.\n", (child_pid == 0) ? "Fils" : "Père");
        
    return EXIT_SUCCESS;
}
/*
Réponses aux questions 

1)CTRL C envoie un SIGINT à tous les processus du groupe dans le terminal en cours, le fils héritant du groupe du processus du père, les deux s'arrêtent donc.

2)On remarque que le processus fils s'arrête, cependant il est toujours listé de manière diférente. Il s'agit d'un processus zombie:
avant le kill : yanivbenchetrit 90827 90826 90826      0    1 S+   s004    0:00.00 ./server_3
apres le kill : yanivbenchetrit 90827 90826 90826      0    1 Z+   s004    0:00.00 (server_3)

3) Cette fois ci le fils n'est plus visible

4)On observe que lorsque le père s'arrête, le fils lui continue de tourner.
*/
