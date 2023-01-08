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
      //we assume the list is empty
    Node* last_created = nullptr;
    Node* current = other.getFirstNode();
    while(current->next != nullptr) //we can directly parse with other_first because its a copy of the pointer to the first elem 
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
    last_created->next = new Node {current->data, nullptr, last_created};
    last = last_created->next;
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
        // subtractLasts = other.getLastNode()->data - this->last->data;
        // current1 = other.getLastNode()->prev;
        // current2 = this->last->prev;
    }
    Node* resultLast = new Node {subtractLasts, nullptr, nullptr};
    result.setLast(resultLast);
    while (current1 != nullptr || current2 != nullptr)
    {

       
        if (current2 == nullptr)
        {
            subtractLasts = current1->data - minus;
            minus = 0;
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
    if (resultLast->data == 0)
    {
        if (resultLast->next->data == 0)
        {

            while (resultLast->next->data == 0 && resultLast->next->next != nullptr)
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
    if (resultLast->data == 0)
    {
        Node* save = resultLast;
        resultLast = resultLast->next;
        resultLast->prev = nullptr;
        delete save;
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
    std::cout << "delitelq e ";
    Node* prnt3 = this->first;
    while (prnt3 != nullptr)
    {
        std:: cout << prnt3->data;
        prnt3 = prnt3->next;
    }
    std:: cout << std:: endl;
    std::cout << "delimoto e ";
    Node* prnt4 = other.getFirstNode();
    while (prnt4 != nullptr)
    {
        std:: cout << prnt4->data;
        prnt4 = prnt4->next;
    }
    

    if ((*this) < other)
    {
        Node* nullNode = new Node{0, nullptr, nullptr};
        Calculator result(nullNode);
        return result;
    }
    std::cout << " q ";
    Calculator result;
    Calculator midResult1;
    Node* current = this->first;
    int countSubtractions = 0;
    Node* nodeHelper = nullptr;
    Calculator multiplyDivisor(other.getFirstNode());
    
    Node* resultNode = new Node {current->data, nullptr, nullptr};
    midResult1.setFirst(resultNode);
    current = current->next;
    for (size_t i = 0; i < other.size() - 1; i++)
    {
        std::cout << " w ";
        Node* currentNode = new Node {current->data, nullptr, resultNode};
        resultNode->next = currentNode;
        resultNode = currentNode;
        current = current->next;
    }
    midResult1.setLast(resultNode);
    while (current != nullptr)
    {
        // std::cout << std:: endl << "mid result is ";
        // Node* prnt2 = midResult1.getFirstNode();
        // while (prnt2 != nullptr)
        // {
        //     std:: cout << prnt2->data;
        //     prnt2 = prnt2->next;
        // }

        if (nodeHelper != nullptr)
        {
            std::cout << " p ";
            //std :: cout << " crr " << current->data;
            Node* nextDigit = new Node {current->data, nullptr, midResult1.getLastNode()};
            midResult1.getLastNode()->next = nextDigit;
            midResult1.setLast(nextDigit);

            std::cout << std:: endl << "mid result is ";
            Node* prnt6 = midResult1.getFirstNode();
            while (prnt6 != nullptr)
            {
                std:: cout << prnt6->data;
                prnt6 = prnt6->next;
            }
        }
        
        std::cout << " Here ";
        if (midResult1 < multiplyDivisor)
        {
            std::cout << " v ";
            Node* plusDigit = new Node {current->data, nullptr, resultNode};
            resultNode->next = plusDigit;
            resultNode = plusDigit;
            current = current->next;
            midResult1.setLast(resultNode);
        }
        //std::cout << " here ";
        countSubtractions = 0;
        

        std::cout << std:: endl << "Mid result is ";
        Node* prnt0 = midResult1.getFirstNode();
        while (prnt0 != nullptr)
        {
            std:: cout << prnt0->data;
            prnt0 = prnt0->next;
        }
        std:: cout << std:: endl;
        std::cout << "Delimoto e ";
        Node* prnt = multiplyDivisor.getFirstNode();
        while (prnt != nullptr)
        {
            std:: cout << prnt->data;
            prnt = prnt->next;
        }
        std:: cout << std:: endl;

        Node* nullNode = new Node{0, nullptr, nullptr};
        Calculator newResult (nullNode);
        while (midResult1 >= multiplyDivisor)
        {
            // std :: cout <<std:: endl<< " m ";
            
            // std::cout <<  " new result is ";
            // Node* prnt5 = newResult.getFirstNode();
            // while (prnt5 != nullptr)
            // {
            //     std:: cout << prnt5->data;
            //     prnt5 = prnt5->next;
            // }
            //  std::cout <<  " multy is ";
            // Node* prnt77 = multiplyDivisor.getFirstNode();
            // while (prnt77 != nullptr)
            // {
            //     std:: cout << prnt77->data;
            //     prnt77 = prnt77->next;
            // }
            // std::cout <<  "  mid result is ";
            // Node* prnt7 = midResult1.getFirstNode();
            // while (prnt7 != nullptr)
            // {
            //     std:: cout << prnt7->data;
            //     prnt7 = prnt7->next;
            // }
            // newResult = newResult + multiplyDivisor;
            countSubtractions++;
            midResult1 = midResult1 - multiplyDivisor;
            
            // std::cout << " " << countSubtractions << " ";
            
            std::cout << std::endl << " " << countSubtractions << " ";
            std::cout <<  " mid result is ";
            Node* prnt2 = midResult1.getFirstNode();
            while (prnt2 != nullptr)
            {
                std:: cout << prnt2->data;
                prnt2 = prnt2->next;
            }
            // midResult1 = newResult;
        }
        // countSubtractions--;
        // midResult1 = midResult1 + multiplyDivisor - newResult;
        std :: cout << "probaA ";
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
        Node* prntR = result.getFirstNode();

        std::cout << std::endl << " result is ";
        while (prntR != nullptr)
        {
            std::cout << prntR->data;
            prntR=prntR->next;
        }
    }
    
    
    std::cout << " end ";
    //Node* oneNode = new Node {1, nullptr,nullptr};
    

    //*//----------------------------//

    
        // std::cout << std:: endl << "mid result is ";
        // Node* prnt5 = midResult1.getFirstNode();
        // while (prnt5 != nullptr)
        // {
        //     std:: cout << prnt5->data;
        //     prnt5 = prnt5->next;
        // }
        // std :: cout << "  "<< std :: endl;
        // std::cout << "delimoto e ";
        // Node* prnt2 = multiplyDivisor.getFirstNode();
        // while (prnt2 != nullptr)
        // {
        //     std:: cout << prnt2->data;
        //     prnt2 = prnt2->next;
        // }
        // midResult1 = midResult2;
        //std:: cout << " b ";
    
     
    
    std::cout << " t ";
    // while (current != nullptr)
    // {
    //     countSubtractions = 0;
    //     std::cout << " f ";
    //     Node* nextDigit = new Node {current->data, nullptr, midResult1.getLastNode()};
    //     midResult1.getLastNode()->next = nextDigit;
    //     midResult1.setLast(nextDigit);

    //     std::cout << current->data << " ";
    //     std::cout << std:: endl << "Mid result is ";
    //     Node* prnt4 = midResult1.getFirstNode();
    //     while (prnt4 != nullptr)
    //     {
    //         std:: cout << prnt4->data;
    //         prnt4 = prnt4->next;
    //     }
    //     std::cout << " delimoto e ";
    //     Node* prnt8 = multiplyDivisor.getFirstNode();
    //     while (prnt8 != nullptr)
    //     {
    //         std:: cout << prnt8->data;
    //         prnt8 = prnt8->next;
    //     }

    //     if (midResult1 < other)
    //     {
    //         std::cout << " nn ";
    //         Node* plusDigit = new Node {current->data, nullptr, resultNode};
    //         resultNode->next = plusDigit;
    //         resultNode = plusDigit;
    //         current = current->next;
    //         midResult1.setLast(resultNode);
    //     }
    //     while (midResult1 >= multiplyDivisor)
    //     {
    //         midResult1 = midResult1 - multiplyDivisor;
    //         countSubtractions++;

    //         std::cout <<  "   " <<  countSubtractions << " ";
    //         // std::cout << " mid result is ";
    //         // Node* middd = midResult1.getFirstNode();
    //         // while (middd != nullptr)
    //         // {
    //         //     std:: cout << middd->data;
    //         //     middd = middd->next;
    //         // }
    //         // std :: cout << "  "<< std :: endl;
    //     }
    //     std :: cout << " proba2 ";
    //     Node* setResult = new Node {countSubtractions, nullptr, result.getLastNode()};
    //     result.getLastNode()->next = setResult;
    //     result.setLast(setResult); 

    //     current = current->next;  
    // }

    return result;
}