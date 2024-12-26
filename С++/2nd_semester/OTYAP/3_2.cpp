#include <iostream> // Подключим библиотеку для работы с потоками ввода-вывода
#include <fstream>  // Подключим библиотеку для работы с файловыми потоками
#include <vector>   // Подключим библиотеку для работы с std::vector
#include <cstring>  // Подключим библиотеку для работы с С-строками

using namespace std;

// Объявляем перечисление с именем STATES
enum STATES
{
    A, // Состояние чтения идентификатора
    B, // Состояние чтения константы
    C, // Состояние чтения арифметических символов
    D, // Состояние чтения знака ';'
    E, // Состояние чтения неизвестной лексемы и прочие ошибки
    G, // Состояние для вывода ключевых слов
    H, // Состояние чтения знака '>'
    I, // Состояние чтения знака '<>'
    J, // Состояние чтения знака '<'
    K, // Состояние чтения знака '='
    F, // Состояние выхода из автомата
    S  // Начальное состояние
};

// Удобно будет хранить массив типов лексем, индексы типов совпадают с состояниями
const char *types[] = {"[id]", "[vl]", "[ao]", "[sc]", "[wl]", "[kw]", "[co]", "[co]", "[co]", "[eq]"};

// Функция, сравнивающая лексему с ключевыми словами
bool is_kw(char *text)
{   // strcmp вернёт ноль, если С-строки равны
    if (!strcmp(text, "until"))
        return true;
    if (!strcmp(text, "and"))
        return true;
    if (!strcmp(text, "or"))
        return true;
    if (!strcmp(text, "not"))
        return true;
    if (!strcmp(text, "do"))
        return true;
    if (!strcmp(text, "loop"))
        return true;
    return false;
}

// Матрица состояний и переходов конечного автомата
const enum STATES ST_MATRIX[10][12] 
{ //         A  B  C  D  E  G  H  I  J  K  F  S
    /*A-z*/ {A, E, A, A, E, A, A, A, A, A, F, A},
    /*0-9*/ {A, B, B, B, E, B, B, B, B, B, F, B},
    /*Sep*/ {S, S, S, S, S, S, S, S, S, S, F, S},
    /*Ari*/ {C, C, C, C, E, C, C, C, C, C, F, C},
    /* ; */ {D, D, D, D, D, D, D, D, D, D, F, D},
    /* < */ {J, J, J, J, J, J, J, J, J, J, F, J},
    /* = */ {K, K, K, K, K, K, K, K, K, K, F, K},
    /* > */ {H, H, H, H, H, H, H, H, I, H, F, I},
    /* \0*/ {F, F, F, F, F, F, F, F, F, F, F, F},
    /*NAS*/ {E, E, E, E, E, E, E, E, E, E, F, E}
};

// Функция для перехода по матрице состояний автомата, возвращает индекс символа в матрице автомата
int GetNextState(const char temp)
{

    if (isalpha(temp)) return 0; /*A-z*/
    if ((int)temp > 47 && temp < 58) return 1; /*0-9*/

    switch (temp)
    {
    case (' '): /*Sep*/
        return 2;
        break;
    case ('\n'): /*Sep*/
        return 2;
        break;
    case ('\t'): /*Sep*/
        return 2;
        break;
    case ('*'): /*Ari*/
        return 3;
        break;
    case ('+'): /*Ari*/
        return 3;
        break;
    case ('-'): /*Ari*/
        return 3;
        break;
    case ('/'): /*Ari*/
        return 3;
        break;
    case (';'): /* ; */
        return 4;
        break;
    case ('<'): /* < */
        return 5;
        break;
    case ('='): /* = */
        return 6;
        break;
    case ('>'): /* > */
        return 7;
        break;
    case ('\0'): /* \0*/
        return 8;
        break;
    }
    return 9; /*NAS*/
}

struct Lex
{
    char *str = nullptr; // Текст лексемы
    int id = 4; // id типа лексемы
};

