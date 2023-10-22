/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * client_5.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>

void stop_handler(int sig) {
    printf("[Client] Signal %d reçu. Arrêt en cours...\n", sig);
    exit(EXIT_SUCCESS);
}

void exit_message(void) {
    printf("[CLIENT] Message à la fin du programme.\n");
}

int main() {

    struct sigaction sa;
    sa.sa_handler = stop_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Erreur lors de l'installation du gestionnaire pour SIGINT");
        exit(EXIT_FAILURE);
    }

    if (sigaction(SIGTERM, &sa, NULL) == -1) {
        perror("Erreur d'installation du gestionnaire pour SIGTERM");
        exit(EXIT_FAILURE);
    }


    int fifo_fd = open("fifo", O_RDONLY);
    if (fifo_fd == -1) {
        perror("Erreur lors de l'ouverture de la fifo en lecture");
        exit(EXIT_FAILURE);
    }

    //Message en fin de programme
    if (atexit(exit_message) != 0) {
        perror("Erreur d'installation de la fonction exit_message");
        exit(EXIT_FAILURE);
    }

    //Affichage du premier message
    printf("[SERVEUR] TP1 : Hello World \n");

    int received_number;
    while (read(fifo_fd, &received_number, sizeof(int)) > 0) {
        printf("[Client] Reçu: %d\n", received_number);
    }

    close(fifo_fd);
    return EXIT_SUCCESS;
}
/*
Lorsqu'on arrête un des deux processus l'autre s'arête aussi
*/

