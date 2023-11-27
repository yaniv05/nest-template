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



