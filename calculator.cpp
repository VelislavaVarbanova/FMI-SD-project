#include "calculator.h"
#include <exception>
#include <iostream>

Node* Calculator :: getFirstNode() const
{
    return first;
}

Node* Calculator :: getLastNode() const
{
    return last;
}

void Calculator :: setFirst(Node* first)
{
    this->first = first;
}

void Calculator :: setLast(Node* last)
{
    this->last = last;
}

Calculator :: Calculator() : first(nullptr), last(nullptr) {}

Calculator :: Calculator(const std::string& string)
{
    first = new Node(string[0]-'0');
    last = first;
    for (int i = 1; i < string.size(); i++)
    {
        Node* newLast = new Node(string[i]-'0', nullptr, last);
        last->next = newLast;
        last = newLast;
    }
}

Calculator :: Calculator(Node* node)
{
    first = node;
    while (node->next != nullptr)
    {
        node = node->next;
    }
    last = node;
}

Calculator& Calculator::operator=(const Calculator& other)
{
    if (this != &other)
    {
        clear();
        copy(other);
    }
    return *this;
}
void Calculator::copy(const Calculator& other)
{
    if (other.getFirstNode() == nullptr)
    {
        first = nullptr;
        last = nullptr;
        return;
    }
    Node* last_created = nullptr;
    Node* current = other.getFirstNode();
    while(current->next != nullptr) 
    {
        Node* new_node = new Node {current->data, nullptr, last_created};
        if (last_created != nullptr)
        {
            last_created->next = new_node;
        }
        else
        {
            first = new_node;
        }
        last_created = new_node;
        current = current->next;
    }
    if (last_created != nullptr)
    {
        last_created->next = new Node {current->data, nullptr, last_created};
        last = last_created->next;
        return;
    }
    first = new Node{current->data, nullptr, nullptr};
    last = first;
}

void Calculator :: clear()
{
    Node* save = first;
    while (first != nullptr)
    {
        save = first;
        first = first->next;
        delete save;
    }
}

// Calculator :: ~Calculator()
// {
//     clear();
// }

std::string Calculator :: convert10to16()
{
    Calculator N (this->first);
    Node* nullNode = new Node{0, nullptr, nullptr};
    Calculator zero(nullNode);
    std::string result;
    int b = 16;     //b is for base and it's 16 because we are cinverting to hex 
    Node* bNode = new Node {1 , nullptr, nullptr}; 
    Calculator B;
    B.setFirst(bNode);
    B.setLast(new Node {6, nullptr, bNode});
    bNode->next = B.getLastNode();
    while (!(N == zero))
    {
        Calculator D = N / B;
        Calculator R = N % B;
        char r;
        if (R.getFirstNode()->data > 1 && R.getFirstNode()->data <= 9)
        {
            r = R.getFirstNode()->data;
            r = r + '0';
        }
        else if (R.getFirstNode()->data == 1)
        {
            switch (R.getLastNode()->data)
            {
            case 0:
                r = 'A';
                break;
            case 1:
                r = 'B';
                break;
            case 2:
                r = 'C';
                break;
            case 3:
                r = 'D';
                break;
            case 4:
                r = 'E';
                break;
            case 5:
                r = 'F';
                break;
            default: throw std::logic_error ("wrong number!");
                break;
            }
        }else
        {
            throw std::logic_error ("wrong number!");
        }
        result = r + result;
        N = D;
    }
    return result;
}

// Calculator Calculator :: convert16to10(const std::string& string)
// {
//     size_t n = string.size();
//     int b = 10 ;     //b is for base and it's 10 because we are cinverting to decimal 
//     Node* bNode = new Node {1 , nullptr, nullptr};  
//     Calculator B;
//     B.setFirst(bNode);
//     B.setLast(new Node {0, nullptr, bNode});
//     bNode->next = B.getLastNode();
//     Calculator result(new Node {0, nullptr, nullptr});

