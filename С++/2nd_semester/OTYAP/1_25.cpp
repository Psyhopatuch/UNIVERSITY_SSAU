#include <iostream>
#include <fstream>

using namespace std;// Работаем в пространстве имён стандартной библиотеки

bool russian_is_bukva(char bukva)// Аналог isalpha() для кириллицы
{
    return (bukva >= 'А' && bukva <= 'Я') || (bukva >= 'а' && bukva <= 'я') || bukva == 'ё' || bukva == 'Ё';
}

char russian_tolower(char bukva)// Аналог tolower() для кириллицы
{
    if(bukva >= 'А' && bukva <= 'Я')return (char)bukva+32;
    if(bukva == 'Ё')return (char)bukva+15;
    return bukva;
}

void texter(const char *text, ofstream &fout)//Передадим неконстантный указатель на константный char, содержащий текст и поток вывода по амперсанду, чтобы избежать копирования
{
    char *word = new char[500];//Динамический массив char
    int size = 0;//current word size
    bool skip = false;//Переменная-флажок, отвечающая за пропуск слова если оно длиннее 6 символов
    do
    {
        if (russian_is_bukva(*text))
        {
            word[size] = *text;
            size++;
            size > 6 ? skip = true : skip;//Слова длиннее 6 символов не будем считать словами и будем их пропускать
        }
        else
        {
            if (!skip)// Если слово не длиннее 6 букв
            {

                bool ravnue = 1;//Флажок равенства символов
                for (int i = 0, j = size - 1; i <= size / 2 && ravnue != 0; i++, j--)//Будем проходить полученное слово с двух концов и сравнивать символы, закончим сразу, как только два симметричных символа не совпадут
                {
                    //fout<< "tolower("<<russian_tolower(word[i])<<") == tolower("<<russian_tolower(word[j])<<")"<<endl;
                    russian_tolower(word[i]) == russian_tolower(word[j]) ? ravnue = 1 : ravnue = 0;//Тернарное условие чтобы избежать if()
                }
                if (ravnue)//Если слово симметрично равно посимвольно, то
                {
                    for (int i = 0; i < size; i++)//Побуквенный вывод в консоль и в output.txt
                    {
                        fout << word[i];
                        cout << word[i];
                    }
                    fout << " ";
                    cout << " ";
                }
            }
            skip=false;//"Сброс" флажка пропуска
            delete[] word;// Очистим память
            word = new char[500];//Создадим заново 
            size = 0;//Сбросим счётчик количества символов в массиве word
        }

    } while (*text++);//Будем двигать указатель по тексту пока он не nullptr + 1 раз, последний раз нужен для того, чтобы обработать последнее слово
    delete[] word;// Финальное удаление 
}

int main()
{

    setlocale(LC_ALL, ".1251");//Подключаем кодировку указанную в задании

    ifstream fin("input.txt", ios_base::in);//Открываем поток файлового ввода "ios_base::in" отвечает за установку указателя в начало
    ofstream fout("output.txt");//Открываем поток вывода, по умолчанию файл будет перезаписан

    if (fin.is_open() && fout.is_open())//Проверим открылись ли потоки
    {

        cout << "Connected" << endl;//Информативное сообщение в терминал

        char *text = new char[500];//Динамический массив char

        fin.getline(text, 500, '\0');//Считаем данные из файла либо 500 символов, либо до конца 

        texter(text, fout);//Функция 

        delete[] text;//Удалим ненужное
    }

    //Закроем потоки
    fin.close();
    fout.close();
}
