#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <stdbool.h>
#include <iterator>
#include <fstream>
#include <string>

using namespace std;

class Node{     //класс узел для дерева хаффмана
    public:
        string sym;
        int key;
        Node *left, *right;
        Node();
        Node(string , int );
        Node(Node *, Node *); //конструктор для конкатенации символов и сложения ключей (частот) 
};

Node::Node()
{
    left = NULL;
    right = NULL;
}

Node::Node(string _sym, int _key)
{
    sym = _sym; // это переменная для хранения символа
    key = _key; // это переменная для хранения частот
    left = NULL; right = NULL;
}

Node::Node(Node *_left, Node *_right)  //создание узла где мы конкатинируем сиволы и частоты 
{
    sym = _left->sym + _right->sym; // конкатенируем строки
    key = _left->key + _right->key; // складываем частоты

    left = _left; // устанавливаем левого потомка
    right = _right; // устанавливаем правого потомка
}