//     for (size_t i = 0; i < string.size(); i++)
//     {
//         n--;            //formula is result = result + (b^n * d)
//         Calculator calculatorD;
//         char d = string.front();
//         switch (d)
//         {
//         case 1 ... 9 :
//             Node* nodeD = new Node {int(d),nullptr,nullptr};
//             calculatorD.setFirst(nodeD);
//             calculatorD.setLast(nodeD);
//             break;
//         case 'A': case 'a' :
//             Node* nullNode = new  Node {0, nullptr, nullptr};
//             Node* nodeA = new Node(1,nullNode,nullptr);
//             nullNode->prev = nodeA;
//             calculatorD.setFirst(nodeA);
//             calculatorD.setLast(nullNode);
//             break;
//         case 'B': case 'b':
//             Node* oneNode = new  Node {1, nullptr, nullptr};
//             Node* nodeB = new Node(1,oneNode,nullptr);
//             oneNode->prev = nodeB;
//             calculatorD.setFirst(nodeB);
//             calculatorD.setLast(oneNode);
//             break;
//         case 'C': case 'c':
//             Node* nodeTwo = new  Node {2, nullptr, nullptr};
//             Node* nodeC = new Node(1,nodeTwo,nullptr);
//             nodeTwo->prev = nodeC;
//             calculatorD.setFirst(nodeC);
//             calculatorD.setLast(nodeTwo);
//             break;
//         case 'D': case 'd':
//             Node* nodeTree = new  Node {3, nullptr, nullptr};
//             Node* nodeD = new Node(1,nodeTree,nullptr);
//             nodeTree->prev = nodeD;
//             calculatorD.setFirst(nodeD);
//             calculatorD.setLast(nodeTree);
//             break;
//         case 'E': case 'e':
//             Node* nodeFour = new  Node {4, nullptr, nullptr};
//             Node* nodeE = new Node(1,nodeFour,nullptr);
//             nodeFour->prev = nodeE;
//             calculatorD.setFirst(nodeE);
//             calculatorD.setLast(nodeFour);
//             break;
//         case 'F': case 'f':
//             Node* nodeFive = new  Node {5, nullptr, nullptr};
//             Node* nodeF = new Node(1,nodeFive,nullptr);
//             nodeFive->prev = nodeF;
//             calculatorD.setFirst(nodeF);
//             calculatorD.setLast(nodeFive);
//             break;
//         default: throw std::logic_error ("not a hex number!");
//             break;
//         }
//         for (size_t i = 0; i < n; i++)
//         {
//             B = B * B;
//         }
//         result = result + (calculatorD * B );
//     }
//     return result;
// }

Calculator Calculator :: operator+(const Calculator& other)
{
    Calculator result;
    int sumOfLasts = this->last->data + other.getLastNode()->data;
    Node* resultLast = new Node {sumOfLasts % 10, nullptr, nullptr};
    result.setLast(resultLast);
    bool plus1 = false;
    if (sumOfLasts > 9)
    {
        plus1 = true;
    }
    
    Node* current1 = this->last->prev;
    Node* current2 = other.getLastNode()->prev; 
    while (current1 != nullptr || current2 != nullptr)
    {
        if (current1 == nullptr)
        {
            sumOfLasts = current2->data + plus1;
        }
        else if (current2 == nullptr)
        {
            sumOfLasts = current1->data + plus1;
        }else 
        {
            sumOfLasts = current1->data + current2->data + plus1;
        }
        Node* currentResult = new Node {sumOfLasts % 10, resultLast, nullptr};
        resultLast->prev = currentResult;
        resultLast = currentResult;

        plus1 = false;
        if (sumOfLasts > 9)
        {
            plus1 = true;
        }
        if (current1 != nullptr)
        {
            current1 = current1->prev;
        }
        if (current2 != nullptr)
        {
            current2 = current2->prev;
        }
    }
    if (plus1 == true)
    {
        Node* firstDigit = new Node {1, resultLast, nullptr};
        resultLast->prev = firstDigit;
        resultLast = firstDigit;
    }
    result.setFirst(resultLast);
    return result;
}

