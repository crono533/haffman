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


    list.printList();

    return 0;
}