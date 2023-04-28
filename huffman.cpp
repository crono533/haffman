#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <stdbool.h>
#include <iterator>
#include <fstream>

using namespace std;

class Node{
    public:
        char sym;
        int key;
        Node *left, *right;
        Node();
        Node(char , int );
        Node(Node *, Node *);
};

Node::Node()
{
    left = NULL;
    right = NULL;
}

Node::Node(char symbol, int code)
{
    sym = symbol;
    key = code;
    left = NULL; right = NULL;
}
