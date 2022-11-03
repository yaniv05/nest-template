/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°6
 * Dominique Marcadet - 2022 - CC BY-SA
 *
 * sac.cpp
 *
 * Compilation :
 *     c++ -std=c++20 -o new new.cpp
 * Exécution :
 *     ./new
 */



#include <iostream>
#include <vector>

struct A {
    int a_;
    A( int a ) : a_{ a } { std::cout << "A constructor\n"; }
    void * operator new( size_t s );
    void   operator delete( void * p );
};

size_t allocator_index{ 0 };
char buf[5 * sizeof( A )];

void * A::operator new( size_t s ) {
    std::cout << "A::operator new\n";
    return buf + allocator_index++ * sizeof( A );
}

void A::operator delete( void * p ) {
    std::cout << "A::operator delete\n";
}

int main()
{
    std::vector< A * > v;
    for( int i{ 0 }; i < 5; ++i ) {
        v.push_back( new A{ i });
    }
    for( int i{ 0 }; i < 5; ++i ) {
        delete v[i];
    }
}

