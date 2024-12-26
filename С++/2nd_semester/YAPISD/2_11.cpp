#include <iostream>
#include <fstream>

using namespace std;

int get_size() { // Функция будеть открывать файл, считывать размер матрицы и закрывать
    ifstream fin("input.txt", ios_base::in);// Откроем поток и указатель на начало
    int size;
    fin >> size; // Для возведения в квадрат матрица всегда квадратная, достаточно одного размера, ошибки не возникнет
    fin.close(); // Закроем поток
    return size; // Вернём размер
}

void get_matrix(int**& matrix) {
    ifstream fin("input.txt", ios_base::in); 

    int size;
    fin >> size;// Чтобы не передавать в функцию размер матрицы, считаем его из файла,
    fin >> size;// дважды, чтобы просто подвинуть указатель в потоке

    int i = 0;
    while (fin >> matrix[i / size][i % size] && ++i < size * size);// Считывание матрицы из потока, [i / size]--строка, [i % size]--столбец
    fin.close();
}

int get_elem(int i, int size, int** matrix)// Отдельная ф-я, вычисляющая элемент, стоящий на месте [i / size][i % size]
{
    int s = 0;
    int j = -1;
    while (++j < size) s += matrix[i / size][j] * matrix[j][i % size]; // j-"бегает" по [i / size] строке и [i % size] столбцу соответственно
    return s; //  Выход из цикла while осуществляется, когда j "пробежит" строку и столбец, затем возврат значения элем.
}

void get_multiply(int size, int**& matrix)
{
    int** matrix_multiply = new int* [size];// Создадим новую динамическую матрицу, так как выполнить перемножение в "один проход"  не получится
    for (int i = 0; i < size; i++)
        matrix_multiply[i] = new int[size];// Динамическая матрица--"динамический одномерный массив одномерных динамических массивов"

    int i = -1;
    while (++i < size * size)  
        matrix_multiply[i / size][i % size] = get_elem(i, size, matrix);// Последовательно заполним новую матрицу результатом матричного перемножения

    for (int i = 0; i < size; i++) // Освободим память, удаляя исходную матрицу
        delete[] matrix[i]; // Удалять нужно каждый одномерный массив матрицы отдельно
    delete[] matrix;

    matrix = matrix_multiply; // Чтобы ничего не возвращать, старый указатель теперь указывает на новую матрицу
}

void print_matrix(int size, int**& matrix) 
{ // Функция, выводящая матрицу в файл

    ofstream fout("output.txt");
    int i = -1;
    while (++i < size * size) fout << matrix[i / size][i % size] << " "; // Переберём элементы матрицы и выведем каждый элемент матрицы в поток

    for (int i = 0; i < size; i++)// Освободим память, удаляя исходную матрицу, она уже выведена и не понадобится
        delete[] matrix[i];
    delete[] matrix;

    fout.close();// Закроем поток
}

int main()
{
    int size = get_size(); // Считаем из файла размер матрицы

    int** matrix = new int* [size]; //Создадим двумерный динамический массив
    for (int i = 0; i < size; i++)
        matrix[i] = new int[size]; 

    get_matrix(matrix); // Считаем матрицу из файла

    get_multiply(size, matrix); // Возведём в матричный квадрат

    print_matrix(size, matrix); // Выведем матрицу в файл

    return 0; 
}
