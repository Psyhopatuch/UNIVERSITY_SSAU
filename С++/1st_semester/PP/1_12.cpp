#include <iostream> // Подключение директивы ввод-вывод
#include <string> // Подключение директивы строк, является элементом iostream, но на старых версиях С++ требует подключения
#include <regex> // Подключение директивы регулярных выражений


using namespace std; //Работа в пространстве имён стандартной библиотеки 

string error_text = "|ERROR.INCORRECT INPUT|\n";
regex r_size("[2-9][0-9]{0,3}"); // Регулярное выражение
regex r_elem("[-]?[0-9]{1,5}[.]?[0-9]{0,3}"); // Регулярное выражение
regex r_cont("[Y]|[N]"); // Регулярное выражение

bool IntCheck(string x) // Проверка введённого размера
{
	if (regex_match(x.c_str(), r_size))
		return 1; // Возвращает функции значение "Истина"
	else
		return 0; // Возвращает функции значение "Ложь"
}

bool DoubleCheck(string x) // Проверка элемента матрицы
{
	if (regex_match(x.c_str(), r_elem))
		return 1; // Возвращает функции значение "Истина"
	else
		return 0; // Возвращает функции значение "Ложь"
}

bool YNCheck(string user_data) // Проверка символа продолжения
{
	if (regex_match(user_data.c_str(), r_cont))
		return 1; // Возвращает функции значение "Истина"
	else
		return 0; // Возвращает функции значение "Ложь"
}


int main()
{
	
	string user_continue, temp; // Обьявление переменных
	do // Повтор программы 
	{
		cout << "Enter matrix length(max=9*10^3): "; // Ввод длинны матрицы
		getline(cin, temp); // Получить с троку целиком--std::getline(откуда,куда записать)
		while (!IntCheck(temp)) // Пока функция проверки не "true"
		{
			cout << error_text; // Вывод текста ошибки
			cout << "Enter matrix length(max=9*10^3): ";
			getline(cin, temp); // Получить с троку целиком--std::getline(откуда,куда записать)
		}
		int len = stoi(temp);

		cout << "Enter matrix width(max=9*10^3): ";
		getline(cin, temp); // Получить с троку целиком--std::getline(откуда,куда записать)
		while (!IntCheck(temp)) // Пока функция проверки не "true"
		{
			cout << error_text; // Вывод текста ошибки
			cout << "Enter matrix length(max=9*10^3): ";
			getline(cin, temp); // Получить с троку целиком--std::getline(откуда,куда записать)
		}
		int wid = stoi(temp);

		// Объявление матрицы
		double** matrix = new double* [len];
		for (int i = 0; i < len; i++) 
		{       
			matrix[i] = new double[wid]; 
		}

		for (int i = 0; i < len; i++) //Ввод матрицы перебором с проверкой
		{
			for (int j = 0; j < wid; j++)
			{
				cout << "Enter element[" << i+1 << "][" << j+1 << "]: ";

				getline(cin, temp); // Получить с троку целиком--std::getline(откуда,куда записать)

				while (!DoubleCheck(temp)) // Пока функция проверки не "true"
				{
					cout << error_text; // Вывод текста ошибки
					cout << "Enter element[" << i+1 << "][" << j+1 << "]: ";
					getline(cin, temp); // Получить с троку целиком--std::getline(откуда,куда записать)
				}
				matrix[i][j] = stod(temp); //String to double
			}
		}

		for (int i = 0; i < len; i++)
		{
			for (int j = 0; j < wid; j++)
			{
				cout << matrix[i][j] << " ";
			}
			cout << endl;
		}

		double min = matrix[0][0], max = matrix[0][0];//Объявление и инициализация переменных принимающих значения минимума и максимума

		for (int i = 0; i < len; i++)
		{
			for (int j = 0; j < wid; j++)
			{
				if (matrix[i][j] > max) // Если текущий элемент больше чем переменная максимума, то присваиваем ей значение текущего элемента
				{
					max = matrix[i][j];
				}

				if (matrix[i][j] < min) // Аналогично
				{
					min = matrix[i][j];
				}
			}
		}

		for (int i = 0; i < len; i++) 
		{
			delete[] matrix[i];  // Удаляем массив
		}

		cout << "Min: " << min;
		cout << "\nMax: " << max;

		cout << "\nPrefer to continue working?[Y/N]"; // Запрос повтора программы
		getline(cin, user_continue); // Получить строку целиком--std::getline(откуда,куда записать)
		while (!YNCheck(user_continue)) // Пока функция проверки не "true"
		{
			cout << error_text; // Вывод текста ошибки
			cout << "Prefer to continue working?[Y/N]:";
			getline(cin, user_continue); // Получить строку целиком--std::getline(откуда,куда записать)
		}

	} while (user_continue == "Y"); // Условие повтора программы
	return 0;
}