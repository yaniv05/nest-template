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
#include <cmath>


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

    Number(std::string s) : first_(nullptr) {
        if (s.empty()) {
            throw std::invalid_argument("Empty string is not a valid input");
        }

        const size_t len = s.length();
        for (size_t i = 0; i < len; ++i) {
            if (!std::isdigit(s[i])) {
                throw std::invalid_argument("Invalid character in the input string");
            }
        }

        unsigned int count = 0;
        unsigned long currentDigitValue = 0;

        for (int i = len - 1; i >= 0; --i) {
            currentDigitValue += (s[i] - '0') * std::pow(10, count);

            if (++count == static_cast<unsigned int>(std::log10(number_base)) || i == 0) {
                addDigitToFront(currentDigitValue);
                currentDigitValue = 0;
                count = 0;
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

    void add(unsigned int i) {
        // Inverser la liste pour commencer par le chiffre le moins significatif
        reverseList();

        Digit* current = first_;
        DigitType carry = 0;
        while (i > 0 || carry) {
            // Si nous atteignons la fin de notre nombre, ajoutez un nouveau chiffre à la fin
            if (!current) {
                addDigitToEnd(0);
                current = first_;
                while (current && current->next_) {
                    current = current->next_;
                }
            }

            // Calculer la somme et la retenue
            DigitType sum = current->digit_ + (i % number_base) + carry;
            current->digit_ = sum % number_base;
            carry = sum / number_base;

            // Progresser vers le chiffre suivant
            if (current) {
                current = current->next_;
            }
            i /= number_base;
        }

        // Inverser à nouveau la liste pour retrouver l'ordre initial
        reverseList();
    }

void multiply(unsigned int multiplier) {
    Number result(0);  // Initialize a result number to zero.

    Number original(*this); 

    int shift = 0;  

    while (multiplier > 0) {
        unsigned int currentMultiplierDigit = multiplier % number_base;

        Number tempProduct(original);
        tempProduct = tempProduct.singleDigitMultiply(currentMultiplierDigit);

        for(int i = 0; i < shift; i++) {
            tempProduct.addDigitToEnd(0);
        }

        result.addNumber(tempProduct);  

        multiplier /= number_base;
        shift++;
    }

    *this = result;  
}


Number singleDigitMultiply(unsigned int d){
    reverseList();
    if (d == 0) {
        return Number(0);  // Multiplying by 0 always gives 0.
    }

    Number productNumber(0);   // Start with an empty number.
    unsigned int carry = 0;   // To handle any values that carry over when multiplying.

    Digit* currentDigit = first_;
    
    int i = 0;
    // Multiply each digit of the number by d.
    while (currentDigit || carry > 0) {
        unsigned int tempProduct = (currentDigit ? currentDigit->digit_ : 0) * d + carry;
        carry = tempProduct / number_base;  
        
        if(i){
            productNumber.addDigitToFront(tempProduct % number_base); 
        }else{
            productNumber.add(tempProduct % number_base);
        }

        currentDigit = currentDigit->next_;
        i++;
    }
    reverseList();
    return productNumber;
}



void addNumber(const Number& other) {
    // Reverse both numbers to start with the least significant digit.
    reverseList();
    Number otherCopy = other; 
    otherCopy.reverseList();

    Digit* currentThis = first_;
    Digit* currentOther = otherCopy.first_;
    Digit* prevThis = nullptr;  
    unsigned int carry = 0;

    if (currentThis && currentThis->digit_ == 0 && !currentThis->next_) {
        if (currentOther) {
            currentThis->digit_ = currentOther->digit_;
            currentOther = currentOther->next_;
        } else {
            currentThis->digit_ = 0;
            carry = 0;
        }
        prevThis = currentThis;
        currentThis = currentThis->next_;
    }

    while (currentThis || currentOther || carry) {
        unsigned int sum = carry;

        if (currentThis) {
            sum += currentThis->digit_;
        }

        if (currentOther) {
            sum += currentOther->digit_;
            currentOther = currentOther->next_;
        }

        carry = sum / number_base;

        if (currentThis) {
            currentThis->digit_ = sum % number_base;
            prevThis = currentThis;
            currentThis = currentThis->next_;
        } else {
            addDigitToEnd(sum % number_base);
            
            if (prevThis) {
                currentThis = prevThis->next_;
            } else {
                currentThis = first_;
            }
        }
    }

    reverseList();
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

    void reverseList() {
        Digit *prev = nullptr;
        Digit *current = first_;
        Digit *next = nullptr;

        while (current != nullptr) {
            next = current->next_;
            current->next_ = prev;
            prev = current;
            current = next;
        }
        first_ = prev;
    }





    Digit * first_;

};

Number factorial(unsigned int i);

std::istream & operator>>(std::istream & in, Number & n);


inline std::ostream & operator<<( std::ostream & out, const Number & n )
{
    n.print( out );
    return out;
}

#endif
