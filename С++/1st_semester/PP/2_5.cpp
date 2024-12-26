#include<iostream>
#include<string>
#include<regex>
#include<cmath>

using namespace std;

string error_text = "|ERROR.Incorect input|\n";
regex regular_x("[-]?[0][.]?[0-9]{0,9}|[-]?[1]");
regex regular_accuracy("[0-9]{1,2}[.]?[0-9]{0,7}");
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
	{
		double An = pow(-1, n + 1) * pow(x, 2 * n) / (4*n*n-2*n);
		return An;
	}
}

double Accuracy(double x, int n, double S)
{
	double accuracy = abs(An(x, n) / S);
	return accuracy;
}

void IntAccCalcPrint(double accuracy, double x, vector<double>& vec)
{
	double S = 0;

	if (vec[0] == x)
	{
		int k = 0;
		for (int n = 1; n < (vec.size() - 1) && k < accuracy; n = n + 2)
		{
			k = k + 1;
			cout << "[Saved]Number of iteration: " << k << endl;
			cout << "Last summed term: " << vec[n] << endl;
			cout << "Current summ: " << vec[n + 1] << endl;
			cout << "Current accuracy: " << Accuracy(x, k + 1, vec[n + 1]) << endl << endl;
		}
		S += vec.back();
		for (int n = 1 + (vec.size() - 1) / 2; n <= accuracy; n++)
		{
			S += An(x, n);
			cout << "Number of iteration: " << n << endl;
			cout << "Last summed term: " << An(x, n) << endl;
			vec.push_back(An(x, n));
			cout << "Current summ: " << S << endl;
			vec.push_back(S);
			cout << "Current accuracy: " << Accuracy(x, n + 1, S) << endl << endl;
		}
	}
	else
	{
		vec.clear();
		vec.push_back(x);
		for (int n = 1; n <= accuracy; n++)
		{
			S += An(x, n);
			cout << "Number of iteration: " << n << endl;
			cout << "Last summed term: " << An(x, n) << endl;
			vec.push_back(An(x, n));
			cout << "Current summ: " << S << endl;
			vec.push_back(S);
			cout << "Current accuracy: " << Accuracy(x, n + 1, S) << endl << endl;
		}
	}
	
}

void DoubleAccCalcPrint(double accuracy, double x, vector<double>& vec)
{
	double S = 0;

	if (vec[0] == x)
	{
		int k = 0;
		int n = 1;

		do
		{
			
			k = k + 1;
			cout << "[Saved]Number of iteration: " << k << endl;
			cout << "Last summed term: " << vec[n] << endl;
			cout << "Current summ: " << vec[n + 1] << endl;
			cout << "Current accuracy: " << Accuracy(x, k + 1, vec[n + 1]) << endl << endl;
			n = n + 2;

		} while (n < (vec.size() - 1) && !(Accuracy(x, k + 1, vec[n + 1]) <= accuracy));
		
		S += vec.back();
		n = k;

		while (!(Accuracy(x, n + 1, S) <= accuracy))
		{
			n += 1;
			S += An(x, n);
			cout << "Number of iteration: " << n << endl;
			cout << "Last summed term: " << An(x, n) << endl;
			vec.push_back(An(x, n));
			cout << "Current summ: " << S << endl;
			vec.push_back(S);
			cout << "Current accuracy: " << Accuracy(x, n + 1, S) << endl << endl;
		}
	}
	else
	{
		vec.clear();
		vec.push_back(x);
		int n = 0;
		do
		{
			n += 1;
			S += An(x, n);
			cout << "Number of iteration: " << n << endl;
			cout << "Last summed term: " << An(x, n) << endl;
			vec.push_back(An(x, n));
			cout << "Current summ: " << S << endl;
			vec.push_back(S);
			cout << "Current accuracy: " << Accuracy(x, n + 1, S) << endl << endl;
		} while (!(Accuracy(x, n + 1, S) <= accuracy));
	}
}

void AllCalcPrint(double accuracy, double x, vector<double> &vec)
{
	if ((int)accuracy == accuracy)
		IntAccCalcPrint(accuracy, x, vec);
	else
		DoubleAccCalcPrint(accuracy, x, vec);
}



int main()
{
	vector<double> data;
	data.push_back(2);
	string user_continue;
	do //Условие повтора программы
	{
		string temp;

		cout << "Enter x(-1<=x<=1): ";
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


		AllCalcPrint(accuracy, x, data);
		

		cout << "\nPrefer to continue working?[Y/N]:"; //Запрос повтора программы
		getline(cin, user_continue); //Получить строку целиком--std::getline(откуда,куда записать)
		while (!YNCheck(user_continue)) //Цикл пока не будут получены корректные данные, проверка на соответствие регулярному выражению
		{
			cout << error_text;
			cout << "Prefer to continue working?[Y/N]:";
			getline(cin, user_continue); //Получить строку целиком--std::getline(откуда,куда записать)
		}

	} while (user_continue == "Y");
	data.clear();
	return 0;
}