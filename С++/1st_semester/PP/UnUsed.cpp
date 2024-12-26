#include <iostream> //Подключение директивы ввод-вывод
#include<string> //Подключение директивы строк, является элементом iostream, но на старых версиях С++ требует подключения
#include <regex> //Подключение директивы регулярных выражений

using namespace std; //Чтобы не прописывать каждый раз std:: будем работать в этом пространстве имён

int getInt(string TextOutput, string TextError) // Функция, приенимающая на вход текст ошибки/просто текст вывода
{
	regex regular("[0-9]{0,9}"); //Регулярное выражение
	string user_data;
	getline(cin, user_data);
	while (!regex_match(user_data.c_str(), regular)) //Цикл пока не будут получены корректные данные, проверка на соответствие регулярному выражению
	{
		cout << TextError<<endl;
		cout << TextOutput;
		getline(cin, user_data);
	}
	return stoi(user_data); //Возвращает функции значение считанного в типе int
}

double getDoubleEl(string TextOutput, string TextError,int i,int j) // Функция, приенимающая на вход текст ошибки/просто текст вывода/индексы ячейки матрицы
{
	regex regular("[-][0-9]{0,9}|[0-9]{0,9}|[-][0-9]{0,9}[.][0-9]{0,9}|[0-9]{0,9}[.][0-9]{0,9}"); //Регулярное выражение
	string user_data;
	getline(cin,user_data);
	while (!regex_match(user_data.c_str(), regular)) //Цикл пока не будут получены корректные данные, проверка на соответствие регулярному выражению
	{
		cout << TextError<<endl;
		cout << TextOutput<<"["<<i<<"]["<<j<<"]: ";
		getline(cin, user_data);
	}
return stod(user_data); //Возвращает функции значение считанного в типе double
}

int main()
{
	char user_continue;
	do //Повтор программы 
	{ 
		cout << "Enter matrix length(max=10): ";
		int length = getInt("Enter matrix length: ", "Error, incorrect input");

		cout << "Enter matrix width: ";
		int width = getInt("Enter matrix width(max=10): ", "Error, incorrect input");

		//Проверки на максимальную длинну и ширину
		if (length > 10)
		{
			length = 10;
		}

		if (width > 10)
		{
			width = 10;
		}

		double matrix[10][10]; //Объявление матрицы
		for (int i = 0; i < length;i++)
		{
			for (int j = 0; j < length; j++)
			{
				cout << "Enter element[" << i << "][" << j << "]: ";
				matrix[i][j] = getDoubleEl("Enter element", "Error, incorrect input ", i, j);
			}
		}

		double min = matrix[0][0], max = matrix[0][0];//Объявление и инициализация переменных принимающих значения минимума и максимума

		for (int i = 0; i < length; i++)
		{
			for (int j = 0; j < length; j++)
			{
				if (matrix[i][j]>max) //Если текущий элемент больше чем переменная максимума, то присваиваем её значение текущего элемента
				{
					max = matrix[i][j];
				}

				if (matrix[i][j]<min) //Аналогично
				{
					min = matrix[i][j];
				}
			}


		}

		cout << "Min: " << min;
		cout << "\nMax: " << max;

		cout << "\nPrefer to continue working?[Y/N]"; //Запрос повтора программы
		cin >> user_continue;
	} while (user_continue == 'Y'); //Условие повтора программы
	return 0;
}