#include "Node.h"

Node :: Node(const int& a) : data(a), next(nullptr), prev(nullptr) {}

Node :: Node(const int& a, Node* next, Node* prev) : data(a), next(next), prev(prev) {}