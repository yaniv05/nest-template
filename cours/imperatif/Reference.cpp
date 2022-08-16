/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°2
 * Dominique Marcadet - 2022 - CC BY-SA
 *
 * Reference.cpp
 *
 * Compilation :
 *      c++ -std=c++20 Reference.cpp -o Reference
 * Exécution :
 *      ./Reference
 */

#include <iostream>

int main()
{
    int    i{ 3 };
    int & ri{ i };
    std::cout << "i = " << i << " - ri = " << ri << "\n";
    std::cout << "&i = " << &i << " - &ri = " << &ri << "\n";
    
    i = 5;
    std::cout << "i = " << i << " - ri = " << ri << "\n";
    
    ri = -2;
    std::cout << "i = " << i << " - ri = " << ri << "\n";
    
    int j{ 7 };
    ri = j;
    std::cout << "i = " << i << " - ri = " << ri << "\n";
    j = -1;
    std::cout << "i = " << i << " - ri = " << ri << "\n";
    
    const int    k{ 8 };
    const int & rk{ k };
}
