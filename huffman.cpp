#include <iostream>
#include <fstream>
#include <string>
#include <stdbool.h>
#include <algorithm>

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
    ListNode(ListNode *node)
    {
        symbol = node->symbol;
        code = node->code;
        frequency_of_symbol = node->frequency_of_symbol;
        nextNode = nullptr;
        rightChild = nullptr;
        leftChild = nullptr;
    }
};

class List
{
    friend ListNode;

protected:
    ListNode *head;

public:
    ListNode *getHead()
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

    void addHead(ListNode *new_head)
    {
        new_head->nextNode = head;
        head = new_head;
    }

    void printList()
    {
        ListNode *current = head;

        while (current)
        {
            cout << current->symbol << " - " << current->frequency_of_symbol << endl;
            current = current->nextNode;
        }
    }

    void delHead()
    {
        head = head->nextNode;
    }

    bool findSym(string key) // метод нужен для того, чтобы понять, если ли символ в списке
    {
        ListNode *current = this->head;

        if (current == nullptr)
        {
            // cout<< "error findSym"<<endl;
            return false;
        }

        if (current->symbol == key) // если символ является головой списка
            return true;

        while (current && current->symbol != key) // если он не голова то ищем его
        {
            current = current->nextNode;
        }

        if (current && current->symbol == key) // если нашли то возвращает true
            return true;
        else
        {
            return false;
        }

        return false; // если не нашли то false
    }

    int getFreqSym(string key) // метод нужен для того, чтобы понять, если ли символ в списке
    {
        ListNode *current = this->head;

        if (current == nullptr)
        {
            // cout<< "error findSym"<<endl;
            return false;
        }

        if (current->symbol == key) // если символ является головой списка
            return current->frequency_of_symbol;

        while (current && current->symbol != key) // если он не голова то ищем его
        {
            current = current->nextNode;
        }

        if (current && current->symbol == key) // если нашли то возвращает true
            return current->frequency_of_symbol;
        else
        {
            return false;
        }

        return false; // если не нашли то false
    }

    ListNode *getNode(string key)
    {
        ListNode *current = this->head;

        if (current == nullptr)
        {
            // cout<< "error findSym"<<endl;
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
        if (head == nullptr)
            return 0;

        int size_of_list = 0;
        ListNode *current = head;
        while (current)
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
            cout << node->symbol << " - " << code << " - " << node->frequency_of_symbol <<  endl;
            return;
        }

        printHuffmanCodes(node->leftChild, code + "0");
        printHuffmanCodes(node->rightChild, code + "1");
    }

    string findHuffmanCode(ListNode *node, string key, string code)
    {
        if (node == nullptr)
            return "";

        if (node->symbol == key)
        {
            //cout << "found";
            return code;
        }

        string leftCode = findHuffmanCode(node->leftChild, key, code + "0");
        if (!leftCode.empty())
            return leftCode;

        string rightCode = findHuffmanCode(node->rightChild, key, code + "1");
        if (!rightCode.empty())
            return rightCode;

        return "";
    }

};

void print_vector(unsigned char vector)
{
    if (vector)
    {

        unsigned char mask;

        for (unsigned char ix_bit_ltr = 0, ix_bit_rtl = 7; ix_bit_ltr < 8; ix_bit_ltr++, ix_bit_rtl--)
        {
            mask = 1 << ix_bit_rtl; // сдвигаем маску на нужное количесто бит
            // с помощью & проверяем установлен бит или нет, если нет то выводим 0, если да то выводим 1
            printf("%d", (vector & mask) ? 1 : 0);
        }

        printf("\n");
    }
}

