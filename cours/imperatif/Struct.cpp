/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°2
 * Dominique Marcadet - 2022 - CC BY-SA
 *
 * Struct.cpp
 *
 * Compilation :
 *      c++ -std=c++20 Struct.cpp -o Struct
 * Exécution :
 *      ./Struct
 */

#include <iostream>

enum class Sexe { Homme, Femme };
// Énumération issue de C :
// enum Sexe { Homme, Femme };

// Le caractère _ à la fin du nom de l'attribut est une convention
// que j'utilise, il n'est pas obligatoire
struct Personne {
    std::string nom_;
    Sexe sexe_;
    int age_;
};

int main()
{
    Personne p1;
    // En C :
    // struct Personne p1;
    p1.nom_ = "Paul";
    p1.sexe_ = Sexe::Homme;
    // Avec l'énumération C :
    //p1.sexe_ = Homme;
    p1.age_ = 23;
    std::cout << p1.nom_ << " a " << p1.age_ << " ans\n";
    
    Personne p2{ "Anne", Sexe::Femme, 34 };
    Personne * pp = &p2;
    std::cout << (*pp).nom_ << " a " << pp->age_ << " ans\n";    
}
