#include <iostream> //Подключение директивы ввод-вывод
#include <string> //Подключение директивы строк, является элементом iostream, но на старых версиях С++ требует подключения
#include <regex> //Подключение директивы регулярных выражений

using namespace std; //Работа в пространстве имён стандартной библиотеки 

regex r_size("[1-9]{1}|[10]{1}"); //Регулярное выражение
regex r_elem("[-]?[0-9]{1,9}[.]?[0-9]{0,9}"); //Регулярное выражение
regex r_cont("[Y]|[N]");

bool IntCheck(string user_data) //Проверка введённого размера
{
	if (regex_match(user_data.c_str(), r_size))
		return 1;
	else
		return 0;
}


bool DoubleCheck(string user_data) //Проверка введённого размера
{
	if (regex_match(user_data.c_str(), r_elem))
		return 1;
	else
		return 0;
}

bool YNCheck(string user_data) //Проверка символа продолжения
{
	if (regex_match(user_data.c_str(), r_cont))
		return 1; //Возвращает функции значение "Истина"
	else
		return 0; //Возвращает функции значение "Ложь"
}

int main()
{

	string cont, s_line_count, s_stolb_count, s_element;

	do //Повтор программы 
	{
		cout << "Enter matrix length(max=10): ";
		getline(cin, s_line_count);
		while (!IntCheck(s_line_count))
		{
			cout << "Error, incorrect input\n";
			cout << "Enter matrix length(max=10): ";
			getline(cin, s_line_count);
		}
		int line_count = stoi(s_line_count);

		cout << "Enter matrix width(max=10): ";
		getline(cin, s_stolb_count);
		while (!IntCheck(s_stolb_count))
		{
			cout << "Error, incorrect input\n";
			cout << "Enter matrix length(max=10): ";
			getline(cin, s_stolb_count);
		}
		int stolb_count = stoi(s_stolb_count);

		double matrix[10][10]; //Объявление матрицы

		for (int i = 0; i < line_count; i++) //Ввод матрицы 
		{
			for (int j = 0; j < stolb_count; j++)
			{
				cout << "Enter element[" << i+1 << "][" << j+1 << "]: ";

				getline(cin, s_element);

				while (!DoubleCheck(s_element))
				{
					cout << "Error, incorrect input\n";
					cout << "Enter element[" << i+1 << "][" << j+1 << "]: ";
					getline(cin, s_element);
				}
				matrix[i][j] = stod(s_element); //String to double
			}
		}

		double min, max;//Объявление и инициализация переменных принимающих значения минимума и максимума
		double min_in_stolb[10], max_in_line[10];

		for (int i = 0; i < line_count; i++)
		{
			max = matrix[i][0];
			for (int j = 0; j < stolb_count; j++)
			{
				if (matrix[i][j]>max) //Если текущий элемент больше чем переменная максимума, то присваиваем её значение текущего элемента
				{
					max = matrix[i][j];
				}
			}
			max_in_line[i] = max;
		}

		/*for (int i = 0; i < len; i++)
		{
			cout << "maxs[" << i+1 << "]:" << max_in_line[i] << ";";
		}*/

		for (int j = 0; j < stolb_count; j++)
		{
			min = matrix[0][j];
			for (int i = 0; i < line_count; i++)
			{
				if (matrix[i][j] < min) //Если текущий элемент больше чем переменная максимума, то присваиваем её значение текущего элемента
				{
					min = matrix[i][j];
				}
			}
			min_in_stolb[j] = min;
		}

		/*for (int i = 0; i < wid; i++)
		{
			cout << "mins[" << i+1 << "]:" << min_in_stolb[i]<<";";
		}*/

		for (int i = 0; i < line_count; i++)
		{
			for (int j = 0; j < stolb_count; j++)
			{
				if (min_in_stolb[j] == max_in_line[i])
				{ 
					cout << "Sedle point: (" << i+1 << ";" << j+1 << ")\n";
				}
			}
		}

		cout << "\nPrefer to continue working?[Y/N]"; //Запрос повтора программы
		getline(cin, cont); //Получить строку целиком--std::getline(откуда,куда записать)
		while (!YNCheck(cont)) //Цикл пока не будут получены корректные данные, проверка на соответствие регулярному выражению
		{
			cout << "Error. Incorrect format, try enter again:\n";
			cout << "Prefer to continue working?[Y/N]:";
			getline(cin, cont); //Получить строку целиком--std::getline(откуда,куда записать)
		}

	} while (cont == "Y"); //Условие повтора программы
	return 0;
}