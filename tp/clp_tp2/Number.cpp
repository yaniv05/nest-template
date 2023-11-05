/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°2
 *
 * Number.cpp
 */

#include <exception>
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>

#include "Number.hpp"



Number factorial(unsigned int i) {
    Number result(1);
    for (unsigned int j = 1; j <= i; ++j) {
        result.multiply(j);
    }
    return result;
}

std::istream & operator>>(std::istream & in, Number & n) {
    std::string s;
    in >> std::ws;  

    while (in.good()) {
        int c{ in.get() };
        if (std::isdigit(c)) {
            s.push_back(static_cast<char>(c));
        } else {
            in.putback(c);
            break;
        }
    }

    if (!s.empty()) {
        n = Number(s);
    }

    return in;
}







