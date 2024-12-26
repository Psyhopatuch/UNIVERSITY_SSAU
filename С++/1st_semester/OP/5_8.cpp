#include<iostream>
#include<fstream>
#include<regex>

using namespace std;

regex reg_YN("[Yy]|[Nn]");
regex reg_int("[1-9][0-9]{0,8}");
regex reg_double("[1-9][0-9]{0,8}|[0-9]{1,9}[.][0-9]{0,8}[1-9]");

regex Variant("[1-3]{1}"); //Регулярное выражение
regex reg_inp_str("([0-2][0-9]|[3][1])[./,]([0][0-9]|[1][1-2])[./,]([2][0][0][0-9]|[2][0][1][0-9]|[2][0][2][0-3]) ([A-Z]{3}) ([1-9][0-9]{0,8}|[0-9]{1,9}[.][0-9]{0,8}[1-9])");
string error = "|ERROR. Incorrect input|\n";

class exchangwe {
private:
	string date;
	string name;
	double rate;
public:

	friend ostream& operator<<(ostream& cout, exchangwe& object);
	friend istream& operator>>(istream& cin, exchangwe& object);

	string OutData() {
		return date + ' ' + name + ' ' + to_string(rate);
	}

	void InData(string date, string name, string rate) {

		this->date = date;
		this->name = name;
		this->rate = stod(rate);

	}

	void InData(string rate) {
		this->rate = stod(rate);
	}

	exchangwe(string date, string name, string rate) {
		InData(date, name, rate);
	}

	exchangwe() {
		
	}
	void Rate(double &RUB) {
		RUB = RUB / rate;
	}

};

ostream& operator<<(ostream& cout, exchangwe& object) {
	cout << object.OutData();
	return cout;
}
ofstream& operator<<(ofstream& cout, exchangwe& object) {
	cout << object.OutData();
	return cout;
}

istream& operator>>(istream& cin, exchangwe& object) {

	string temp;
	string date;
	string name;
	string rate;

	getline(cin, temp);
	while (!(regex_match(temp, reg_inp_str)&&!regex_match(temp.erase(11,EOF),)) {
		cout << error;
		cout << "Repeat entry: ";
		getline(cin, temp);
	}

	for (int i = 0; i < 10; i++) {
		date.push_back(temp[i]);
	}

	for (int i = 11; i < 14; i++) {
		name.push_back(temp[i]);
	}
	int i = 15;

	while (i < temp.size()) {
		rate.push_back(temp[i]);
		i++;
	}

	object.InData(date, name, rate);

	return cin;
}

string GetVar(string what)
{
	string user_data;
	cout << what;
	getline(cin, user_data);
	while (!regex_match(user_data.c_str(), reg_var)) //Цикл пока не будут получены корректные данные, проверка на соответствие регулярному выражению
	{
		cout << error;
		cout << what;
		getline(cin, user_data);
	}
	return user_data; //Возвращает функции значение считанного
}

string GetYN(string what)
{
	string temp;
	cout << what;
	getline(cin, temp);
	while (!regex_match(temp.c_str(), reg_YN)) {
		cout << error;
		cout << what;
		getline(cin, temp);
	}
	cout << endl;
	return temp;
}

string GetInt(string what) // Функция, приенимающая на вход текст ошибки/просто текст вывода
{
	string temp;
	cout << what;
	getline(cin, temp);
	while (!regex_match(temp.c_str(), reg_int)) //Цикл пока не будут получены корректные данные, проверка на соответствие регулярному выражению
	{
		cout << error;
		cout << what;
		getline(cin, temp);
	}
	return temp; //Возвращает функции значение считанного в типе int
}

int main() {
	string rep;

	do{
		exchangwe object;
		//ifstream fin(".txt", ios_base::in);
		cout << "Enter data in format[date(DD.MM.YYYY) name(YYY) rate(double)](split information with spase) :" << endl;
		cin >> object;
		int steps = stoi(GetInt("Enter steps count: "));

		for (int i = 0; i < steps; i++) {

		}
			 


		rep = GetYN("Prefer to continue working?[Y / N]: ");
	} while (rep == "y" || rep == "Y");
}