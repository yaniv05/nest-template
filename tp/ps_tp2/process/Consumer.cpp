/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * Consumer.cpp
 * c++ -std=c++20 Consumer.cpp -o Consumer -lpthread -lrt
 */

#include <iostream>
#include <thread>

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/named_semaphore.hpp>

#include "../Random.hpp"
#include "../ProdOrCons.hpp"

#include "MessageBox.hpp"

/*
 * Consommateur de messages
 */
class Consumer : public ProdOrCons< MessageBox > {
public:
    // Le constructeur de ProdOrCons sera utilisé comme constructeur de Consumer
    using ProdOrCons::ProdOrCons;
 
    void operator()() override {
        // TODO :retirer de box_ nb_messages_ entiers avec attente aléatoire avant
        // chaque retrait. Afficher des messages pour suivre l'avancement.
        // Afficher un message d'erreur si un nombre négatif est extrait.
        for (unsigned i = 0; i < nb_messages_; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(random_engine_()));
            int message = box_.get();
            if (message < 0) {
                std::cerr << "Consumer " << name_ << " error: negative message " << message << std::endl;
            } else {
                std::cout << "Consumer " << name_ << " fetched: " << message << std::endl;
            }
        }
    }
};


int main()
{
    using namespace boost::interprocess;

    // TODO : attendre que le producteur ait signalé que la boîte
    // est prête, accéder à la mémoire partagée, la projeter en mémoire,
    // y accéder comme boîte à lettres, lancer le consommateur
    
    using namespace boost::interprocess;
    // Attendre que la boîte soit prête
    named_semaphore semaphore(open_only, "Semaphore");
    semaphore.wait();

    // Accéder à la mémoire partagée
    shared_memory_object shm(open_only, "SharedMemory", read_only);
    mapped_region region(shm, read_only);
    void* addr = region.get_address();
    MessageBox* box = static_cast<MessageBox*>(addr);

    // Lancer le consommateur
    Random randomEngine(50);
    Consumer consumer(1, *box, randomEngine, 20);
    std::thread consumerThread(std::ref(consumer));
    consumerThread.join();

    return 0;
}

