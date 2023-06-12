#include <iostream>
#include <fstream>
#include <string>
#include <stdbool.h>

using namespace std;

class ListNode // класс для узла списка, список нужен для того чтобы создать таблицу частот появления символов
{
public:
    string symbol;
    size_t frequency_of_symbol;
    ListNode *nextNode;

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
    }
};

class List
{
    friend ListNode;

protected:
    ListNode *head;

public:
    List()
    {
        head = nullptr;
    }

    List(ListNode *node)
    {
        head = node;
    }

    bool addAfterGiven( int search_frequency, ListNode **node_to_insert) // метод для добалвения элемента списка после заданного
    {
        if(node_to_insert)
        {
            if(*node_to_insert)
            {
                ListNode *new_node = *node_to_insert; 
                ListNode *current = head;
                ListNode *current_next = nullptr;

                for(; (current != nullptr) && (current->nextNode->frequency_of_symbol <= search_frequency); current = current->nextNode);
                current_next = current->nextNode;

                current->nextNode = new_node;
                new_node->nextNode = current_next;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
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



    return 0;
}