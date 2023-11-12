/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * Consumer.hpp
 */

#pragma once

#include <iostream>
#include <thread>

#include "../ProdOrCons.hpp"
 
#include "osyncstream.hpp"
#include "MessageBox.hpp"


/*
 * Consommateur de messages
 */
class Consumer : public ProdOrCons< MessageBox > {
public:
    // Le constructeur de ProdOrCons sera utilisé comme constructeur de Consumer
    using ProdOrCons::ProdOrCons;
 
    void operator()() override {
        // TODO :
        // - Retirer de box_ nb_messages_ entiers avec attente aléatoire avant
        //   chaque retrait.
        // - Afficher des messages entre chaque étape pour suivre l'avancement.
        // - Afficher un message d'erreur si un nombre négatif est extrait.
        for (unsigned i = 0; i < nb_messages_; ++i) {
            // Attente aléatoire avant de retirer le message
            std::this_thread::sleep_for(std::chrono::milliseconds(random_engine_()));

            {
                osyncstream{ std::cout } << "Consumer " << name_ << " trying to fetch message\n";
            }

            int message = box_.get();

            if (message < 0) {
                osyncstream{ std::cout } << "Consumer " << name_ << " found an error: negative message\n";
            } else {
                osyncstream{ std::cout } << "Consumer " << name_ << " has fetched message: " << message << "\n";
            }
        }
    }
};

