#include <iostream>
#include <map>
#include <vector>
#include <stdbool.h>
#include <iterator>
#include <fstream>
#include <string>

using namespace std;

class TreeNode{     //класс узел для дерева хаффмана
    public:
        string sym;
        int key;
        TreeNode *left, *right;
    public:
        TreeNode();
        TreeNode(string , int );
        TreeNode(TreeNode *, TreeNode *); //конструктор для конкатенации символов и сложения ключей (частот) 
};

TreeNode::TreeNode()
{
    left = NULL;
    right = NULL;
}

TreeNode::TreeNode(string _sym, int _key)
{
    sym = _sym; // это переменная для хранения символа
    key = _key; // это переменная для хранения частот
    left = NULL; right = NULL;
}

TreeNode::TreeNode(TreeNode *_left, TreeNode *_right)  //создание узла где мы конкатинируем сиволы и частоты 
{
    sym = _left->sym + _right->sym; // конкатенируем строки
    key = _left->key + _right->key; // складываем частоты

    left = _left; // устанавливаем левого потомка
    right = _right; // устанавливаем правого потомка
}

class ListNode // класс узел для списка
{
    public:
        TreeNode *treeNode;
        ListNode *nextNode;
    public:

        bool addAfterGiven(ListNode **list_head, int search_key, TreeNode **node_to_insert) //метод для добалвения элемента списка после заданного
        {
            if(list_head)
            {
                if(*list_head)
                {
                    ListNode *new_node;
                    new_node->treeNode = *node_to_insert;
                    new_node->nextNode = NULL;

                    ListNode *current = *list_head;
                    for(; current && current->treeNode->key != search_key && current->nextNode->treeNode->key <= search_key; current = current->nextNode);

                    new_node->nextNode = current->nextNode;
                    current->nextNode = new_node;

                    return true;
    
                }else return false;

            }else return false;
        }

        void dellByValue(ListNode **list_head, int search_key) //метод для удаления узла списка (доделать)
        {
            
        }
};
