/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°3
 *
 * TestExpression.cpp
 * c++ -std=c++20 -o TestExpression TestExpression.cpp Expression.cpp -lgtest -lpthread
 */

#include <sstream>
#include <utility>

#include <gtest/gtest.h>

#include "Expression.hpp"

TEST(ExpressionTest, AffichageNombre) {
    Nombre n(5);
    EXPECT_EQ(n.afficher(), "5");
}

TEST(ExpressionTest, AffichageVariable) {
    Variable v("x");
    EXPECT_EQ(v.afficher(), "x");
}

TEST(ExpressionTest, DerivationNombre) {
    Nombre n(5);
    Expression* derivee = n.deriver("x");
    EXPECT_EQ(derivee->afficher(), "0");
    delete derivee;
}

TEST(ExpressionTest, DerivationVariable) {
    Variable v("x");
    Expression* derivee1 = v.deriver("x");
    EXPECT_EQ(derivee1->afficher(), "1");
    delete derivee1;

    Expression* derivee2 = v.deriver("y");
    EXPECT_EQ(derivee2->afficher(), "0");
    delete derivee2;
}


 
int main( int argc, char * argv[] )
{
    ::testing::InitGoogleTest( &argc, argv );
    int result = RUN_ALL_TESTS();

    Nombre::afficherComptage();
    Variable::afficherComptage();

    return result;
}
