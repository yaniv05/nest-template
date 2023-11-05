/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°2
 *
 * Number.hpp
 */

#ifndef NUMBER_HPP_INCLUDED
#define NUMBER_HPP_INCLUDED

#include <iostream>
#include <string>
#include <utility>


class Number {
public:
    Number( unsigned long l )
        : first_(nullptr)
    {
        if (l == 0) {
            first_ = new Digit(0);
        } else {
            while (l > 0) {
                addDigitToFront(l % number_base);
                l /= number_base;
            }
        }
    }

    ~Number() {
        deleteDigits(first_);
    }

    void print( std::ostream & out ) const {
        if (first_) {
            first_->print(out);
        }
    }


    // Constructeur de copie
    Number(const Number& other)
        : first_(nullptr)
    {
        copyDigitsFrom(other.first_);
    }

    // Opérateur d'affectation par copie
    Number& operator=(const Number& other) {
        if (&other == this) {
            return *this;
        }
        deleteDigits(first_);
        first_ = nullptr;
        copyDigitsFrom(other.first_);
        return *this;
    }

private:
    using DigitType = unsigned int;
    static const DigitType number_base{ 10u };

    struct Digit {
        Digit(DigitType d)
            : digit_(d), next_(nullptr) {}

        ~Digit() {
            // Le destructeur de Digit n'a rien à faire ici car nous gérons la libération de la mémoire dans la fonction deleteDigits
        }

        DigitType digit_;
        Digit * next_;

        void print(std::ostream & out) const {
            out << digit_; // Afficher d'abord le chiffre courant
            if (next_) {
                next_->print(out);
            }
        }
    };

    void addDigitToFront(DigitType d) {
        Digit* newDigit = new Digit(d);
        newDigit->next_ = first_;
        first_ = newDigit;
    }

    void deleteDigits(Digit* current) {
        if (current) {
            deleteDigits(current->next_);
            delete current;
        }
    }

    void copyDigitsFrom(const Digit* source) {
        if (source) {
            addDigitToEnd(source->digit_);
            copyDigitsFrom(source->next_);
        }
    }

    void addDigitToEnd(DigitType d) {
        if (!first_) {
            first_ = new Digit(d);
            return;
        }
        Digit* current = first_;
        while (current->next_) {
            current = current->next_;
        }
        current->next_ = new Digit(d);
    }

    Digit * first_;
};

inline std::ostream & operator<<( std::ostream & out, const Number & n )
{
    n.print( out );
    return out;
}

#endif
