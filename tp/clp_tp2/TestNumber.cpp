/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - TP n°2
 *
 * TestNumber.cpp
 * c++ -std=c++20 -o TestNumber Number.cpp TestNumber.cpp -lgtest -lpthread
 */

#include <exception>
#include <sstream>
#include <string>
#include <utility>

#include <cstdlib>
#include <ctime>


#include <gtest/gtest.h>

#include "Number.hpp"

 
TEST( TestNumber, TestNumber0 )
{
    Number n{ 0 };
    std::ostringstream os;
    os << n;
    EXPECT_EQ( os.str(), "0" );
}
 
TEST( TestNumber, TestNumber12345678 )
{
    Number n{ 12345678 };
    std::ostringstream os;
    os << n;
    EXPECT_EQ( os.str(), "12345678" );
}
 
TEST( TestNumber, TestNumberBig )
{
    Number n{ 12345123451234512345UL };
    std::ostringstream os;
    os << n;
    EXPECT_EQ( os.str(), "12345123451234512345" );
}

TEST( TestNumber, TestNumberRandom )
{
    auto r{ std::rand() };
    Number n{ static_cast< unsigned long >( r )};
    std::ostringstream os;
    os << n;
    EXPECT_EQ( os.str(), std::to_string( r ));
}

TEST(TestNumber, CopyConstructor) {
    Number original(12345);
    Number copy(original);

    std::ostringstream os1, os2;
    os1 << original;
    os2 << copy;
    
    EXPECT_EQ(os1.str(), "12345");
    EXPECT_EQ(os2.str(), os1.str());
}

TEST(TestNumber, CopyAssignmentOperator) {
    Number original(67890);
    Number assigned(12345);
    assigned = original;

    std::ostringstream os1, os2;
    os1 << original;
    os2 << assigned;

    EXPECT_EQ(os1.str(), "67890");
    EXPECT_EQ(os2.str(), os1.str());
}

TEST(TestNumber, SelfAssignment) {
    Number number(98765);
    number = number;

    std::ostringstream os;
    os << number;
    
    EXPECT_EQ(os.str(), "98765");
}

int main( int argc, char * argv[] )
{
    std::srand( std::time( nullptr ));
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
