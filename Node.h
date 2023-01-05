struct Node
{
    int data;
    Node* next;
    Node* prev;

public:
    Node(const int& a);
    Node(const int& a, Node* next, Node* prev);
};