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

TEST(AdditionTest, AffichageAddition) {
    Expression* gauche = new Nombre(3);
    Expression* droite = new Nombre(4);
    Expression* addition = new Addition(gauche, droite);

    EXPECT_EQ(addition->afficher(), "(3 + 4)");

    delete gauche;
    delete droite;
    delete addition;
}

TEST(AdditionTest, DerivationAddition) {
    Expression* gauche = new Variable("x");
    Expression* droite = new Nombre(5);
    Expression* addition = new Addition(gauche, droite);

    Expression* derivee = addition->deriver("x");
    EXPECT_EQ(derivee->afficher(), "(1 + 0)");

    delete gauche;
    delete droite;
    delete addition;
    delete derivee;
}


TEST(MultiplicationTest, AffichageMultiplication) {
    Expression* gauche = new Nombre(3);
    Expression* droite = new Nombre(4);
    Expression* multiplication = new Multiplication(gauche, droite);

    EXPECT_EQ(multiplication->afficher(), "(3 * 4)");

    delete gauche;
    delete droite;
    delete multiplication;
}

TEST(MultiplicationTest, DerivationMultiplication) {
    Expression* gauche = new Variable("x");
    Expression* droite = new Nombre(5);
    Expression* multiplication = new Multiplication(gauche, droite);

    Expression* derivee = multiplication->deriver("x");
    EXPECT_EQ(derivee->afficher(), "((1 * 5) + (x * 0))");

    delete gauche;
    delete droite;
    delete multiplication;
    delete derivee;
}

 
int main( int argc, char * argv[] )
{
    ::testing::InitGoogleTest( &argc, argv );
    int result = RUN_ALL_TESTS();

    Nombre::afficherComptage();
    Variable::afficherComptage();

    return result;
}
