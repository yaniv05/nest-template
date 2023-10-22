/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_5.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <time.h>

void stop_handler(int sig) {
    printf("[Serveur] Signal %d reçu. Arrêt en cours...\n", sig);
    exit(EXIT_SUCCESS);
}

void exit_message(void) {
    printf("[SERVEUR] Message à la fin du programme.\n");
}

int main() {
    // Initialisation du générateur de nombres aléatoires
    srand(time(NULL));

    int number_to_send;

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


    int fifo_fd = open("fifo", O_WRONLY);
    if (fifo_fd == -1) {
        perror("Erreur lors de l'ouverture de la fifo en écriture");
        exit(EXIT_FAILURE);
    }
    //Message en fin de programme
    if (atexit(exit_message) != 0) {
        perror("Erreur d'installation de la fonction exit_message");
        exit(EXIT_FAILURE);
    }
    
    //Affichage du premier message
    printf("[SERVEUR] TP1 : Hello World \n");
   
    while (1) {
        number_to_send =  rand() % 100;
        printf("[Serveur] Envoyé: %d\n", number_to_send);
        write(fifo_fd, &number_to_send, sizeof(int));
        sleep(1);
    }



    close(fifo_fd);
    return EXIT_SUCCESS;
}
/*
Lorsqu'on arrête un des deux processus l'autre s'arête aussi
*/
