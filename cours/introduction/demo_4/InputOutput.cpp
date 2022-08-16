/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°1
 * Dominique Marcadet - 2022 - CC BY-SA
 *
 * InputOutput.c
 *
 * Compilation avec édition de liens :
 *     c++ -o InputOutput InputOutput.cpp
 *
 * Exécution :
 *     ./InputOutput
 */


#include <iostream>

int main() {
    std::cout << "Donner un nombre : ";
    int n;
    std::cin >> n;
    if( std::cin.good() ) {
        std::cout << "Le carré de " << n << " est " << n * n << "\n";
    }
    return 0;
}
