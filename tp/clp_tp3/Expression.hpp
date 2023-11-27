/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°3
 *
 * Expression.hpp
 */

#ifndef EXPRESSION_HPP_INCLUDED
#define EXPRESSION_HPP_INCLUDED

#include <iostream>
#include <string>
#include <utility>

class Expression {
public:
    // TODO
    virtual ~Expression() {}
    virtual Expression* clone() const = 0;
private:
};

class Nombre : public Expression {
    int valeur;

public:
    Nombre(int val) : valeur(val) {}
    Nombre(const Nombre& other) : valeur(other.valeur) {}
    ~Nombre() override {}

    Nombre* clone() const override {
        return new Nombre(*this);
    }

    int getValeur() const {
        return valeur;
    }
};

class Variable : public Expression {
    std::string nom;

public:
    Variable(const std::string& nom) : nom(nom) {}
    Variable(const Variable& other) : nom(other.nom) {}
    ~Variable() override {}

    Variable* clone() const override {
        return new Variable(*this);
    }

    std::string getNom() const {
        return nom;
    }

};




#endif
