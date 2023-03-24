#include "calculator.h"
#include <iostream>
#include <sstream>

int main()
{
    std::stringstream s1 ("13");
    std::stringstream s2 ("0");
    Calculator a;
    Calculator b;
    s1 >> a;
    s2 >> b;
    Calculator d = a*b; 
    std:: cout << d;




    // std:: string s4;
    //d.convert16to10(string1);
    // s4 = a.convert10to16();
    // std :: cout << s4;

    std::cout<< std::endl;
}