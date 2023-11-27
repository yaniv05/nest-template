/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°3
 *
 * Expression.cpp
 */

#include <iostream>
#include <string>
#include <utility>

#include "Expression.hpp"

std::ostream& operator<<(std::ostream& os, const Expression& expr) {
    os << expr.afficher();
    return os;
}

int Nombre::instancesCrees = 0;
int Nombre::instancesDetruites = 0;

int Variable::instancesCrees = 0;
int Variable::instancesDetruites = 0;