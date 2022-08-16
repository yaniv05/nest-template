/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°2
 * Dominique Marcadet - 2022 - CC BY-SA
 *
 * String.cpp
 *
 * Compilation :
 *      c++ -std=c++20 String.cpp -o String
 * Exécution :
 *      ./String
 */

#include <iostream>
#include <ios>
#include <string>

int main()
{
    // C : tableau de caractères avec une sentinelle
    char s1[] = "hello";
    std::cout << "sizeof( s1 ) = " << sizeof( s1 ) << "\n";
    const char * s2 = "hello" ;
    // Affichage de true/false plutôt que 1/0
    std::cout << std::boolalpha;
    // Comparaison de pointeurs, pas des chaînes
    std::cout << "s1 == s2 = " <<  ( s1 == s2 ) << "\n";
    
    std::string s3{ "hello" };
    // Une string C++ se compare bien, y compris avec une
    // chaîne de caractères C
    std::cout << "s1 == s3 = " << ( s1 == s3 ) << "\n";
    // Concaténation
    std::string s4{ " world" };
    std::cout << "s3 + s4 = " << s3 + s4 << "\n";
    s3 += s4;
    std::cout << "s3 = " << s3 << "\n";
}
