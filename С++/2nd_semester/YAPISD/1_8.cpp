#include <iostream>
#include <fstream>

using namespace std; // Работаем в пространстве имён стандартной библиотeки

int how_many_wrds(ifstream &fin) // Функция возвращает кол-во слов в файле
{
    int size = 0;
    double temp;
    while (fin >> temp) size++; // Пока читается будем читать и записывать кол-во считанных слов в счётчик
    fin.clear();            // Снимем флаги с потока;
    fin.seekg(0, ios::beg); // Передвинем указатель в потоке на начало
    return size;
}

ifstream &operator>>(ifstream &fin, double *&nums) // Перегрузим оператор ввода для double *&nums
{
    int i = 0;
    while (fin >> nums[i++]); // Пока читается будем читать в динамический массив char
    return fin;
}

double cubes(int &size, double *&nums) // Передадим ссылку на переменную типа int и на указатель типа double
{
    double summ = 0;
    for (int i = 0; i < size; i++)
    {
        nums[i] > 0 ? summ += nums[i] * nums[i] * nums[i] : 1; // Проверка положительности элемента и вычисления
    }
    return summ;
}

int main()
{
    ifstream fin("input.txt", ios_base::in); // Откроем поток ввода и установим указатель на начало
    if (fin.is_open())                       // Если поток ввода открыт
    {
        int size = how_many_wrds(fin);
        double *nums = new double[size]; // Создадим динамический массив double, размером в количество слов в файле
        fin >> nums;                     // Считаем числа из файла за счёт перегрузки оператора
        fin.close();

        ofstream fout("output.txt");
        if (fout.is_open()) // Если поток вывода открыт
        {
            fout << cubes(size, nums);
            fout.close();
        }
        else // Если поток вывода не был открыт
        {
            delete[] nums; // Удалим память, которая была выделена new
            return -1; 
        } 
        delete[] nums; // Освободим память, которая была выделена new
    }
    else return -1; // Если поток не был открыт вернём -1
    return 0;      // Если программа отработала штатно вернём ноль
}
