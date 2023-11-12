/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * Producer.cpp
 * c++ -std=c++20 Producer.cpp -o Producer -lpthread -lrt
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
 * Producteur de messages
 */
class Producer : public ProdOrCons< MessageBox > {
public:
    // Le constructeur de ProdOrCons sera utilisé comme constructeur de Producer
    using ProdOrCons::ProdOrCons;
 
    void operator()() override {
        // TODO : déposer dans box nb_messages nombres entiers positifs avec attente
        // aléatoire entre chaque. Afficher des messages pour suivre l'avancement.
        for (unsigned i = 0; i < nb_messages_; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(random_engine_()));
            box_.put(i);
            std::cout << "Producer " << name_ << " produced: " << i << std::endl;
        }
    }
};


int main()
{
    using namespace boost::interprocess;

    // TODO : créer la mémoire partagée, la projeter en mémoire,
    // y construire la boîte à lettres, signaler au consommateur
    // que la boîte est prête, lancer le producteur
    
    using namespace boost::interprocess;
    // Créer un segment de mémoire partagée
    shared_memory_object shm(create_only, "SharedMemory", read_write);
    shm.truncate(sizeof(MessageBox));

    // Mapper ce segment à l'adresse du processus
    mapped_region region(shm, read_write);
    void* addr = region.get_address();

    // Construction de la boîte à lettres dans la mémoire partagée
    MessageBox* box = new (addr) MessageBox();

    // Signaler au consommateur que la boîte est prête
    named_semaphore semaphore(create_only, "Semaphore", 1);

    // Lancer le producteur
    Random randomEngine(50);
    Producer producer(1, *box, randomEngine, 20);
    std::thread producerThread(std::ref(producer));
    producerThread.join();

    return 0;
}

