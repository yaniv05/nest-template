/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * MessageBox.hpp
 */

#pragma once

#include <array>
#include <algorithm>

#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>

#include "../BasicMessageBox.hpp"

/*
 * FIFO d'echange de messages entre producteurs et consommateurs
 * Version pour synchronisation entre processus
 */
class MessageBox : public BasicMessageBox {
public: 
    MessageBox() {
        notEmpty = false;
        notFull = true;
    }

    void put(int message) {
        // TODO : ajouter les mecanismes de synchronisation
        boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock(mutex);
        while (!notFull) {  // Attendre si la boîte est pleine
            notFullCondition.wait(lock);
        }
        basic_put(message);
        notEmpty = true;
        notEmptyCondition.notify_one();
    }
 
    int get() {
        // TODO : ajouter les mecanismes de synchronisation
        boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock(mutex);
        while (!notEmpty) {  // Attendre si la boîte est vide
            notEmptyCondition.wait(lock);
        }
        int message = basic_get();
        notFull = true;
        notFullCondition.notify_one();
        return message;
    }
 
private:
    // TODO : ajouter les objets de synchronisation
    boost::interprocess::interprocess_mutex mutex;
    boost::interprocess::interprocess_condition notFullCondition, notEmptyCondition;
    bool notEmpty, notFull;

    bool isFull() const {
        return (put_index_ + 1) % box_size_ == get_index_;
    }

    bool isEmpty() const {
        return put_index_ == get_index_;
    }
};
 
