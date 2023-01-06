#include "calculator.h"
#include <iostream>

int main()
{
    std::string string1 = "1234";
    std::string string2 = "4321";
    std :: string string3 = "0";
    Calculator a (string1);
    Calculator b (string2);
    Calculator c (string3);
    Calculator d = a*b;
    Node* current = d.getFirstNode();
        // Node* node = new Node (0);
        // Calculator d (node);
        // Node* current = d.getFirstNode();
    while (current != nullptr)
    {
        std:: cout << current->data;
        current = current->next;
    }

    
    // if (a>=b)
    // {
    //     std:: cout << " 1 ";
    // }
    // if (b > a)
    // {
    //     std:: cout << " 2 ";
    // }if (a > b)
    // {
    //     std:: cout << " 3 ";
    // }
    // if (a > a)
    // {
    //     std:: cout << " 4 ";
    // }
    
    
    std::cout<< std::endl;
}