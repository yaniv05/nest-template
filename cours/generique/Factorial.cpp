/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°5
 * Dominique Marcadet - 2022 - CC BY-SA
 *
 * Factorial.cpp
 *
 * Compilation :
 *     c++ -std=c++20 -o Factorial Factorial.cpp
 * Exécution :
 *     ./Factorial
 */

#include <iostream>

template< unsigned N >
struct Factorial {
    static constexpr unsigned value{
	         N * Factorial< N-1 >::value };
};

template<>
struct Factorial< 0 > {
    static constexpr unsigned value{ 1 };
};


int main()
{
    std::cout << "Factorial< 0 > = " << Factorial< 0 >::value << "\n";
    std::cout << "Factorial< 13 > = " << Factorial< 13 >::value << "\n";
    std::cout << "Factorial< 14 > = " << Factorial< 14 >::value << "\n";
}

