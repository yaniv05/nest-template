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

 
int main( int argc, char * argv[] )
{
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
