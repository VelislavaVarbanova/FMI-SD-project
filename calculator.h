#include "Node.h"
#include <string>
#include <iostream>


class Calculator
{
private:

    Node* first;
    Node* last;

    void clear();
    size_t size () const;
    void copy(const Calculator& other);
    
public:
    Calculator();
    Calculator(const std::string&);
    Calculator(Node*);
    //~Calculator();

    Node* getFirstNode()const;
    Node* getLastNode()const;

    void setFirst(Node*);
    void setLast(Node*);

    std::string convert10to16();
    //Calculator convert16to10(const std::string&);

    Calculator operator+(const Calculator&);
    Calculator operator-(const Calculator&);
    Calculator operator*(const Calculator&);
    Calculator operator/(const Calculator&);
    Calculator operator%(const Calculator&);

    Calculator& operator=(const Calculator& other);
    bool operator>(const Calculator&);
    bool operator>=(const Calculator&);
    bool operator<(const Calculator&);
    bool operator==(const Calculator&);

    friend std::ostream& operator<<(std::ostream&, Calculator&);
    friend std::istream& operator>>(std::istream&, Calculator&);
};
