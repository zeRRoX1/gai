#include <iostream>

using namespace std;

struct violation
{
    char* violat;
    violation* next;
};

struct node
{
    int number;
    node* parent;
    node* left;
    node* right;

    violation* head;
    violation* tail;
};

class database
{
private:
    int size;
    node* root;

public:
    database();
    ~database();

    void Add(int);
    void PrintAll(node*, int);
    void PrintNumber(int);
    void PrintRangeNumber(node*);
    node* ReturnRoot();
    void DeleteAll(node* temp);
};

database::database()
{
    root = NULL;
    size = 0;
}


//деструктор
database::~database()
{
    DeleteAll(root);
}

//метод удаления всего
void database::DeleteAll(node* temp)
{
    if (temp)
    {
        DeleteAll(temp->left);
        DeleteAll(temp->right);
        delete temp;
    }
}

//метод добавления 
void database::Add(int value)
{
    node* temp = new node;
    temp->number = value;

    temp->left = temp->right = temp->parent = NULL;

    if (!root)
        root = temp;
    else
    {
        node* tmp1 = root;
        node* tmp2 = NULL;

        while (tmp1)
        {
            tmp2 = tmp1;
            if (value < tmp1->number)
                tmp1 = tmp1->left;
            else if (value > tmp1->number)
                tmp1 = tmp1->right;
            else
                break;
        }

        if (value < tmp2->number) {
            tmp2->left = temp;
            temp->parent = tmp2;
        }
        else if (value > tmp2->number) {
            tmp2->right = temp;
            temp->parent = tmp2;
        }
        else
            cout << "равны\n";
    }
}

//печать полной базы данных
void database::PrintAll(node* temp, int value)
{
    if (temp)
    {
        PrintAll(temp->left, value + 1);
        cout << "Номер машины: " << temp->number << endl;
        cout << "Нарушение: " << endl;
        PrintAll(temp->right, value + 1);
    }
}

//печать по номеру
void database::PrintNumber(int num)
{
    if (root)
    {
        node* temp = root;
        int k = 0;
        while (temp)
        {
            if (num == temp->number)
            {
                k = 0;
                break;
            }
            if (num < temp->number) {
                ++k;
                temp = temp->left;
            }
            else if (num > temp->number) {
                ++k;
                temp = temp->right;
            }
        }
        if (k == 0)
        {
            cout << "Номер машины: " << temp->number << endl;
            cout << "Нарушение: " << endl;
        }
        else
            cout << "Машины с таким номером в базе нету\n";

    }
}

int main()
{
    setlocale(LC_ALL, "Russian");


    database bd;

    for (int i = 0; i < 6; ++i)
        bd.Add(rand() % 9000 + 1000);

    bd.PrintAll(bd.ReturnRoot(), 0);
    cout << endl << endl;
    bd.Add(5555);
    bd.PrintAll(bd.ReturnRoot(), 0);
    cout << endl << endl;

    cout << "Введите номер машины: ";
    int num;
    cin >> num;
    bd.PrintNumber(num);
}