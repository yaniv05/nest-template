/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_6.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 8080 
#define MAX_CONN 5 

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Initialisation du générateur de nombres aléatoires
    srand(time(NULL));

    // Création du socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Erreur lors de la création du socket");
        exit(EXIT_FAILURE);
    }

    // Configuration du socket pour permettre la réutilisation de l'adresse
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt SO_REUSEADDR");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; 
    // Conversion du numéro de port au format réseau
    address.sin_port = htons(PORT);  

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind échoué");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, MAX_CONN) < 0) {
        perror("listen échoué");
        exit(EXIT_FAILURE);
    }

    printf("Serveur en écoute sur le port %d...\n", PORT);

    // Acceptation de la connexion client
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept échoué");
        exit(EXIT_FAILURE);
    }

    printf("Connexion établie avec le client.\n");

    while (1) {
        int random_number = rand()%100;  
        ssize_t sent = write(new_socket, &random_number, sizeof(random_number)); 
        if (sent <= 0) {
            perror("Erreur lors de l'envoi du nombre");
            break;
        }
        sleep(1);
    }

    // Fermer les sockets
    close(new_socket);
    close(server_fd);
    
    return 0;
}
