/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°2
 * Dominique Marcadet - 2022 - CC BY-SA
 *
 * Allocation.cpp
 *
 * Compilation :
 *      c++ -g -std=c++20 Allocation.cpp -o Allocation
 * Exécution :
 *      ulimit -v 10000000
 *      ./Allocation
 *      valgrind ./Allocation
 */

#include <iostream>

// Variable globale : accessible par toutes les fonctions
// Variable allouée statiquement avant la première instruction de main()
int globale{ 7 };

void foo()
{
    // Variables locales : accessibles uniquement dans foo()
    // Variable locale allouée automatiquement
    int automatique{ 5 };
    // Variable locale allouée dynamiquement
    int * dynamique{ new int{ 33 } };
    // Variable locale allouée statiquement
    static int statique{ 587 };

    ++globale; ++automatique; ++*dynamique; ++statique;
    
    std::cout << "automatique = " << automatique << "\n";
    std::cout << "*dynamique = " << *dynamique << "\n";
    std::cout << "statique = " << statique << "\n";
    
    // Sans cette instruction, fuite de mémoire;
    delete dynamique;
    // Destruction de automatique après la sortie de foo()
}

void bar()
{
    static unsigned nb = 0;
    while( true ) {
        std::cout << "nb = " << ++nb << "\n";
        new int[1000000];
    }
}

int main()
{
    std::cout << "globale = " << globale << "\n";
    foo();
    foo();
    std::cout << "globale = " << globale << "\n";
    //bar();
}

// Destruction de globale après la sortie de main()
// Destruction de statique après la sortie de main()
