#include <iostream> //Подключение директивы ввод-вывод
#include<string> //Подключение директивы строк, является элементом iostream, но на старых версиях С++ требует подключения
#include <regex> //Подключение директивы регулярных выражений

using namespace std; //Работа в пространстве имён стандартной библиотеки

bool IsTime(string user_data) //Проверка строки на содержание ЧЧ:ММ:СС
{
	regex regular("([0-1][0-9]|[2][0-3]):([0-5][0-9]):([0-5][0-9])"); //Регулярное выражение
	if (regex_match(user_data.c_str(), regular)) //Проверка на соответствие регулярному выражению и отсутствие пробелов
		return 1; //Возвращает функции значение "Истина"
	else
		return 0; //Возвращает функции значение "Ложь"
}

int HHMMSStoSec(string time_in) //Функция переводящая ЧЧ:ММ:СС в секунды с начала суток
{
	regex regular("([0-1][0-9]|[2][0-3]):([0-5][0-9]):([0-5][0-9])"); //Регулярное выражение
	smatch parts; //Переменная, содержащая куски
	regex_match(time_in, parts, regular); //Дробление аргумента функции на круглые скобки в regular и запись их в smatch parts 

	int Hours = stoi(parts.str(1));
	int Min = stoi(parts.str(2));
	int Sec = stoi(parts.str(3));

	int time_out = Hours * 3600 + Min * 60 + Sec;

	return time_out; //Возвращает функции вычисленное значение
}

bool YNCheck(string user_data) //Проверка символа продолжения
{
	regex regular("[Y]|[N]");
	if (regex_match(user_data.c_str(), regular))
		return 1; //Возвращает функции значение "Истина"
	else
		return 0; //Возвращает функции значение "Ложь"
}


int main() 
{
	string user_continue, begining_time, end_time;
	int result;
	do //Условие повтора программы
	{
		do //Проверка на ненулевой результат
		{
			cout << "Enter begining time[HH:MM:SS]: "; //Ввод времени начала операции
			getline(cin, begining_time); //Получить с троку целиком--std::getline(откуда,куда записать)

			while (!IsTime(begining_time)) //Цикл пока не будут получены корректные данные, проверка на соответствие регулярному выражению
			{
				cout << "Error. Incorrect format, try enter again:\n";
				cout << "Enter begining time[HH:MM:SS]: ";
				getline(cin, begining_time); //Получить строку целиком--std::getline(откуда,куда записать)
			}

			cout << "Enter end time[HH:MM:SS]: "; //Ввод времини конца операции
			getline(cin, end_time); //Получить строку целиком--std::getline(откуда,куда записать)

			while (!IsTime(end_time)) //Цикл пока не будут получены корректные данные, проверка на соответствие регулярному выражению
			{
				cout << "Error. Incorrect format, try enter again:\n";
				cout << "Enter end time[HH:MM:SS]: ";
				getline(cin, end_time); //Получить строку целиком--std::getline(откуда,куда записать)
			}

			result = HHMMSStoSec(end_time) - HHMMSStoSec(begining_time); //Вычисления через функцию HHMMSStoSec
			if (result > 0)
			{
				cout << result << "(seconds) or "; //Вывод результата в секундах
				cout << result / 60 << "(minutes)\n"; //Вывод результата в минутах (приблизительно)
			}
			else cout << "End time cannot be early than begining time, try again ^_^\n";
		} 
		while (result <= 0); //Проверка на ненулевой результат

		cout << "Prefer to continue working?[Y/N]:"; //Запрос повтора программы
		getline(cin, user_continue); //Получить строку целиком--std::getline(откуда,куда записать)
		while (!YNCheck(user_continue)) //Цикл пока не будут получены корректные данные, проверка на соответствие регулярному выражению
		{
			cout << "Error. Incorrect format, try enter again:\n";
			cout << "Prefer to continue working?[Y/N]:";
			getline(cin, user_continue); //Получить строку целиком--std::getline(откуда,куда записать)
		}
	} while (user_continue == "Y"); //Условие повтора программы
return 0;
}