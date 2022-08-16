/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°1
 * Dominique Marcadet - 2022 - CC BY-SA
 *
 * CallHello.cpp
 *
 * Compilation avec édition de liens :
 *     c++ -o CallHello CallHello.cpp Hello.cpp
 * Exécution :
 *     ./CallHello World
 *
 * Compilation séparée puis édition de liens :
 *     c++ -c CallHello.cpp
 *     c++ -c Hello.cpp
 *     c++ -o CallHello CallHello.o Hello.o
 * Exécution :
 *     ./CallHello World
 */

// Inclusion du fichier d'entête
#include "Hello.hpp"


int main( int argc, char * argv[] )
{
    hello( argv[1] );
    return 0;
}