Calculator Calculator :: operator-(const Calculator& other)
{
    Calculator result;
    int subtractLasts;
    Node* current1;
    Node* current2;
    int minus = 0;
    if ((*this) >= other)
    {
        if (this->last->data < other.getLastNode()->data)
        {
            subtractLasts = this->last->data + 10 - other.getLastNode()->data;
            minus++;
        }else
        {
            subtractLasts = this->last->data - other.getLastNode()->data;
        }
        current1 = this->last->prev;
        current2 = other.getLastNode()->prev;
    }else
    {
        throw std::logic_error ("Big Numbers support only POSITIVE numbers!");
    }
    Node* resultLast = new Node {subtractLasts, nullptr, nullptr};
    result.setLast(resultLast);
    while (current1 != nullptr || current2 != nullptr)
    {

       
        if (current2 == nullptr)
        {
            if (current1->data - minus < 0)
            {
                subtractLasts = current1->data + 10 - minus;
                minus = 1;
            }
            else
            {
                subtractLasts = current1->data - minus;
                minus = 0;
            }
        }else 
        {
            if (current1->data - minus < current2->data )
            {
                subtractLasts = current1->data + 10 - current2->data - minus;
                minus = 1;
            
            }else
            {
                subtractLasts = current1->data - current2->data - minus;
                minus = 0;
            }
        }
        Node* currentResult = new Node {subtractLasts % 10, resultLast, nullptr};
        resultLast->prev = currentResult;
        resultLast = currentResult;
        if (current1 != nullptr)
        {
            current1 = current1->prev;
        }
        if (current2 != nullptr)
        {
            current2 = current2->prev;
        }
    }
    if (resultLast->data == 0 && resultLast->next != nullptr)
    {
        if (resultLast->next != nullptr && resultLast->next->data == 0 )
        {
            while (resultLast->next != nullptr && resultLast->next->data == 0 )
            {
                Node* save = resultLast;
                resultLast = resultLast->next;
                resultLast->prev = nullptr;
                delete save;
            }
            if (resultLast->next != nullptr )
            {
                Node* save = resultLast;
                resultLast = resultLast->next;
                resultLast->prev = nullptr;
                delete save;
            }
            
        }
        else
        {
            Node* save = resultLast;
            resultLast = resultLast->next;
            resultLast->prev = nullptr;
            delete save;
        }
    }
    result.setFirst(resultLast);
    return result;
}

bool Calculator :: operator>(const Calculator& other)
{
    Node* crr1 = this->first;
    Node* crr2 = other.getFirstNode();
    int biggerNum = 0;
    while (crr1 != nullptr && crr2 != nullptr)
    {  
        if (biggerNum == 0)
        {
            if (crr1->data > crr2->data)
            {
                biggerNum = 1;
            }
            if (crr1->data < crr2->data)
            {
                biggerNum = 2;
            }
        }
        crr1 = crr1->next;
        crr2 = crr2->next;
    }

    if (crr1 == nullptr && crr2 != nullptr)
    {
        return false;
    }
    else if (crr2 == nullptr && crr1 != nullptr)
    {
        return true;
    }
    else      // размера е равен
    {
        if (biggerNum == 1)
        {
            return true;
        }
        return false;
    }
}

bool Calculator :: operator>=(const Calculator& other)
{
    Node* crr1 = this->first;
    Node* crr2 = other.getFirstNode();
    int biggerNum = 0;
    while (crr1 != nullptr && crr2 != nullptr)
    {  
        if (biggerNum == 0)
        {
            if (crr1->data > crr2->data)
            {
                biggerNum = 1;
            }
            if (crr1->data < crr2->data)
            {
                biggerNum = 2;
            }
        }
        crr1 = crr1->next;
        crr2 = crr2->next;
    }

    if (crr1 == nullptr && crr2 != nullptr)
    {
        return false;
    }
    else if (crr2 == nullptr && crr1 != nullptr)
    {
        return true;
    }
    else      // размера е равен
    {
        if (biggerNum == 1 || biggerNum == 0)
        {
            return true;
        }
        return false;
    }
}

bool Calculator :: operator<(const Calculator& other)
{
    return !((*this)>=other);
}

Calculator Calculator :: operator*(const Calculator& other)
{
    Node* nullNode = new Node{0, nullptr, nullptr};
    Calculator result(nullNode);
    if (this->first->data == 0 || other.getFirstNode()->data == 0) //taka opravqme problema s pechataneto na 0000
    {
        return result;
    }
    Node* current1;
    Node* current2;
    if ((*this) > other)
    {
        current1 = this->last;
        current2 = other.getLastNode();
    }
    else
    {
        current1 = other.getLastNode();
        current2 = this->last;
    }
    Node* lastDigit = current1;
    int carryCurrent = 0;
    int moveLeft = 0;
    
    while (current2 != nullptr)
    {
        Node* resultNode = nullptr;
        while (current1 != nullptr)
        {
            int multiplyLasts = (current2->data * current1->data + carryCurrent) ;
            Node* currentResult = new Node {multiplyLasts % 10, resultNode, nullptr};
            if (resultNode != nullptr)
            {
                resultNode->prev = currentResult;
            }
            resultNode = currentResult;
            carryCurrent = multiplyLasts / 10;            
            current1 = current1->prev;
        }

        if (carryCurrent > 0 )
        {
            Node* firstDigit = new Node {carryCurrent, resultNode, nullptr};
            resultNode->prev = firstDigit;
            resultNode = firstDigit;
        }

        Calculator midResult(resultNode);

        for (int i = 0; i < moveLeft; i++)
        {
            Node* move = new Node {0, nullptr, midResult.getLastNode()};
            midResult.getLastNode()->next = move;
            midResult.setLast(move);
        }

        result = result + midResult; 

        for (int i = 0; i < moveLeft; i++)
        {
            Node* moveL = new Node {0, nullptr, midResult.getLastNode()};
            midResult.getLastNode()->next = moveL;
            midResult.setLast(moveL);
        }

        moveLeft++;
        carryCurrent = 0;
        current1 = lastDigit;
        current2 = current2->prev; 
    }
    return result;
}

