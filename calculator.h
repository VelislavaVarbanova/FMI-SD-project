#include "Node.h"
#include <string>


class Calculator
{
private:

    Node* first;
    Node* last;
    
public:
    Calculator();
    Calculator(const std::string&);
    Calculator(Node*);
    ~Calculator();
    void clear();

    Node* getFirstNode()const;
    Node* getLastNode()const;

    void setFirst(Node*);
    void setLast(Node*);

    std::string convert10to16();
    std::string convert16to10(const std::string&);

    Calculator operator+(const Calculator&);
    Calculator operator-(const Calculator&);
    bool operator>(const Calculator&);
    Calculator operator*(const Calculator&);
};
