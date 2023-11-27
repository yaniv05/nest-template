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

    /**
     * Dérive l'expression par rapport à une variable donnée.
     * 
     * @param var Le nom de la variable par rapport à laquelle dériver.
     * @return Une nouvelle instance d'Expression qui représente la dérivée.
     *         Retourne une expression constante (0) si l'expression ne dépend pas de la variable.
     *         L'allocation mémoire pour la nouvelle expression est dynamique et doit être gérée par le récepteur.
     */
    
    virtual ~Expression() {}
    virtual std::string afficher() const = 0;
    virtual Expression* clone() const = 0;
    virtual Expression* deriver(const std::string& var) const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Expression& expr);
private:
};


class Nombre : public Expression {
    int valeur;
    static int instancesCrees;
    static int instancesDetruites;

    public:
        Nombre(const Nombre& other) : valeur(other.valeur) {
            instancesCrees++;
        }

        Nombre(int val) : valeur(val) {
            instancesCrees++;
        }
        ~Nombre() override {
            instancesDetruites++;
        }

        Nombre* clone() const override {
            return new Nombre(*this);
        }

        int getValeur() const {
            return valeur;
        }

        std::string afficher() const override {
            return std::to_string(valeur);
        }

        Expression* deriver(const std::string& var) const override {
            return new Nombre(0); // La dérivée d'un nombre constant est toujours 0
        }

        static void afficherComptage() {
            std::cout << "Nombre - Créés: " << instancesCrees 
                    << ", Détruits: " << instancesDetruites << std::endl;
        }
};

class Variable : public Expression {
    std::string nom;
    static int instancesCrees;
    static int instancesDetruites;

    public:
        Variable(const std::string& nom) : nom(nom) {
            instancesCrees++;
        }
        Variable(const Variable& other) : nom(other.nom) {
            instancesCrees++;
        }
        ~Variable() override {
            instancesDetruites++;
        }

        Variable* clone() const override {
            return new Variable(*this);
        }

        std::string getNom() const {
            return nom;
        }

        std::string afficher() const override {
            return nom;
        }

        Expression* deriver(const std::string& var) const override {
            if (nom == var) {
                return new Nombre(1); // d(var)/d(var) = 1
            } else {
                return new Nombre(0); // d(autre_var)/d(var) = 0
            }
        }

        static void afficherComptage() {
            std::cout << "Nombre - Créés: " << instancesCrees 
                    << ", Détruits: " << instancesDetruites << std::endl;
        }

};

class Operation : public Expression {
protected:
    Expression* gauche;
    Expression* droite;

public:
    Operation(Expression* g, Expression* d) 
        : gauche(g->clone()), droite(d->clone()) {}

    ~Operation() {
        delete gauche;
        delete droite;
    }

    // Constructeur de copie
    Operation(const Operation& autre)
        : gauche(autre.gauche->clone()), droite(autre.droite->clone()) {}

    virtual std::string afficher() const = 0;
    virtual Expression* deriver(const std::string& var) const = 0;
    virtual Expression* clone() const = 0;

};

class Addition : public Operation {
public:
    Addition(Expression* gauche, Expression* droite) 
        : Operation(gauche, droite) {}

    // Méthode pour afficher l'addition
    std::string afficher() const override {
        return "(" + gauche->afficher() + " + " + droite->afficher() + ")";
    }

    // Méthode pour dériver l'addition
    Expression* deriver(const std::string& var) const override {
        return new Addition(gauche->deriver(var), droite->deriver(var));
    }

    // Méthode pour cloner l'objet
    Expression* clone() const override {
        return new Addition(*this);
    }
};

class Multiplication : public Operation {
public:
    Multiplication(Expression* gauche, Expression* droite) 
        : Operation(gauche, droite) {}

    // Méthode pour afficher la multiplication
    std::string afficher() const override {
        return "(" + gauche->afficher() + " * " + droite->afficher() + ")";
    }

    // Méthode pour dériver la multiplication
    Expression* deriver(const std::string& var) const override {
        // Règle du produit : (u*v)' = u'*v + u*v'
        return new Addition(
            new Multiplication(gauche->deriver(var), droite->clone()),
            new Multiplication(gauche->clone(), droite->deriver(var))
        );
    }

    // Méthode pour cloner l'objet
    Expression* clone() const override {
        return new Multiplication(*this);
    }
};





#endif
