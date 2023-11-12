/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * MessageBox.hpp
 */

#pragma once

#include <mutex>
#include <condition_variable>

#include "../BasicMessageBox.hpp"

/*
 * FIFO d'echange de messages entre producteurs et consommateurs
 * Version pour synchronisation entre threads
 */
class MessageBox : public BasicMessageBox {
public:  
    void put(int message) {
        // TODO :
        // - Ajouter les instructions de synchronisation
        // - Ne pas faire d'affichage dans cette méthode
        std::unique_lock<std::mutex> lock(mtx);
        while (isFull()) {
            notFull.wait(lock);
        }
        basic_put(message);
        ++count;  // Augmenter le nombre de messages après avoir déposé un message
        notEmpty.notify_one();
    }

    int get() {
        // TODO :
        // - Ajouter les instructions de synchronisation
        // - Ne pas faire d'affichage dans cette méthode
        std::unique_lock<std::mutex> lock(mtx);
        while (isEmpty()) {
            notEmpty.wait(lock);
        }
        int message = basic_get();
        --count;  // Diminuer le nombre de messages après avoir retiré un message
        notFull.notify_one();
        return message;
    }

private:
    // TODO : 
    // - Ajouter les objets de synchronisation
    std::mutex mtx;  // Mutex pour la synchronisation
    std::condition_variable notFull;  // Condition pour la disponibilité de l'espace
    std::condition_variable notEmpty;  // Condition pour la disponibilité du message

    unsigned int count = 0;  // Variable pour suivre le nombre de messages dans la boîte

    bool isFull() const {
        return count == box_size_;  // La boîte est pleine si le compte atteint la taille de la boîte
    }

    bool isEmpty() const {
        return count == 0;  // La boîte est vide si le compte est 0
    }
};
 
