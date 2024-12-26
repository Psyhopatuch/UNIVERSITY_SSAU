#include <iostream>
#include <fstream>

using namespace std;

bool key = false; // Ключ глобально для доступа из всей программы

class LIST; // Объявим класс LIST, чтобы сделать его другом ITEM

// Класс узла списка
class ITEM
{
    int val;    // Целочисленная переменная--поле класса
    ITEM *next; // Указатель на следующий элемент--поле класса
    ITEM *prev; // Указатель на предыдущий элемент--поле класса

public:
    ITEM(int v = 0) : val(v), next(nullptr), prev(nullptr) {} // Конструктор

    // Дружественные классу функции и класс
    friend ostream &operator<<(ostream &, LIST &);
    friend ITEM *split(ITEM *);
    friend ITEM *merge(ITEM *, ITEM *);
    friend void merge_sort(ITEM *&);
    friend void bubble_sort(LIST &L);
    friend class LIST; // Для доступа к приватным полям этого класса из дружественного
};

// Класс списка
class LIST
{
    ITEM *head; // Поле-ссылка на голову списка, список без головы не получится
    ITEM *last; // Поле-ссылка на хвост списка, поле используется только для push_back в список
public:         
    // Конструктор и деструктор
    LIST();
    ~LIST();

    // Методы класса
    void swap(ITEM *, ITEM *);
    int size();
    void push_back(int);
    
    // Дружественные функции
    friend ostream &operator<<(ostream &, LIST &);
    friend istream &operator>>(istream &, LIST &);
    friend void bubble_sort(LIST &L);
    friend void sort(LIST &list, bool key);
};

// Метод класса LIST, для добавления эл. в конец
void LIST::push_back(int val)
{
    ITEM *n = new ITEM(val); // Новый контейнер
    if (head)                // Если голова не nullptr, то свяжем новый контейнер с концом списка и передвинем конец списка на этот контейнер
    {
        n->prev = last;
        last->next = n;
        last = n;
    }
    else // Контейнер--голова списка и конец
    {
        head = last = n;
    }
}

// Метод, возврящающий длинну списка
int LIST::size()
{

    ITEM *p = head; // Будем двигать указатель по списку
    int size = 0;   // пока он не станет nullptr и вернём
    while (p)       // число переходов по списку
    {
        size++;
        p = p->next;
    }
    return size;
}

// Конструктор списка по умолчанию
LIST::LIST()
{
    head = nullptr;
    last = nullptr;
}

// Деструктор списка
LIST::~LIST()
{

    if (head)
    {
        ITEM *p = head;

        while (head->next)
        {
            p = head->next;
            delete head;
            head = p;
        }
        delete head;
    }
}

// Перегрузка оператора ввода
istream &operator>>(istream &fin, LIST &L)
{
    fin >> key;
    int value;
    while (!fin.eof())
    {
        fin >> value;       // Считали значение
        L.push_back(value); // Поместили в конец
    }
    return fin;
}

// Перегрузка оператора вывода
ostream &operator<<(ostream &fout, LIST &L)
{
    if (!L.head)
    {
        fout << 0;
        return fout;
    }

    ITEM *p = L.head;
    fout << L.size() << ' ';
    while (p)
    {
        fout << p->val << " ";
        p = p->next;
    }
    return fout;
}

// swap
void LIST::swap(ITEM *obj_1, ITEM *obj_2)
{
    // swap пустых элементов или самого с собой
    if (!obj_1 || !obj_2 || obj_1 == obj_2)
        return;

    // Проверка на головы и перестановка
    if (obj_1 == head)
        head = obj_2;
    else if (obj_2 == head)
        head = obj_1;

    // Обмен полей next у двух переставляемых элеметов методом 'трёх стаканов'
    ITEM *temp = obj_1->next;
    obj_1->next = obj_2->next;
    obj_2->next = temp;

    // Обмен полей prev у двух элементов, следующих за переставляемыми, если таковые существуют
    if (obj_1->next)
        obj_1->next->prev = obj_1;
    if (obj_2->next)
        obj_2->next->prev = obj_2;

    // Обмен полей prev у двух переставляемых элеметов методом трёх стаканов
    temp = obj_1->prev;
    obj_1->prev = obj_2->prev;
    obj_2->prev = temp;

    // Обмен полей next у двух элементов, предыдущих переставляемыми, если таковые существуют
    if (obj_1->prev)
        obj_1->prev->next = obj_1;
    if (obj_2->prev)
        obj_2->prev->next = obj_2;
}

