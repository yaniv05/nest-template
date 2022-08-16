/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°2
 * Dominique Marcadet - 2022 - CC BY-SA
 *
 * Pointer_1.cpp
 *
 * Compilation :
 *      c++ -std=c++20 Pointer_1.cpp -o Pointer_1
 * Exécution :
 *      ./Pointer_1
 */

#include <iostream>

int main()
{
    int i{ 5 };
    std::cout << " i = " << i  << "\n";
    int * p{ &i };
    std::cout << " p = " << p  << "\n";
    std::cout << "*p = " << *p << "\n";
    
    std::cout << "Affectation de -7 dans *p\n";
    *p = -7;
    std::cout << " i = " << i  << "\n";
    std::cout << " p = " << p  << "\n";
    std::cout << "*p = " << *p << "\n";
}
