#include <iostream>
#include <fstream>

using namespace std;

// Класс очереди(Шаблон, интересно попробовать), написан на основе односвязного списка, в значении узла хранит что угодно
template <typename Type> // Шаблонный аргумент Type
class QUEUE
{
    // Класс узла очереди
    class QUEUE_ITEM
    {
        Type val;                                         // Значение контейнера шаблонного типа
        QUEUE_ITEM *next;                                 // Указатель на следующий элемент--поле класса
        QUEUE_ITEM(Type v) : val(v), next(nullptr) {}     // Конструктор по умолчанию
        friend QUEUE;                                     // Для доступа к полям этого класса из дружественного
    };
    QUEUE_ITEM *head;                   // Поле-ссылка на голову очереди
    QUEUE_ITEM *last;                   // Поле-ссылка на хвост очереди, нужно для push, чтобы не бегать по очереди
public:                                 // Квалификатор доступа

    // Конструктор и деструктор
    QUEUE() : head(nullptr), last(nullptr){}; // Конструктор по умолчанию
    ~QUEUE()                                  // Деструктор
    {
        if (head) // Будем последовательно удалять элементы с начала, двигая голову
        {
            QUEUE_ITEM *ptr = head;

            while (head->next)
            {
                ptr = head->next;
                delete head;
                head = ptr;
            }
            delete head;
        }
    };

    // Методы класса
    void push(Type obj) // Метод класса, отвечающий за добавление эл-тов в конец очереди
    {
        QUEUE_ITEM *item = new QUEUE_ITEM(obj); // Выделим память под новый контейнер
        if (head)                               // Eсли голова есть,
        {
            last->next = item; // то добавим элемент в конец
            last = last->next; // и передвинем конец очереди
        }
        else
        {
            last = head = item; // Если головы нет, то элемент--голова
        }
    };

    Type get() // Метод класса, отвечающий за извлечение эл-тов из начала очереди
    {
        if (head->next) // Если следующий за головой элемент существует
        {
            Type temp = head->val;        // Создадим временную переменную, хранящую значение контейнера
            QUEUE_ITEM *const ptr = head; // Константный указатель на голову
            head = head->next;            // Передвинем голову
            delete ptr;                   // Удалим контейнер
            return temp;                  // Вернём сохранённое ранее значение
        }
        else
            return head->val; // Осталась только голова--вернём значение, удалится деструктором
    };

    bool empty() // Метод, возвращающий ложь, если очередь содержит элементы и возвр. ноль в противных случаях
    {
        return !head;
    }
};

class BIN_TREE
{
    class TREE_NODE
    {
        long int val;                                                        // Значение узла
        TREE_NODE *left;                                                // Ссылка на левый потомок
        TREE_NODE *right;                                               // Ссылка на правый потомок
        TREE_NODE(int v = 0) : val(v), left(nullptr), right(nullptr) {} // Конструктор по умолчанию
        friend class BIN_TREE; // Для доступа к полям этого класса из дружественного
        friend void print(BIN_TREE::TREE_NODE *root, ostream &fout);
        friend void get_reflected_tree(BIN_TREE::TREE_NODE*);
    };

    TREE_NODE *root; // Ссылка на узел-корень

    void deleter(TREE_NODE *node) // Метод класса, рекурсивное удаление дерева
    {
        if (node->left)           // Если существует левый потомок
            deleter(node->left);  // Рекурсия по левому поддереву
        if (node->right)          // Если существует правый потомок
            deleter(node->right); // Рекурсия по правому поддереву
        delete node;              // Удаление последнего узла
    }

public:                           // Квалификатор доступа
    BIN_TREE() : root(nullptr){}; // Конструктор по умолчанию
    ~BIN_TREE()                   // Деструктор с написанной ранее рекурсивной функцией
    {
        deleter(root);
    }

    // Методы класса
    void push(int val) // Добавляет элемент в дерево по ширине
    {
        TREE_NODE *item = new TREE_NODE(val); // Выделим память и инициализируем узел дерева значением аргумента функции
        if (!root)                            // Нет корня дерева
        {
            root = item; // Теперь новый элемент корень дерева
            return;      // Элемент вставлен, переход к возвращению значений
        }
        QUEUE<TREE_NODE *> FiFo; // Объявим очередь
        FiFo.push(root);         // Поместим корень в очередь
        while (!FiFo.empty())    // Пока очередь не пуста
        {
            TREE_NODE *cur = FiFo.get();
            if (!cur->left)
            {
                cur->left = item;
                return; // Элемент вставлен, переход к возвращению значений
            }
            else if (!cur->right)
            {
                cur->right = item;
                return; // Элемент вставлен, переход к возвращению значений
            }
            FiFo.push(cur->left); // Если оба потомка не пустые внесём их в очередь рекурсивно
            FiFo.push(cur->right);
        }
    }
    // Дружественные функции
    friend ostream &operator<<(ostream &fout, BIN_TREE &obj);
    friend istream &operator>>(istream &, BIN_TREE &);
    friend void get_reflected_tree(BIN_TREE &obj);
    friend void get_reflected_tree(BIN_TREE::TREE_NODE*);
    friend void print(BIN_TREE::TREE_NODE *root, ostream &fout);
};

void get_reflected_tree(BIN_TREE::TREE_NODE*node) // Функция, отражающая дерево зеркально
{
    if(!node)return;                    // Условие выхода из рекурсии
    struct BIN_TREE::TREE_NODE* temp;   // Временный указатель
    get_reflected_tree(node->left);     // Рекурсия по левому потомку
    get_reflected_tree(node->right);    // Рекурсия по правому потомку
    temp = node->left;                  // Поменяем местами левое и правое поддерево
    node->left = node->right;           // с помощью временного указателя
    node->right = temp;
}

void get_reflected_tree(BIN_TREE &tree){get_reflected_tree(tree.root);} //Оболочка предыдущей функции для инкапсуляции

// Перегрузка оператора ввода
istream &operator>>(istream &fin, BIN_TREE &obj)
{
    long int temp; // Переменная для считывания целых чисел из потока
    while (!fin.eof())
    {
        fin >> temp;
        obj.push(temp);
    }
    return fin; // Вернём поток
}

// Перегрузка оператора вывода
ostream &operator<<(ostream &fout, BIN_TREE &obj)
{
    print(obj.root, fout); // Функция вывода
    return fout; // Вернём поток
}

void print(BIN_TREE::TREE_NODE *root, ostream &fout)
{
    if (!root) return;              // Условие выхода из рекурсии

    fout << root->val << " ";       // Вывод в поток

    print(root->left, fout);        // Рекурсия по левому потомку
    print(root->right, fout);       // Рекурсия по правому потомку
}

int main()
{
    ifstream fin("input.txt");              // Откроем поток ввода
    ofstream fout("output.txt");            // Откроем поток вывода

    if (!fin.is_open() && !fout.is_open())  // Потоки не открылись--переидём к возвращению значений
        return 1;    

    BIN_TREE tree;                          // Объявим дерево
    fin >> tree;                            // Считаем из файла, с помощью перегрузки оператора
    get_reflected_tree(tree);               // Отразим дерево
    fout << tree;                           // Выведем в поток перегрузкой оператора
    
    fin.close();                            // Закроем поток ввода
    fout.close();                           // Закроем поток вывода
    return 0;                               // Вернём ноль
}
