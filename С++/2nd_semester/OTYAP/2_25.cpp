//Вариант 25. Словом текста является последовательность букв русского алфавита длиной не более 6 символов. Найти те слова, в которых буквы алфавита образуют симметричную последовательность букв (палиндром).
//Идея--в этой работе два конечных автомата, первый разбивает текст на лексемы, второй--расширенный, определяет палиндромы. Второй автомат реализован в виде Машины Тьюринга
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
using namespace std;

bool rus_isalpha(char letter) // Аналог isalpha() для кириллицы
{
    return (letter >= 'А' && letter <= 'Я') || (letter >= 'а' && letter <= 'я') || letter == 'ё' || letter == 'Ё';
}

enum State
{       // the FSM states used to slise input text to lexems
    Sy, // Symbol
    Sl, // Slisers ' ', '\t', '/n'
    End, // End of text
    ERROR // Ошибка(неизвестные символы)
};

const State MATRIX[4][4] = {
    {State::Sy, State::Sl, State::End, State::ERROR},
    {State::Sy, State::Sl, State::End, State::ERROR},
    {State::End, State::End, State::End,State::End},
    {State::ERROR, State::Sl, State::End,State::ERROR}
    };

enum StateTM
{       // the Turing Machine states
    S,  // Start
    R,  // Right
    S2, // Start from end
    L,  // Left
    E,  // Error
    F   // Finish(exit)
};

const int ST = 6;
const int INP = 4;

// 0-isalpha
// 1-' ', '\t', '\n'
// 2-not a symbol
// 3-'\0'
const StateTM MATRIX_TM[ST][INP] = {
    {StateTM::R, StateTM::F, StateTM::E, StateTM::E},
    {StateTM::R, StateTM::S2, StateTM::E, StateTM::S2},
    {StateTM::L, StateTM::F, StateTM::E, StateTM::E},
    {StateTM::L, StateTM::S, StateTM::E, StateTM::E},
    {StateTM::E, StateTM::E, StateTM::E, StateTM::E},
    {StateTM::F, StateTM::F, StateTM::F, StateTM::F}};

int Way_to_State_TM(const char temp) // Функция, возвращающая номер столбца в матрице состояний МТ
{
    if (rus_isalpha(temp))
        return 0;
    if (temp == ' ' || temp == '\t' || temp == '\n')
        return 1;
    if (temp == '\0')
        return 3;
    return 2;
}

int Way_to_State(const char temp) // Функция, возвращающая номер столбца в матрице состояний КА
{
    if (rus_isalpha(temp))
        return 0;
    if (temp == ' ' || temp == '\t' || temp == '\n')//||temp ==','||temp =='.'||temp =='\''||temp =='\"'||temp ==':'||temp ==';'
        return 1;
    if (temp == '\0')
        return 2;
    return 3;
}

void RULE(char *&s, StateTM &state, char &saved) // Функция--набор правил для Машины Тьюринга(сдвиг головки в лево или в право, замена символа)
{
    int INP = Way_to_State_TM(*s);               // Чтобы определить действие при переходе воспользуемся двойным swich-case
    switch (state)                               // Для Машины Тьюринга это сдвиг каретки влево или вправо остаться на месте, замена символа на что-то 
    {                                            // или не замена
    case (S):// Start
        switch (INP)
        {
        case (0):
            if (saved != *s)                     // Чтобы избежать миллиона состояний, у нас будет память на один символ
                state = E;                       // 1)Берём самый левый символ, не равный пробелу, сравниваем его с самым правым(если головка МТ уже была там), запоминаем его и заменяем на пробел
            saved = *s;                          // и переходим в 2), если равен, если не равен, то переходим в 6). Если встречено два пробела подряд, то переходим в 5
            *s = ' ';
            s++;
            break;
        }
        break;

    case (S2):// Start from end                  // 3)Берём самый правый символ, не равный пробелу, сравниваем его с самым левым(если головка МТ уже была там), запоминаем его и заменяем на пробел
        switch (INP)                             // и переходим в 4), если равен, если не равен, то переходим в 6). Если встречено два пробела подряд, то переходим в 5
        {
        case (0):
            if (saved != *s)
                state = E;
            *s = ' ';
            s--;
            saved = *s;
            break;
        }
        break;

    case (R):// Right                            // 2)Бежим вправо, пока не встретим пробел или нуль-терминатор, перемещаем головку на одну ячейку влево и переходим в 3)
        switch (INP)
        {
        case (0):
            s++;
            break;
        case (1):
            s--;
            break;
        case (3):
            s--;
            break;
        }
        break;

    case (L):// Left                             // 4)Бежим влево, пока не встретим пробел или нуль-терминатор, перемещаем головку на одну ячейку вправо и переходим в 1)
        switch (INP)
        {
        case (0):
            s--;
            break;
        case (1):
            s++;
            break;
        }
        break;

    case (F):// Finish(exit)                      // 5) Слово--палиндром
        /* code */
        break;
    case (E): // Error                            // 6) Если какие-то из букв на проходах не равны переходим сюда
        /* code */
        break;
    }
    state = MATRIX_TM[(int)state][INP]; // Переход по матрице состояний МТ
}