ITEM *split(ITEM *head) // Быстрый-медленный указатель для нахождения головы второго подсписка
{
    ITEM *second_ptr = head;
    ITEM *first_ptr = head->next;

    while (first_ptr) // Быстрый указатель продвигается на два контейнера каждый раз, медленный--на один
    {
        first_ptr = first_ptr->next;
        if (first_ptr)
        {
            second_ptr = second_ptr->next;
            first_ptr = first_ptr->next;
        }
    }

    ITEM *temp = second_ptr->next;
    second_ptr->next->prev = nullptr; // Разделим входящий список на два и вернём голову второго
    second_ptr->next = nullptr;       //
    return temp;
}

// Рекурсия слияния двух отсортированных списков
ITEM *merge(ITEM *left, ITEM *right)
{
    // Если левый список пуст, вернём правый
    if (left == nullptr)
    {
        return right;
    }

    // Если правый список пуст, вернём левый
    if (right == nullptr)
    {
        return left;
    }

    // Слияние двух непустых списков
    if (left->val <= right->val)
    {
        left->next = merge(left->next, right); // Слияние рекурсивное левого и правого списков
        left->next->prev = left;
        left->prev = nullptr;
        return left;
    }
    else
    {
        right->next = merge(left, right->next); // Слияние рекурсивное правого и левого списков
        right->next->prev = right;
        right->prev = nullptr;
        return right;
    }
}

// Рекурсивное тело сортировки слиянием
void merge_sort(ITEM *&head)
{
    // Если узел списка один или их нет, то массив отсортирован
    if (head == nullptr || head->next == nullptr)
    {
        return;
    }

    // Делим список на два функцией split()
    ITEM *head_2 = (split(head));

    // Два полученных списка отсортируем рекурсивно
    merge_sort(head);
    merge_sort(head_2);

    // Объединим отсортированные списки
    head = merge(head, head_2);
}

// Сортировка пузырём
void bubble_sort(LIST &L)
{
    bool sorted = false; //Флажок, отсортирован или нет

    while (!sorted) // Пока не встретилась итерация без перестановок
    {
        ITEM *p = L.head; // Указатель на голову списка
        sorted = true;
        while (p->next) // Пока p->next!=0
        {
            if (p->val > p->next->val) 
            {
                L.swap(p, p->next); // Особенность ф-ии свап, после вызова контейнер, на который указывал 'p' и будет следующим
                sorted = false; // Встретилась перестановка => массив не отсортирован
            }
            else
            {
                p=p->next; // А если свап не случился, то подвинем указатель на следующий контейнер
            }
        }
    }
}

// Вынесем выбор сортировки по ключу в отдельную функцию для инкапсуляции
void sort(LIST &list, bool key)
{

    switch (key)
    {
    case (false):
        merge_sort(list.head); // Сортировка слиянием
        break;
    case (true):
        bubble_sort(list); // Сортировка пузырьком
    }
}

int main()
{
    LIST list;

    ifstream fin("input.txt", ios_base::in);
    ofstream fout("output.txt");

    if (!fin.is_open() && !fout.is_open()) // Потоки не открылись--переидём к возвращению значений
        return 1;    

    fin >> list;     // С помощью перегрузки оператора считаем список
    sort(list, key); // Сортировка по ключу
    fout << list;    // С помощью перегрузки оператора выводим список
    // Будет удалён через деструктор
    return 0;
}
