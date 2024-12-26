#include <iostream>
#include <regex> 

using namespace std;
int main()
{
	char cont;
	do
	{
		setlocale(LC_ALL, "RU");

		string user_data; //Переменная для проверки
		cout << "Введите число\n";
		cin >> user_data; //Ввод переменной для проверки
		//Регулярное выражение
		double user_data_1;
		regex regular("([0-9:]{0,})");
		//Условие, проверка на соответствие регулярному выражению
		if (regex_match(user_data.c_str(), regular))//Regex_match проверяет, соотв. ли вся строка выражению, regex_search проверяет подстроки на соответствие данному выражению
		{
			cout << "Верный ввод\n";
			user_data_1 = stod(user_data);// Преобразование string в double/stoi/stof/etc.
			cout << user_data_1 << "\n";
		}
		else
		{
			cout << "Неверный ввод\n";
		}

		cout << "Повтор?[Y/N]\n";
		cin >> cont;
	} while (cont == 'Y');
	return 0;
}

int HHMMSStoSec(string time_in)
{
	string replace;
	int replace_int, time_out;
	time_out = 0;
	for (int i = 0; i <= 7; i++) //Перебор строки введённого времени
	{
		if (time_in[i] != ':') // Условие пропуска двоеточий, перевод времени в абстрактную форму прошедших секунд с начала дня
		{
			replace = time_in[i];
			replace_int = stoi(replace); // Перевод типа данных char в т.д. int
			switch (i)
			{
			case 0:time_out += replace_int * 36000; break; //Перевод. Десятки часов в секунды
			case 1:time_out += replace_int * 3600; break; //Перевод. Единицы часов в секунды
				//Case 2 это двоеточие, пропущенное условием
			case 3:time_out += replace_int * 600; break; //Перевод. Десятки минут в секунды
			case 4:time_out += replace_int * 60; break; //Перевод. Единицы минут в секунды
				//Case 5 это двоеточие, пропущенное условием
			case 6:time_out += replace_int * 10; break; //Перевод. Десятки секунд в секунды
			case 7:time_out += replace_int; break; //Прибавление оставшихся единиц секунд
			}
		}
	}
	return time_out; //Возвращает функции вычисленное значение
}

bool doubleCheck_0(string x) //Проверка введённого размера
{
	regex regular("[-][0-9]{1,9}|[0-9]{1,9}|[-][0-9]{1,9}[.][0-9]{1,9}|[0-9]{1,9}[.][0-9]{1,9}"); //Регулярное выражение
	if (regex_match(x.c_str(), regular))
		return 1;
	else
		return 0;
}

bool doubleCheck_1(string x) //Проверка введённого размера
{
	regex regular("[-]?[0-9]{1,9}[.]?[0-9]{0,9}"); //Регулярное выражение ?-символ может быть, а может не быть.
	//regular("[-][0-9]{1,9}|[0-9]{1,9}|[-][0-9]{1,9}[.][0-9]{1,9}|[0-9]{1,9}[.][0-9]{1,9}"); //Регулярное выражение
	if (regex_match(x.c_str(), regular))
		return 1;
	else
		return 0;
}

bool IntCheck(string x) //Проверка введённого размера
{
	regex regular("[1-9]{1}|[10]{1}"); //Регулярное выражение
	if (regex_match(x.c_str(), regular))
		return 1;
	else
		return 0;
}

bool IsTime(string x)
{
	regex regular("([0-1][0-9]|[2][0-3])""(:)""([0-5][0-9])""(:)""([0-5][0-9])"); //Регулярное выражение
	if (regex_match(x.c_str(), regular)) //Проверка на соответствие регулярному выражению и отсутствие пробелов
	{
		return true;
	}
	else
	{
		return false;
	}
}