size_t Calculator :: size() const
{
    Node* crr = first;
    size_t size = 0;
    while (crr != nullptr)
    {
        size++;
        crr = crr->next;
    }
    return size;
}

Calculator Calculator :: operator/(const Calculator& other)
{   
    if ((*this) < other)
    {
        Node* nullNode = new Node{0, nullptr, nullptr};
        Calculator result(nullNode);
        return result;
    }
    Calculator result;
    Calculator midResult;
    Node* current = this->first;
    int countSubtractions = 0;
    Node* nodeHelper = nullptr;
    Calculator multiplyDivisor(other.getFirstNode());
    
    Node* resultNode = new Node {current->data, nullptr, nullptr};
    midResult.setFirst(resultNode);
    current = current->next;
    for (size_t i = 0; i < other.size() - 1; i++)
    {
        Node* currentNode = new Node {current->data, nullptr, resultNode};
        resultNode->next = currentNode;
        resultNode = currentNode;
        current = current->next;
    }
    midResult.setLast(resultNode);
    while (current != nullptr)
    {
        if (nodeHelper != nullptr)
        {
            Node* nextDigit = new Node {current->data, nullptr, midResult.getLastNode()};
            midResult.getLastNode()->next = nextDigit;
            midResult.setLast(nextDigit);
            current = current->next;
        }
        if (midResult < multiplyDivisor)
        {
            Node* plusDigit = new Node {current->data, nullptr, resultNode};
            resultNode->next = plusDigit;
            resultNode = plusDigit;
            current = current->next;
            midResult.setLast(resultNode);
        }
        countSubtractions = 0;
        while (midResult >= multiplyDivisor)
        {
            midResult = midResult - multiplyDivisor;
            countSubtractions++;
        }
        Node* setResult = new Node {countSubtractions, nullptr, nodeHelper};
        if (nodeHelper != nullptr)
        {
            nodeHelper->next = setResult;
        }
        if (nodeHelper == nullptr)
        {
            result.setFirst(setResult);
        }
        nodeHelper = setResult;
        result.setLast(setResult);
    }
    if (current == nullptr && midResult.size() == multiplyDivisor.size())
    {
        while (midResult >= multiplyDivisor)
        {
            midResult = midResult - multiplyDivisor;
            countSubtractions++;
        }
        Node* setResult = new Node {countSubtractions, nullptr, nullptr};
        result.setFirst(setResult);
        result.setLast(setResult);
    }
    return result;
}

Calculator Calculator :: operator%(const Calculator& other)
{
    Calculator result;
    Calculator otherCoppy(other.getFirstNode());
    Calculator dividend = (*this) / otherCoppy;
    Calculator toSubtract = dividend*otherCoppy;
    result = (*this) - toSubtract;
    return result;
}

std::ostream& operator<<(std::ostream& out, Calculator& calc)
{
    Node* curr = calc.getFirstNode();
    while(curr != nullptr)
    {
        out << curr->data;
        curr = curr->next;
    }
    return out;
}

std::istream& operator>>(std::istream& in, Calculator& calc)
{
    std::string string;
    in >> string;
    Node* new_node = new Node(string[0]-'0');
    calc.setFirst(new_node);
    calc.setLast(calc.getFirstNode());
    for (int i = 1; i < string.size(); i++)
    {
        Node* newLast = new Node(string[i]-'0', nullptr, calc.getLastNode());
        calc.getLastNode()->next = newLast;
        calc.setLast(newLast);
    }
    return in;
}

bool Calculator :: operator== (const Calculator& other)
{
    return (!((*this) > other) && !((*this) < other));
}