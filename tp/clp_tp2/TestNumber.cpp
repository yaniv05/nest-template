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

TEST(TestNumber, Addition) {
    Number num(12345);
    num.add(654);
    std::ostringstream os;
    os << num;
    EXPECT_EQ(os.str(), "12999");
}

TEST(TestNumber, SingleDigitMultiplication) {
    Number num(12345);

    Number product = num.singleDigitMultiply(7); // 12345 * 7 = 86315

    std::ostringstream os;
    os << product;

    EXPECT_EQ(os.str(), "86415");

    product = num.singleDigitMultiply(2); 
    os.str(""); 
    os << product;

    EXPECT_EQ(os.str(), "24690");

    product = num.singleDigitMultiply(1); 
    os.str(""); 
    os << product;

    EXPECT_EQ(os.str(), "12345");

    product = num.singleDigitMultiply(0); 
    os.str(""); 
    os << product;

    EXPECT_EQ(os.str(), "0");

}

TEST(TestNumber, AddNumber) {
    // Test case 1
    {
        Number num1(123450);
        Number num2(1478);
        num1.addNumber(num2);

        std::ostringstream os;
        os << num1;

        EXPECT_EQ(os.str(), "124928");
    }

    // Test case 2
    {
        Number num1(86415);
        Number num2(246900);
        num1.addNumber(num2);

        std::ostringstream os;
        os << num1;

        EXPECT_EQ(os.str(), "333315");
    }
        // Test case 3
    {
        Number num1(333315);
        Number num2(1234500);
        num1.addNumber(num2);

        std::ostringstream os;
        os << num1;

        EXPECT_EQ(os.str(), "1567815");
    }
    /*
    // Test case 3
    {
        Number num1(0);
        Number num2(5678);
        num1.addNumber(num2);

        std::ostringstream os;
        os << num1;

        EXPECT_EQ(os.str(), "5678");
    }
    */
}



TEST(TestNumber, Multiplication) {
    Number num(2340);
    num.multiply(100);
    std::ostringstream os;
    os << num;
    //EXPECT_EQ(os.str(), "1567815");
    EXPECT_EQ(os.str(), "234000");

}
/*
TEST( TestNumber, TestFactorial123 )
{
    std::ostringstream os;
    os << factorial( 123 );
    EXPECT_EQ( os.str(), "121463043670253296757662432418812958554542170884833823153289181618292"
                         "358923621676688311569606126402021707358352212940477825910915704116514"
                         "72186029519906261646730733907419814952960000000000000000000000000000" );
}
*/

TEST(TestNumber, StringConstructor) {

    Number num("12345");
    std::ostringstream os;
    os << num;
    EXPECT_EQ(os.str(), "12345");


    EXPECT_THROW(Number("12a45"), std::invalid_argument);
}

TEST(TestNumber, InputStreamOperator) {

    std::istringstream is("   98765  ");  
    Number num(0); 
    is >> num;
    std::ostringstream os;
    os << num;
    EXPECT_EQ(os.str(), "98765");

    std::istringstream is2("abc98765");
    Number num2(0);
    is2 >> num2;
    std::ostringstream os2;
    os2 << num2;
    EXPECT_EQ(os2.str(), "0"); 
}


int main( int argc, char * argv[] )
{
    std::srand( std::time( nullptr ));
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
