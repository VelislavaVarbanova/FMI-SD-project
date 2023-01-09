#include "calculator.h"
#include <iostream>
#include <sstream>

int main()
{
    std::stringstream s1 ("1234");
    std::stringstream s2 ("16");
    std :: string  s3 = "0";
    std:: string s4;
    Calculator a;
    Calculator b;
    Calculator c (s3);
    s1 >> a;
    s2 >> b;
    //Calculator d = a/b; 
    std::cout << " ";

    //d.convert16to10(string1);
    s4 = a.convert10to16();
    std :: cout << s4;
    // a = a-b;
    // std::cout << a;
    // Calculator g;
    // std::stringstream ss("200");
    // ss >> g;
    // std::cout << g;


    // if (a>=c)
    // {
    //     std:: cout << " 1 ";
    // }
    // if (c > a)
    // {
    //     std:: cout << " 2 ";
    // }
    // if (a > c)
    // {
    //     std:: cout << " 3 ";
    // }
    // if (a < c)
    // {
    //     std:: cout << " 4 ";
    // }
    // if (a == c)
    // {
    //     std::cout << " 5 ";
    // }
    std::cout<< std::endl;
}