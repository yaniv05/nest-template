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

// Variable globale qui détermine si la boucle doit continuer à s'exécuter
volatile bool running = true;

// Gestionnaire pour le signal SIGINT
void stop_handler(int sig) {
    if (getpid() == getpgid(0)) {
        printf("[Père] Signal %d reçu. Arrêt en cours\n", sig);
    } else {
        printf("[Fils] Signal %d reçu. Arrêt en cours\n", sig);
    }
    running = false;
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

    pid_t pid = fork();

    if (pid == 0) {  // Fils
        while (running) {
            printf("[Fils] PID: %d, PPID: %d, PGID: %d\n", getpid(), getppid(), getpgid(0));
            sleep(1);
        }
    } else if (pid > 0) {  // Père
        while (running) {
            printf("[Père] PID: %d, PPID: %d, PGID: %d\n", getpid(), getppid(), getpgid(0));
            sleep(1);
        }
    } else {
        perror("Erreur avec fork");
        exit(EXIT_FAILURE);
    }

    printf("Fin du programme, %s se termine.\n", (pid == 0) ? "Fils" : "Père");
        
    return EXIT_SUCCESS;
}
/*
Réponses aux questions 

1)CTRL C envoie un SIGINT à tous les processus du groupe dans le terminal en cours, le fils héritant du groupe du processus du père, les deux s'arrêtent donc.

*/
