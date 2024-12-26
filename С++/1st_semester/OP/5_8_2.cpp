#include<iostream>
#include<fstream>
#include<regex>
#include<iomanip>
#include<string>

using namespace std;

string error = "|ERROR. Incorrect input|\n";
regex reg_var("[12]{1}");
regex reg_YN("[Yy]|[Nn]");
regex reg_word("[A-z0-9_]+");
regex reg_int("[1-9][0-9]{0,8}");
regex reg_double("[1-9][0-9]{0,8}|[0-9]{1,9}[.][0-9]{0,8}[1-9]");
regex reg_date("([0][1-9]|[1-2][0-9]|[3][0-1]).([0][1-9]|[1][0-2]).([1][9][9][1-9]|[2][0][0-9][0-9])");
regex reg_inp_str("([0-9.]{10}) ([A-Z]{3}) ([1-9][0-9]{0,8}|[0-9]{1,9}[.][0-9]{0,8}[1-9])");

int HowMuchDayInMounth(int MM, int YYYY) {
	switch (MM)
	{
	case(1):
		return 31;
		break;
	case(2):
		if (YYYY % 4 == 0)
			return 29;
		else
			return 28;
		break;
	case(3):
		return 31;
		break;
	case(4):
		return 30;
		break;
	case(5):
		return 31;
		break;
	case(6):
		return 30;
		break;
	case(7):
		return 31;
		break;
	case(8):
		return 31;
		break;
	case(9):
		return 30;
		break;
	case(10):
		return 31;
		break;
	case(11):
		return 30;
		break;
	case(12):
		return 31;
		break;
	default:
		cerr << "INCORRECT MOUNTH!";
		return 0;
		break;
	}
}

bool CheckDate(string date) {
	smatch parts;
	if (!regex_match(date, reg_date))
		return 0;
	regex_match(date, parts, reg_date);
	if (HowMuchDayInMounth(stoi(parts.str(2)), stoi(parts.str(3))) < stoi(parts.str(1)))
		return 0;
	return 1;
}

string GetInt(string what) // ‘ункци€, приенимающа€ на вход текст ошибки/просто текст вывода
{
	string temp;
	cout << what;
	getline(cin, temp);
	while (!regex_match(temp.c_str(), reg_int)) //÷икл пока не будут получены корректные данные, проверка на соответствие регул€рному выражению
	{
		cout << error;
		cout << what;
		getline(cin, temp);
	}
	cout << endl;
	return temp; 
}

class cur_exchange {
private:
	string date;
	string name;
	double rate;
public:

	void SetDate(string date) {
		this->date = date;
	}

	void SetName(string name) {
		this->name = name;
	}

	void SetRate(string rate) {
		this->rate = stod(rate);
	}

	string OutDate() {
		return this->date;
	}

	string OutName() {
		return this->name;
	}

	double OutRate() {
		return this->rate;
	}
	
	double GetRate(double h){
		return h / this->rate;
	}

	string GetRate(string h) {
		return to_string(stod(h) / this->rate);
	}

	friend ostream& operator<<(ostream& cout, cur_exchange& object);
	friend istream& operator>>(istream& cin, cur_exchange& object);

};

istream& operator>>(istream& cin, cur_exchange& object) {
	string temp;
	string temp1;

	smatch parts;
	getline(cin, temp);
	temp1 = temp;
	while (!(regex_match(temp, reg_inp_str) && CheckDate(temp1.erase(10, 50)))) {
		cout << error;
		cout << "Repeat entry: " << endl;
		getline(cin, temp);
		temp1 = temp;
	}

	regex_match(temp, parts, reg_inp_str);

	object.SetDate(parts.str(1));
	object.SetName(parts.str(2));
	object.SetRate(parts.str(3));

	return cin;
}

ostream& operator<<(ostream& cout, cur_exchange& object) {
	cout << object.OutDate() + ' ' + object.OutName() + ' ' << object.OutRate();
	return cout;
}

void GetRate(ifstream& fin, ofstream& fout, cur_exchange object) {
	string temp;
	string temp1;
	smatch parts;
	bool flag = 0;
	while (!fin.eof()) {
		getline(fin,temp);
		temp1 = temp;
		if (regex_match(temp, reg_inp_str) && CheckDate(temp1.erase(10, 50))) 
		{
			regex_match(temp, parts, reg_inp_str);
			flag = 1;
			object.SetDate(parts.str(1));
			object.SetName(parts.str(2));
			object.SetRate(parts.str(3));
			fout << object <<endl;
		}
		else 
		{
			if (regex_match(temp.c_str(), reg_double) && flag == 1) {
				fout << temp + " RUB = " << object.GetRate(stod(temp)) << " " + object.OutName() << endl;
			}
			else {
				if (temp != "")
					fout << temp + " |ERROR DATA|" << endl;
				else
					fout << endl;
			}
		}
	}
}

string GetWord(string what) 
{
	string temp;
	cout << what;
	getline(cin, temp);
	while (!regex_match(temp.c_str(), reg_word)) {
		cout << error;
		cout << what;
		getline(cin, temp);
	}
	return temp;
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

string GetDouble(string what)
{
	string temp;
	cout << what;
	getline(cin, temp);
	while (!regex_match(temp.c_str(), reg_double)) {
		cout << error;
		cout << what;
		getline(cin, temp);
	}
	return temp;
}

string GetVar(string what)
{
	string user_data;
	cout << what;
	getline(cin, user_data);
	while (!regex_match(user_data.c_str(), reg_var)) //÷икл пока не будут получены корректные данные, проверка на соответствие регул€рному выражению
	{
		cout << error;
		cout << what;
		getline(cin, user_data);
	}
	return user_data; //¬озвращает функции значение считанного
}

int main() {
	string rep;
	do {

		cout << fixed << setprecision(4);

		int steps=0;
		cur_exchange object;
		cur_exchange object2;

		cout << "//1 - clickboard completion\n";
		cout << "//2 - file completion\n";

		int variant = stoi(GetVar("Enter completion variant(1 | 2): "));

		switch (variant)
		{
		case(1):
			cout << "Enter data in format[date(DD.MM.YYYY) name(YYY) rate(double)](split information with spase) :" << endl;
			cin >> object;
			steps = stoi(GetInt("Enter steps count: "));
			for (int i = 0; i < steps; i++) {
				double currency = stod(GetDouble("Enter RUB count: "));
				cout << currency << " RUB = " << object.GetRate(currency) << " " + object.OutName() << endl << endl;
			}

			break;
		case(2):
			string temp = GetWord("Enter file name: ");
			ifstream fin(temp + ".txt", ios_base::in);
			
			if (fin.is_open()) {
				cout << "|File connected succesfully|\n";

				ofstream fout(temp + "(compleated).txt");
				fout << fixed << setprecision(4);

				GetRate(fin, fout, object);

				cout << "|Succesfully|\n";

				fin.close();
				fout.close();
			}
			break;
		}
		
		rep = GetYN("Prefer to continue working?[Y / N]: ");
	} while (rep == "y" || rep == "Y");
}