/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°1
 * Dominique Marcadet - 2022 - CC BY-SA
 *
 * Hello.cpp
 */

#include <iostream>
#include <string>

// Inclusion du fichier d'entête
#include "Hello.hpp"

// Définition de la fonction hello()
void hello( std::string world )
{
    std::cout << "Hello " << world << std::endl;
}
