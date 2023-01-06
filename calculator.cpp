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

Calculator :: ~Calculator()
{
    clear();
}

// std::string Calculator :: convert10to16()
// {
    
// }

// Calculator Calculator :: convert16to10(const std::string& string)
// {

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
    if ((*this) >= other)
    {
        subtractLasts = this->last->data - other.getLastNode()->data;
        current1 = this->last->prev;
        current2 = other.getLastNode()->prev;
    }else
    {
        throw std::logic_error ("Big Numbers support only POSITIVE numbers!");
        // subtractLasts = other.getLastNode()->data - this->last->data;
        // current1 = other.getLastNode()->prev;
        // current2 = this->last->prev;
    }
    Node* resultLast = new Node {abs(subtractLasts), nullptr, nullptr};
    result.setLast(resultLast);
    bool minus1 = false;
    if (subtractLasts < 0)
    {
        minus1 = true;
    }
    
    while (current1 != nullptr || current2 != nullptr)
    {
        if (current2 == nullptr)
        {
            subtractLasts = current1->data - minus1;
        }else 
        {
            subtractLasts = current1->data - current2->data - minus1;
        }
        Node* currentResult = new Node {subtractLasts %10, resultLast, nullptr};
        resultLast->prev = currentResult;
        resultLast = currentResult;

        minus1 = false;
        if (subtractLasts < 0)
        {
            minus1 = true;
            resultLast->data += 10;
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

Calculator Calculator :: operator*(const Calculator& other)
{
    Node* nullNode = new Node{0, nullptr, nullptr};
    Calculator result(nullNode);
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