struct Lex
{
    bool valid; // флаг корректности лексемы (соответствия заданию)
    char *str;  // текст лексемы
    Lex() : valid(false), str(nullptr){};
};

std::vector<Lex> LexAnalysis_1(char *str)// Функция автомата, разбивающего текст на лексемы
{
    std::vector<Lex> result;
    char *startWord = str;   // текущая позиция в строке
    State state = State::Sy; // текущее состояние
    Lex lex;                 // текущая лексема
    do
    {
        state = MATRIX[(int)state][Way_to_State(*str)];
        if (state == State::Sl || state == State::End)
        {
            int length = str - startWord;   // Вычислим длинну лексемы как разницу между текущим уазателем и началом слова
            if (length < 7&&length>0)       // Длинна лексемы меньше 7 по условию, а второе условие для отсеивания пустых лексем, они не встречаются, но условие обнадёживает
            {
                lex.str = new char[length + 1];
                strncpy(lex.str, startWord, length);    // strncpy--копирует одну строку в другую, нуль-терминаторы тоже копирует, по этому при копировании строк целиком не нужно доставлять '/0'
                lex.str[length] = '\0';                 // В копируемой строке нет '\0', нуль-терминируем сами
                result.push_back(lex);                  // Вставим лексему в конец вектора
            }
            startWord = str+1;
        }
        str++;
    } while (state != End);                             // Из цикла выйдем в конечном состоянии автомата, оно одно

    return result;                                      // Вернём вектор лексем
}

void LexAnalysis(vector<Lex> &vec)// Функция Машины Тьюринга, определяющей палиндромы
{
    char saved;
    for (int i = 0; i <(int)vec.size(); i++)            // Перебор вектора лексем
    {
        StateTM state = StateTM::S;                     // Для каждой новой лексемы начальное состояние МТ--S(Start)

        int size=strlen(vec[i].str)+1;                  // Тут скопируем текст лексемы, чтоб МТ его не попортила
        Lex lex;                                        //
        lex.str=new char[size];                         //
        strncpy(lex.str, vec[i].str, size);             //

        saved = *lex.str;
        char* const p = lex.str;                        // Константный указатель, чтобы удалить потом строку
        while (state != E && state != F)
        {
            RULE(lex.str, state, saved);
        }
        if (state == 5)
        {
            vec[i].valid = true;                        // Лексема--палиндром, если выход из МТ состоялся через F(5), выход может состояться через E(Error)(6)
        }
        delete[] p;                                     // Удаление строки
    }
}

int get_size(ifstream &fin) // Ф-я получения длинны файла
{
    fin.seekg(0, ios::end); // Указатель на конец файла
    int size = fin.tellg(); // Узнать позицию
    fin.seekg(0, ios::beg); // Передвинуть указатель на начало
    return size;
}

ifstream &operator>>(ifstream &fin, char *&array)      // Перегрузим оператор ввода
{
    int size = get_size(fin);
    fin.read(array, size);
    array[size] = '\0';
    return fin;
}

int main()
{
    setlocale(LC_ALL, ".1251");                 // Кодировка
    ifstream fin("input.txt", ios_base::in);    // Откр потока ввода
    ofstream fout("output.txt");                // Открытие потока вывода
    if(!fin.is_open()&&!fout.is_open()) return 0; // Если потоки не открылись, ничего можно не делать
    int size = get_size(fin);
    char *array = new char[size + 1];           // Динамический массив char
    fin >> array;                               // Воспользуемся написанной перегрузкой оператора
    fin.close();
    vector<Lex> vec;                            // Вектор лексем
    vec = LexAnalysis_1(array);                 // Ф-я КА, разбивающего текст на лексемы
    LexAnalysis(vec);
    for (int i = 0; i < (int)vec.size(); i++)   // Вывод в cout
    {
        if (vec[i].valid)
            cout << vec[i].str << ' ';
    }
    for (int i = 0; i < (int)vec.size(); i++)   // Вывод в fout
    {
        if (vec[i].valid)
            fout << vec[i].str << ' ';
        delete[]vec[i].str;                     // Удалим строки лексем
    }
    fout.close();                               
    delete[] array;                             // Удалим текст
    return 0;
}       
