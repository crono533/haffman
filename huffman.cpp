#include <iostream>
#include <fstream>
#include <string>
#include <stdbool.h>

using namespace std;

class ListNode // класс для узла списка, список нужен для того чтобы создать таблицу частот появления символов
{
public:
    string symbol;
    string code;
    size_t frequency_of_symbol;
    ListNode *nextNode;
    ListNode *rightChild;
    ListNode *leftChild;

public:
    // string getListSym()
    // {
    //     return symbol;
    // }

    // void setListSym(string key)
    // {
    //     symbol = key;
    // }

    // ListNode getListNext()
    // {
    //     return *nextNode;
    // }

    // void setListNode(ListNode *node)
    // {
    //     nextNode = node;
    // }

    ListNode(string sym, size_t frequency)
    {
        symbol = sym;
        frequency_of_symbol = frequency;
        nextNode = nullptr;
        rightChild = nullptr;
        leftChild = nullptr;
    }

    ListNode(ListNode *nodeLeft, ListNode *nodeRight)
    {
        symbol = nodeLeft->symbol + nodeRight->symbol;
        frequency_of_symbol = nodeLeft->frequency_of_symbol + nodeRight->frequency_of_symbol;
        nextNode = nullptr;
        leftChild = nodeLeft;
        rightChild = nodeRight;
    }
};

class List
{
    friend ListNode;

protected:
    ListNode *head;

public:

    ListNode* getHead()
    {
        return head;
    }

    void setHead(ListNode *new_node)
    {
        head = new_node;
    }

    List()
    {
        head = nullptr;
    }

    List(ListNode *node)
    {
        head = node;
    }

    bool addAfterGiven(int search_frequency, ListNode **node_to_insert)
    {
        if (node_to_insert)
        {
            if (*node_to_insert)
            {
                ListNode *new_node = *node_to_insert;
                ListNode *current = head;
                ListNode *current_next = nullptr;

                if (head == nullptr || head->frequency_of_symbol >= search_frequency) // Здесь изменено условие сравнения
                {
                    new_node->nextNode = head;
                    head = new_node;
                }
                else
                {
                    while (current->nextNode != nullptr && current->nextNode->frequency_of_symbol <= search_frequency) // Здесь изменено условие сравнения
                    {
                        current = current->nextNode;
                    }

                    current_next = current->nextNode;
                    current->nextNode = new_node;
                    new_node->nextNode = current_next;
                }
                return true;
            }
        }

        return false;
    }

    void addHead(ListNode* new_head)
    {
        new_head->nextNode = head;
        head = new_head;
    }

    void printList()
    {
        ListNode *current = head;

        while(current)
        {
            cout << current->symbol << " - " << current->frequency_of_symbol << endl;
            current = current->nextNode;
        }
    }

    void delHead()
    {
        head = head->nextNode;
    }

    bool findSym(string key) //метод нужен для того, чтобы понять, если ли символ в списке
    {
        ListNode *current = this->head;
        
        if(current == nullptr)
        {
            //cout<< "error findSym"<<endl;
            return false;
        }

        if(current->symbol == key) //если символ является головой списка
            return true;

        while(current && current->symbol != key) //если он не голова то ищем его 
        {
            current = current->nextNode;
        }

        if(current && current->symbol == key) //если нашли то возвращает true 
            return true;
        else
        {
            return false;
        }

        return false; //если не нашли то false
    }

    ListNode* getNode(string key)
    {
        ListNode *current = this->head;

        if(current == nullptr)
        {
            //cout<< "error findSym"<<endl;
            return nullptr;
        }

        if (current->symbol == key) // если символ является головой списка
            return current;
        
        while (current && current->symbol != key) // если он не голова то ищем его
        {
            current = current->nextNode;
        }

        if (current && current->symbol == key) // если нашли то возвращаем узел
            return current;

         return nullptr; // если не нашли, возвращаем nullptr
    }

    void insertionSort()
    {
        if (head == nullptr || head->nextNode == nullptr)
            return;

        List sortedList;
        ListNode *current = head;

        while (current != nullptr)
        {
            ListNode *nextNode = current->nextNode;
            sortedList.addAfterGiven(current->frequency_of_symbol, &current);
            current = nextNode;
        }

        head = sortedList.head;
    }

    int sizeOfList()
    {
        if(head == nullptr)
            return 0;
        
        int size_of_list = 0;
        ListNode *current = head;
        while(current)
        {
            size_of_list++;
            current = current->nextNode;
        }
        return size_of_list;
    }

    void buildHuffmanCodes(ListNode *node, string code)
    {
        if (node == nullptr)
            return;

        if (node->leftChild == nullptr && node->rightChild == nullptr)
        {
            node->code = code;
            return;
        }

        buildHuffmanCodes(node->leftChild, code + "0");
        buildHuffmanCodes(node->rightChild, code + "1");
    }

    void printHuffmanCodes(ListNode *node, string code)
    {
        if (node == nullptr)
            return;

        if (node->leftChild == nullptr && node->rightChild == nullptr)
        {
            cout << node->symbol << " - " << code << endl;
            return;
        }

        printHuffmanCodes(node->leftChild, code + "0");
        printHuffmanCodes(node->rightChild, code + "1");
    }
};


int main()
{
    ifstream myfile("mytext.txt"); //открываем файл
    size_t size_of_file = 0; 
    string my_text; //создаем строку

    while (!myfile.eof()) //пока не конец файла
    {
        getline(myfile, my_text); //считываем строку и записываем её в строку
        cout << endl << my_text << endl;
    }
    size_of_file = my_text.length();


    List list;
    ListNode *current = list.getHead();

    for(int i = 0; i < size_of_file; i++) //в цикле будем создавать список частот символов
    {
        if(current == nullptr)
        {
            string sym(1, my_text[i]); // Создание строки из символа(создаем строку именно так, потому что иначе строку из символа не создать)
            current = new ListNode(sym, 1);
            list.setHead(current);
        }
        else
        {
            string sym(1, my_text[i]); // Создание строки из символа
            if(list.findSym(sym))
            {
                ListNode *node = list.getNode(sym);
                node->frequency_of_symbol++;
            }
            else
            {
                ListNode *new_node = new ListNode(sym, 1);
                list.addHead(new_node);
            }
        }
    }

    list.insertionSort();

    list.printList();

    //строим дерево Хаффмана
    int size_of_list = list.sizeOfList();
    current = list.getHead();
    while(list.sizeOfList() != 1)
    {
        current = list.getHead();
        ListNode *nodeToInsert = new ListNode(current, current->nextNode);
        list.addAfterGiven(nodeToInsert->frequency_of_symbol, &nodeToInsert);
        list.delHead();
        list.delHead();
    }

    list.printList();

    list.buildHuffmanCodes(list.getHead(), "");
    list.printHuffmanCodes(list.getHead(), "");


    return 0;
}