int main()
{
    ifstream myfile("mytext.txt"); //открываем файл
    size_t size_of_file = 0; 
    string my_text; //создаем строку

    while (!myfile.eof()) //пока не конец файла
    {
        getline(myfile, my_text); //считываем строку и записываем её в строку
        //cout << endl << my_text << endl;
    }
    size_of_file = my_text.length();


    List list;
    List listFreq;
    ListNode *current = list.getHead();
    ListNode *current_freq = listFreq.getHead();

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

    //этот кринж надо вынести в метод, или функцию, мне плохо становится когда я смотрю на это
    //создатется список частот
    for(int i = 0; i < size_of_file; i++) //в цикле будем создавать список частот символов
    {
        if(current_freq == nullptr)
        {
            string sym(1, my_text[i]); // Создание строки из символа(создаем строку именно так, потому что иначе строку из символа не создать)
            current_freq = new ListNode(sym, 1);
            listFreq.setHead(current_freq);
        }
        else
        {
            string sym(1, my_text[i]); // Создание строки из символа
            if(listFreq.findSym(sym))
            {
                ListNode *node = listFreq.getNode(sym);
                node->frequency_of_symbol++;
            }
            else
            {
                ListNode *new_node = new ListNode(sym, 1);
                listFreq.addHead(new_node);
            }
        }
    }

    list.insertionSort();
    listFreq.insertionSort();
    //list.printList();
    listFreq.printList();


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

    //list.printList();

    list.buildHuffmanCodes(list.getHead(), "");
    //list.printHuffmanCodes(list.getHead(), "");

    string code;
    //code = list.findHuffmanCode(list.getHead(), "T", "");
   // cout << code << endl;

    //здесь записываем строку нулей и единиц которые представляют последвательность бит после кодирования
    //эта строка будет использоваться для записи бит закодированного сообщения

    //тут записывается таблица
    ofstream file("code_text.txt");
    int freq = 0;
    char freq_to_sym;
    int size_of_listFreq = listFreq.sizeOfList();
    current_freq = listFreq.getHead();
    string stringFreq; 
    while(current_freq)
    {
        freq = listFreq.getFreqSym(current_freq->symbol);
        //cout<< freq << endl;
        file << current_freq->symbol;
        stringFreq.clear();
        while(freq != 0)
        {
            freq_to_sym = (freq % 10) + '0';
            stringFreq = stringFreq + freq_to_sym;
            //cout<< stringFreq << endl;
            //file << freq_to_sym;
            freq = freq / 10; 
        }
        //cout << stringFreq << endl;
        if(stringFreq.length() > 1)
        {
            reverse(stringFreq.begin(), stringFreq.end());
            //cout<<"хуй" << endl;
            //cout << stringFreq << endl;
            int j = stringFreq.length();
            int jx = 0;
            while(j > 0)
            {
                cout << "Write: " << stringFreq[jx] << endl;
                file << stringFreq[jx];
                jx++;
                j--;
            }
        }
        else if(stringFreq.length() == 1)
        {
            file << stringFreq;
        }

        current_freq = current_freq->nextNode;
    }

    file << "Tab";


    string code_text;
    for(int i = 0; i < size_of_file; i++)
    {
        string sym(1, my_text[i]);
        code = list.findHuffmanCode(list.getHead(), sym, "");
        code_text = code_text+code;
    }
   // cout<<"Code text: "<< code_text<< endl << endl;


    //записываем биты в файл
    unsigned char sym_to_write = 0;
    unsigned char mask = 0;

    size_t size_of_code_text = code_text.length();
    size_t lastBits = size_of_code_text % 8;

    if (file.is_open())
    {
        int i = 0;
        for (; i < size_of_code_text; i++)
        {
            string sym(1, code_text[i]);
            if (sym == "1")
            {
                
                mask = (1 << (8 - (i%8) - 1));
                sym_to_write |= mask;
            }

            if ( i != 0 && i % 8 == 0)
            {
                //print_vector(sym_to_write);
                file << sym_to_write;
                sym_to_write = 0;
            }
        }

        for (int j = 0; j < lastBits; j++)
        {
            string sym(1, code_text[(i-1)+j]);
            if (sym == "1")
            {
                mask = (1 << (8 - (j % 8) - 1));
                sym_to_write |= mask;
            }
        }
        //print_vector(sym_to_write);
        file << sym_to_write;
    }

    

    return 0;
}