void lex_analizer(char *text, vector<Lex> &vec)
{
    STATES cur_state = S; // Объявим и инициализируем переменную, хранящую текущее состояние
    STATES prev_state;    // Объявим переменную, хранящую предыдущее состояние
    char *lex_beg = text; // Объявим и инициализируем указатель, хранящий начало обрабатываемой лексемы
    Lex cur_lex;          // Объявим переменную пользовательского типа для хранения текста лексемы и id
    int size = 0;         // Объявим и инициализируем переменную, хранящую текущую длинну лексемы
    do
    {
        prev_state = cur_state; // Предыдущее состояние=следующее состояние
        size = text - lex_beg; // Размер лексемы как разница указателей
        if (size > 5) cur_state = E; // Если размер лексемы >5, то переведём автомат в состояние ошибки
        cur_state = ST_MATRIX[GetNextState(*text)][cur_state]; // Переход по матрице состояний автомата
        // Далее блок кода с проверками и сохранением лексем, условие сложное...
        // Нам необходимо не сохранять читаемую лексему с ошибкой, пробелы, сохранять каждый новый знак сравнения и арифметические знаки по одному, сохранять знак '<>'.
        // Сохранять л-му будем при неравенстве prev & cur состояний, за искл. описанных случаев, и при одиночных знаках, переходящих в своё же состояние
        if ((cur_state != E && cur_state != I && prev_state != cur_state && prev_state != S) || prev_state == H || prev_state == D || prev_state == K || prev_state == C ||(prev_state == J && cur_state != I)) 
        {
            cur_lex.str = new char[size + 1]; // Выделим память под динамический массив, хранящий текст лексемы
            strncpy(cur_lex.str, lex_beg, size); // Скопируем текст лексемы из исходного текста в динамический массив внутри cur_lex
            cur_lex.str[size] = '\0'; // Нультерминируем C-cтроку
            if (prev_state == A && is_kw(cur_lex.str)) prev_state = G; // Если идентификатор совпал с ключевым словом, переведём автомат в состояние вывода ключ. слов
            if (prev_state == B && (-32768 > atoi(cur_lex.str) || atoi(cur_lex.str) > 32767)) prev_state = E; // Числа, не вход. в интервал--ошибка 
            cur_lex.id = prev_state; // Так как id типов лексем совадают с индексами выходных состояний автомата, то сделаем так, так и было задумано, чтоб избежать сложных ф-й обработки
            vec.push_back(cur_lex); // Добавим новую лексему в конец std::vector<Lex>
            lex_beg = text; // Передвинем указатель на начало лексемы
        }
        ++text; // Передвинем указатель на текущий символ на след символ
        if (cur_state == S) lex_beg = text; // Чтоб начало не было до пробела
    } while (cur_state != F); // Выход по конечному состоянию автомата
}

int get_size(ifstream &fin) // Ф-я получения длинны файла
{
    fin.seekg(0, ios::end); // Указатель на конец файла
    int size = fin.tellg(); // Узнать позицию
    fin.seekg(0, ios::beg); // Передвинуть указатель на начало
    return size;            // Вернуть значение
}

ifstream &operator>>(ifstream &fin, char *&array) // Перегрузим оператор ввода
{
    int size = get_size(fin); // Инициализируем целочисленную переменную конечной позицией в файле
    fin.getline(array, size + 1, '\0'); // Считаем файл с помощью метода getline
    return fin; // Вернём поток ввода 
}

ostream &operator<<(ostream &fout, vector<Lex> &vec) // Перегрузим оператор вывода
{
    for (unsigned int i = 0; i < vec.size(); i++) // Перебор вектора
    {
        fout << vec[i].str << types[vec[i].id] << ' '; // Вывод текста лексем и типа
    }
    fout << endl;
    for (unsigned int i = 0; i < vec.size(); i++) // Перебор вектора
    {
        if (vec[i].id == 0) fout << vec[i].str << ' '; // Вывод текста лексем-идентификаторов
    }
    fout << endl;
    for (unsigned int i = 0; i < vec.size(); i++) // Перебор вектора
    {
        if (vec[i].id == 1) fout << vec[i].str << ' '; // Вывод текста лексем-констант
    }
    return fout; // Поток должен быть возвращён
}

int main()
{
    ifstream fin("input.txt"); // Откроем файловый поток ввода
    ofstream fout("output.txt");// Откроем файловый поток вывода
    if (!fin.is_open() && !fout.is_open()) return 1; // Потоки не открылись--переидём к возвращению значений

    char *text = new char[get_size(fin) + 1]; // Создадим динамический массив типа char для хранения текста файла
    fin >> text; // С помощью перегрузки оператора ввода считаем текст из файла в массив
    fin.close(); // Закроем поток ввода

    vector<Lex> vec; // Объявим вектор лексем
    lex_analizer(text, vec); // Ф-я лексического анализатора
    delete[] text; // Очистим место из-под динамического массива(удалим его)

    fout << vec; // С помощью перегрузки оператора вывода выведем текст из std::vector<Lex> в файл
    cout << vec; // С помощью перегрузки оператора вывода выведем текст из std::vector<Lex> на экран

     for (unsigned int i = 0; i < vec.size(); i++) // Перебор вектора
    {
        delete[] vec[i].str; // Очистим задействованную память
    }

    fout.close(); // Закроем поток вывода
    return 0; // Вернём 0
}
