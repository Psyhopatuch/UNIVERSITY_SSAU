#include<iostream>
#include<string>
#include<regex>
#include<cmath>

using namespace std;

string error_text = "|ERROR.Incorect input|\n";
regex regular_x("[-][0][.][2][0-4][0-9]|[-][0][.][2]|[-][0][.][0-1][0-9]{0,1}|[0]|[0][.][0-4][0-9]{0,1}|[0][.][5]");
regex regular_accuracy("([0-9]{1,3}|[0-9][.][0-9]{0,4})");
regex regular_repeat("[Y]|[N]");

bool YNCheck(string user_data)
{
	if (regex_match(user_data.c_str(), regular_repeat))
		return 1; //Возвращает функции значение "Истина"
	else
		return 0; //Возвращает функции значение "Ложь"
}

bool XCheck(string user_data)
{
	if (regex_match(user_data.c_str(), regular_x))
		return 1;
	else
		return 0;
}


bool AccuracyCheck(string user_data)
{
	if (regex_match(user_data.c_str(), regular_accuracy))
		return 1;
	else
		return 0;
}

double An(double x, int n)
{
	//if (x != 0.5)
	{
		double An = pow(-1, n) * pow(2*x,2*n-1) / (2 * n - 1);
		return An;
	}
	/*else
	{ 
		double An = pow(-1, n) / (2 * n - 1);
		return An;
	}*/
}

double Accuracy(double x, int n, double S)
{
	double accuracy = abs(An(x, n) / S);
	return accuracy;
}

void AllCalcPrint(double accuracy, double x)
{
	double S = atan(2);

	if ((int)accuracy == accuracy)
	{ 
		for(int n=1;n<=accuracy;n++)
		{ 
			S += An(x,n);
			cout << "Number of iteration: " << n << endl;
			cout << "Last summed term: " << An(x, n) << endl;
			cout << "Current summ: " << S << endl;
			cout << "Current accuracy: " << Accuracy(x, n+1, S) << endl << endl;
		}
	}
	else
	{
		int n = 0;
		do
		{
			n += 1;
			S += An(x, n);
			cout << "Number of iteration: " << n << endl;
			cout << "Last summed term: " << An(x, n) << endl;
			cout << "Current summ: " << S << endl;
			cout << "Current accuracy: " << Accuracy(x, n+1, S) << endl << endl;
		} while (!(Accuracy(x, n+1, S) <= accuracy));

	}
}

int main()
{
	string user_continue;
	do //Условие повтора программы
	{
		string temp;

		cout << "Enter x: ";
		getline(cin, temp); //Получить строку целиком--std::getline(откуда,куда записать)
		while (!XCheck(temp))
		{
			cout << error_text;
			cout << "Enter x: ";
			getline(cin, temp); //Получить строку целиком--std::getline(откуда,куда записать
		}
		double x = stod(temp);


		cout << "Enter accuracy: ";
		getline(cin, temp); //Получить строку целиком--std::getline(откуда,куда записать)
		while (!AccuracyCheck(temp))
		{
			cout << error_text;
			cout << "Enter accuracy: ";
			getline(cin, temp); //Получить строку целиком--std::getline(откуда,куда записать
		}
		double accuracy = stod(temp);

		AllCalcPrint(accuracy, x);

		cout << "\nPrefer to continue working?[Y/N]:"; //Запрос повтора программы
		getline(cin, user_continue); //Получить строку целиком--std::getline(откуда,куда записать)
		while (!YNCheck(user_continue)) //Цикл пока не будут получены корректные данные, проверка на соответствие регулярному выражению
		{
			cout << error_text;
			cout << "Prefer to continue working?[Y/N]:";
			getline(cin, user_continue); //Получить строку целиком--std::getline(откуда,куда записать)
		}

	} while (user_continue == "Y");
	return 0;
}
