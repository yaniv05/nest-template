/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_4.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>

pid_t child_pid;
int pipe_fd[2];

void stop_handler(int sig) {
    printf("[%s] Signal %d reçu. Arrêt en cours...\n", (getpid() != child_pid) ? "Père" : "Fils", sig);
    exit(EXIT_SUCCESS);
}

void child_exit_handler(int sig) {
    printf("[Père] Le fils a terminé. Arrêt en cours...\n");
    exit(EXIT_SUCCESS);
}

void exit_message(void) {
    printf("Message à la fin du programme %s.\n", getpid() == getpgid(0) ? "Père" : "Fils");
}

int main() {
    // Initialisation du générateur de nombres aléatoires
    srand(time(NULL));

    struct sigaction sa;
    sa.sa_handler = stop_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    struct sigaction sa_child;
    sa_child.sa_handler = child_exit_handler;
    sigemptyset(&sa_child.sa_mask);
    sa_child.sa_flags = 0;

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
    //Gestion de SIGCHLD
    if (sigaction(SIGCHLD, &sa_child, NULL) == -1) {
        perror("Erreur d'installation du gestionnaire pour SIGCHLD");
        exit(EXIT_FAILURE);
    }

    if (pipe(pipe_fd) == -1) {
        perror("Erreur lors de la création du tube");
        exit(EXIT_FAILURE);
    }

    child_pid = fork();

    //Affichage du premier message
    printf("[%s] TP1 : Hello World \n", (getpid() != child_pid) ? "Père" : "Fils");

    if (child_pid == 0) {  // Fils
        close(pipe_fd[1]);  // ferme l'extrémité d'écriture du tube
        int received_number;
        while (read(pipe_fd[0], &received_number, sizeof(int)) > 0) {
            printf("[Fils] Reçu: %d\n", received_number);
        }
        close(pipe_fd[0]);
    } else if (child_pid > 0) {  // Père
        close(pipe_fd[0]);  // ferme l'extrémité de lecture du tube
        int number_to_send = 1;
        while (1) {
            number_to_send =  rand() % 100;
            printf("[Père] Envoyé: %d\n", number_to_send);
            write(pipe_fd[1], &number_to_send, sizeof(int));
            sleep(1);
        }
        close(pipe_fd[1]);
    } else {
        perror("Erreur avec fork");
        exit(EXIT_FAILURE);
    }
    
    //Message en fin de programme
    if (atexit(exit_message) != 0) {
        perror("Erreur d'installation de la fonction exit_message");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
/*
Les processus s'arrêtent bien avec un CTRL C ou un kill sur le père ou sur le fils  

Lorsqu'on arrête le père en premier on obtient : 
[Père] Signal 15 reçu. Arrêt en cours...

Lorsqu'on arrête le fils en premier on obtient : 
[Père] Signal 15 reçu. Arrêt en cours...
[Père] Le fils a terminé. Arrêt en cours...
*/
