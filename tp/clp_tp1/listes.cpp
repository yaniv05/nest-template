/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°1
 *
 * listes.cpp
 */

#include <iostream>
#include <forward_list>
#include <functional>
#include <limits>

#include <cstdlib>
#include <ctime>
#include <vector>

#include <iostream>
#include <vector>

#include <iostream>
#include <vector>

#include <iostream>
#include <vector>

// Nommons notre type pour plus de facilité d'écriture
using int_tab_t = std::vector<int>;

// Fonction pour afficher un tableau
void print_tab(const int_tab_t& tab) {
    std::cout << "[ ";
    for (int num : tab) {
        std::cout << num << " ";
    }
    std::cout << "]";
}

// Fonction de test demandée
void test_11() {
    std::cout << "*** test_11 ***" << std::endl;
    
    // Création du tableau
    const int_tab_t tab{ 1, -2, 3, -4, 5, -6 };
    
    // Affichage du tableau
    print_tab(tab);
    std::cout << std::endl; // Passage à la ligne pour avoir une sortie propre
}

int main()
{
    std::srand( std::time( nullptr ));

    test_11();
    return 0;
}

