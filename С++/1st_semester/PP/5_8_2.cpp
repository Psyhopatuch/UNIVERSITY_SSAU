#include<iostream>
#include<fstream>
#include<regex>
#include<iomanip>
#include<string>

using namespace std;

string error = "MACHINE >> |ERROR. Incorrect input|\n";
regex reg_var("[12]{1}");
regex reg_YN("[Yy]|[Nn]");
regex reg_word("[A-z0-9_]+");
regex reg_int("[1-9][0-9]{0,8}");
//regex reg_double("[1-9][0-9]{0,8}|[0-9]{1,9}[.][0-9]{0,8}[1-9]");
regex reg_double("[1-9][0-9]{0,8}|[0-9]{1,9}[.][0-9]{0,8}[1-9]");
regex reg_date("([0][1-9]|[1-2][0-9]|[3][0-1]).([0][1-9]|[1][0-2]).([1][9][9][1-9]|[2][0][0-9][0-9])");
regex reg_inp_str("([0-9.]{10}) ([A-Z]{3}) ([1-9][0-9]{0,8}|[0-9]{1,9}[.][0-9]{0,8}[1-9])");
regex reg_inp_str2("([1-9][0-9]{0,8}) ([1-9][0-9]{0,8}|[0-9]{1,9}[.][0-9]{0,8}[1-9])");

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
		cerr << "ERROR_MACHINE >> INCORRECT MOUNTH!";
		return -1;
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

class cur_exchange {
private:
	string date;
	string name;
	double rate;
protected:

	void SetDate(string date) {
		this->date = date;
	}

	void SetName(string name) {
		this->name = name;
	}

	void SetRate(string rate) {
		this->rate = stod(rate);
	}

	void SetRate(double rate) {
		this->rate = rate;
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

	string OutAll() {
		return date + ' ' + name + ' ' + to_string(rate);
	}

	double GetRate(double h) {
		return h / this->rate;
	}

	long double GetRateToRub(long double h) {
		return h * this->rate;
	}

	int OutIntDate() {
		string temp;
		smatch parts;
		regex_match(this->date, parts, reg_date);
		temp = parts.str(3) + parts.str(2) + parts.str(1);
		return stoi(temp);
	}

	string GetRate(string h) {
		return to_string(stod(h) / this->rate);
	}

	string GetRateToRub(string h) {
		return to_string(stod(h) * this->rate);
	}

	cur_exchange operator=(cur_exchange& other) {
		this->SetDate(other.OutDate());
		this->SetName(other.OutName());
		this->SetRate(other.OutRate());
		return *this;
	}

	friend class contract;
	friend istream& operator>>(istream& cin, cur_exchange& object);
	friend ifstream& operator>>(ifstream& fin, cur_exchange& object);
	friend ostream& operator<<(ostream& cout, cur_exchange& object);
	friend ofstream& operator<<(ofstream& fout, cur_exchange& object);
};

istream& operator>>(istream& cin, cur_exchange& object)
{
	string temp;
	string temp1;
	smatch parts;
	getline(cin, temp);
	temp1 = temp;

	while (!(regex_match(temp, reg_inp_str) && CheckDate(temp1.erase(10, 50)))) {
		cout << error;
		cout << "MACHINE >> Repeat cur_exchange entry: ";
		getline(cin, temp);
		temp1 = temp;
	}

	regex_match(temp, parts, reg_inp_str);

	object.SetDate(parts.str(1));
	object.SetName(parts.str(2));
	object.SetRate(parts.str(3));

	return cin;
}

ifstream& operator>>(ifstream& fin, cur_exchange& object)
{
	string temp;
	string temp1;
	smatch parts;
	getline(fin, temp);
	temp1 = temp;

	if (regex_match(temp, reg_inp_str) && CheckDate(temp1.erase(10, 50))) {

		regex_match(temp, parts, reg_inp_str);
		object.SetDate(parts.str(1));
		object.SetName(parts.str(2));
		object.SetRate(parts.str(3));
	}

	return fin;
}

ostream& operator<<(ostream& cout, cur_exchange& object)
{
	cout << object.OutDate() + ' ' + object.OutName() + ' ' << object.OutRate();

	return cout;
}

ofstream& operator<<(ofstream& fout, cur_exchange& object)
{
	fout << object.OutDate() + ' ' + object.OutName() + ' ' << object.OutRate();

	return fout;
}

class contract {
private:
	int num;
	long double sum;
	cur_exchange obj;

protected:
	/*contract(int num, double sum, cur_exchange other){

	}*/

	void SetNum(int num) {
		this->num = num;
	}

	void SetSum(long double sum) {
		this->sum = sum;
	}

	void SetCur_exchange(cur_exchange other) {

		this->obj = other;
		sum = (double)obj.GetRateToRub(sum);
		obj.SetName(other.OutName() + " -> RUB");
	}

	int OutNum() {
		return num;
	}

	long double OutSum() {
		return sum;
	}

	cur_exchange OutCur_exchange() {
		return obj;
	}

	contract operator=(contract& other) {
		this->SetNum(other.OutNum());
		this->SetSum(other.OutSum());
		this->SetCur_exchange(other.OutCur_exchange());
		return *this;
	}

	friend bool operator==(contract& obj1, contract& obj2);
	friend void swap(contract& obj1, contract& obj2);
	friend void QSort(vector<contract>& data, int left, int right);
	friend istream& operator>>(istream& cin, contract& obj);
	friend ostream& operator<<(ostream& cout, contract& object);
	friend ifstream& operator>>(ifstream& fin, contract& obj);
	friend ofstream& operator<<(ofstream& fout, contract& object);
	friend ifstream& operator>>(ifstream& fin, vector<contract>& data);
};