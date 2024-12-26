#include <iostream>
#include <string>
#include <regex>

using namespace std;

string error_text = "|ERROR.INCORRECT INPUT|\n";
regex regular_el("([-]?[0-9]{1,2}[.]?[0-9]{0,1})");
regex regular_repeat("[Y]|[N]");
regex regular_operand("[+]|[*]");


bool ElCheck(string user_data) 
{
	if (regex_match(user_data.c_str(), regular_el))
		return 1;
	else
		return 0;
}

bool OperandCheck(string user_data) 
{
	if (regex_match(user_data.c_str(), regular_operand))
		return 1;
	else
		return 0;
}

bool YNCheck(string user_data)
{
	if (regex_match(user_data.c_str(), regular_repeat))
		return 1; //Возвращает функции значение "Истина"
	else
		return 0; //Возвращает функции значение "Ложь"
}

void PlusCalc(double &cur1, double &cur2, double &cur3, double &cur4, double user1, double user2, double user3, double user4)
{
	cur1 += user1;
	cur2 += user2;
	cur3 += user3;
	cur4 += user4;
}

void MultCalc(double &cur1, double &cur2, double &cur3, double &cur4, double user1, double user2, double user3, double user4)
{
	double res1, res2, res3, res4;
	res1 = cur1 * user1 + cur2 * user3;
	res2 = cur1 * user2 + cur2 * user4;
	res3 = cur3 * user1 + cur4 * user3;
	res4 = cur3 * user2 + cur4 * user4;
	cur1 = res1;
	cur2 = res2;
	cur3 = res3;
	cur4 = res4;
}

void PrintMtx(double cur1, double cur2, double cur3, double cur4)
{
	cout << "Current matrix:\n";
	cout << (double)cur1 << "  " << (double)cur2 << endl;
	cout << (double)cur3 << "  " << (double)cur4 << endl;
}

string GetOp()
{
	string operand;
	cout << "Operation[+/*]: ";
	getline(cin, operand); // Получить с троку целиком--std::getline(откуда,куда записать)

	while (!OperandCheck(operand)) // Пока функция проверки не "true"
	{
		cout << error_text; // Вывод текста ошибки
		cout << "Operation[+/*]: ";
		getline(cin, operand); // Получить с троку целиком--std::getline(откуда,куда записать)
	}
	return operand;
}

string GetContinue()
{
	string user_continue;
	cout << "Prefer to continue working?[Y/N]:"; //Запрос повтора программы
	getline(cin, user_continue); //Получить строку целиком--std::getline(откуда,куда записать)

	while (!YNCheck(user_continue)) //Цикл пока не будут получены корректные данные, проверка на соответствие регулярному выражению
	{
		cout << error_text;
		cout << "Prefer to continue working?[Y/N]:";
		getline(cin, user_continue); //Получить строку целиком--std::getline(откуда,куда записать)
	}
	return user_continue;
}

int main()
{
	double cur_mtx[2][2] = { { 0.0,0.0 },{0.0, 0.0 } };
	string user_continue;
	do //Условие повтора программы
	{

		PrintMtx(cur_mtx[0][0], cur_mtx[0][1], cur_mtx[1][0], cur_mtx[1][1]);

		string operand = GetOp();

		string str_el;
		double user_mtx[2][2];

		for (int i = 0; i < 2; i++) 
		{
			for (int j = 0; j < 2; j++)
			{
				cout << "Enter element[" << i + 1 << "][" << j + 1 << "]: ";
				getline(cin, str_el); // Получить с троку целиком--std::getline(откуда,куда записать)

				while (!ElCheck(str_el)) // Пока функция проверки не "true"
				{
					cout << error_text; // Вывод текста ошибки
					cout << "Enter element[" << i + 1 << "][" << j + 1 << "]: ";
					getline(cin, str_el); // Получить с троку целиком--std::getline(откуда,куда записать)
				}
				user_mtx[i][j] = stod(str_el); //String to double
			}
		}

		if (operand == "+")
		{
			PlusCalc(cur_mtx[0][0], cur_mtx[0][1], cur_mtx[1][0], cur_mtx[1][1], user_mtx[0][0], user_mtx[0][1], user_mtx[1][0], user_mtx[1][1]);

			PrintMtx(cur_mtx[0][0], cur_mtx[0][1], cur_mtx[1][0], cur_mtx[1][1]);
		}

		if (operand == "*")
		{
			MultCalc(cur_mtx[0][0], cur_mtx[0][1], cur_mtx[1][0], cur_mtx[1][1], user_mtx[0][0], user_mtx[0][1], user_mtx[1][0], user_mtx[1][1]);

			PrintMtx(cur_mtx[0][0], cur_mtx[0][1], cur_mtx[1][0], cur_mtx[1][1]);
		}

		user_continue = GetContinue();
		cout << endl;
	} while (user_continue == "Y");
}