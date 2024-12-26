#include<iostream>
#include<fstream>
#include<regex>
#include<iomanip>
#include<string>

using namespace std;

string error = "ERROR_MACHINE >> |ERROR. Incorrect input|\n";
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
		if (YYYY % 4 == 0 && YYYY % 100 != 0 || YYYY % 400 == 0)
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
		cerr << "ERROR_MACHINE >> |INCORRECT MOUNTH!|";
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
public:
	cur_exchange() {
		date = "0";
		name = "0";
		rate = 0;
	}
	bool check() {
		return date != "0" && name != "0" && rate!=0;
	}
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

public:
	contract() {
		num = 0;
		sum = 0;
		obj.SetDate("0");
		obj.SetName("0");
		obj.SetRate(0);
	}
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
		this->obj=other.obj;
		return *this;
	}

	bool check() {
		return num != 0 && sum != 0 && obj.OutDate() != "0" && obj.OutName() != "0" && obj.OutRate() != 0;
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

bool operator==(contract& obj1, contract& obj2)
{
	if (obj1.OutNum() == obj2.OutNum())
		return 1;

	return 0;
}

void VecDeleteEl(vector<contract>& sys_data, int n)
{
	vector<contract> temp_vec;
	for (int b = 0; b < sys_data.size(); b++) {
		if (b != n) {
			temp_vec.push_back(sys_data[b]);
		}
	}
	vector<contract>().swap(sys_data);
	sys_data.swap(temp_vec);
	vector<contract>().swap(temp_vec);
}

void DelRepeats(vector<contract>& sys_data)
{
	for (int i = 0; i < sys_data.size(); i++) {
		for (int j = sys_data.size() - 1; j > i ; j--) {
			if (sys_data[i] == sys_data[j]) {
				VecDeleteEl(sys_data, i);
			}
		}
	}
}

void swap(contract& obj1, contract& obj2)
{
	contract temp;
	temp = obj1;
	obj1 = obj2;
	obj2 = temp;
}

void QSort(vector<contract>& data, int left, int right)
{
	if (left <= right) {
		int pivot = data[(left + right) / 2].OutNum();
		int i = left;
		int j = right;

		while (i <= j) {

			while (data[i].OutNum() < pivot) i++;
			while (data[j].OutNum() > pivot) j--;

			if (i <= j)
				swap(data[i], data[j]);
			i++;
			j--;
		}

		QSort(data, left, j);
		QSort(data, i, right);
	}
}

istream& operator>>(istream& cin, contract& obj)
{
	string temp;
	cur_exchange object;

	cout << "MACHINE >> Enter num: ";
	getline(cin, temp);
	while (!regex_match(temp, reg_int)) {
		cout << error;
		cout << "MACHINE >> Enter num: ";
		getline(cin, temp);
	}

	obj.SetNum(stoi(temp));

	cout << "MACHINE >> Enter sum: ";
	getline(cin, temp);
	while (!regex_match(temp, reg_double)) {
		cout << error;
		cout << "MACHINE >> Enter sum: ";
		getline(cin, temp);
	}

	obj.SetSum(stod(temp));

	cout << "MACHINE >> Enter cur_exchange: ";
	cin >> object;
	obj.SetCur_exchange(object);

	return cin;
}

ifstream& operator>>(ifstream& fin, contract& obj) {
	string temp;
	cur_exchange object;

	do {
		getline(fin, temp);
	} while (!fin.eof() && !regex_match(temp, reg_int));
	if (regex_match(temp, reg_int))
		obj.SetNum(stoi(temp));


	if (!fin.eof()){
		getline(fin, temp);
		if (regex_match(temp, reg_double))
			obj.SetSum(stod(temp));
	}

	if (!fin.eof()) {
		fin >> object;
		if (object.check())
			obj.SetCur_exchange(object);
	}
	
	return fin;
}

ostream& operator<<(ostream& cout, contract& object)
{
	cout << "MACHINE >> " << object.OutNum() << endl;
	cout << "MACHINE >> " << object.OutSum() << endl;
	cout << "MACHINE >> " << object.obj << endl;

	return cout;
}

ofstream& operator<<(ofstream& fout, contract& object)
{
	fout << object.OutNum() << endl;
	fout << object.OutSum() << endl;
	fout << object.obj << endl;

	return fout;
}

ifstream& operator>>(ifstream& fin, vector<contract>& data) {
	
	
	while (!fin.eof()) {
		contract object;
		fin >> object;
		if (object.check())
			data.push_back(object);
		else {
			cout << "MACHINE >> |DATA ERROR FOUND|\n";
			return fin;
		}
	}
	cout << "MACHINE >> |IMPORTED|\n\n";
	return fin;
}

ostream& operator<<(ostream& cout, vector<contract>& obj) {
	for (int i = 0; i < obj.size(); i++) {
		cout << obj[i] << endl;
	}
	return cout;
}

ofstream& operator<<(ofstream& fout, vector<contract>& obj) {
	for (int i = 0; i < obj.size(); i++) {
		fout << obj[i] << endl;
	}
	return fout;
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
	while (!regex_match(user_data.c_str(), reg_var)) {
		cout << error;
		cout << what;
		getline(cin, user_data);
	}
	return user_data;
}

string GetInt(string what)
{
	string user_data;
	cout << what;
	getline(cin, user_data);
	while (!regex_match(user_data.c_str(), reg_int)) {
		cout << error;
		cout << what;
		getline(cin, user_data);
	}
	return user_data; 
}

int main() {
	string rep;
	vector<contract> contracts;

	do {
		system("cls");

		contract object;
		string temp;

		cout << fixed << setprecision(4);

		cout << "MACHINE >> 1 - console completion\n";
		cout << "MACHINE >> 2 - file completion\n";

		int variant1 = stoi(GetVar("MACHINE >> Enter completion variant(1 | 2): "));


		cout << "MACHINE >> 1 - console out\n";
		cout << "MACHINE >> 2 - file out\n";

		int variant2 = stoi(GetVar("MACHINE >> Enter output variant(1 | 2): "));

		int steps;


		switch (variant1)
		{
		case(1):
			steps = stoi(GetInt("MACHINE >> Enter steps count: "));
			cout << endl;
			cout << "MACHINE >> Enter data in format: " << endl;
			cout << "[Num](Enter)" << endl;
			cout << "[Sum](Enter)" << endl;
			cout << "[date(DD.MM.YYYY) name(YYY) rate(double)](split information with spase)(Enter)" << endl << endl;

			for (steps; steps > 0; steps--) {
				cin >> object;
				contracts.push_back(object);
				DelRepeats(contracts);
			}
			cout << "---------------------------------------------------------------------------------------------\n";
			QSort(contracts, 0, contracts.size() - 1);
			switch (variant2)
			{
			case(1):
				cout << contracts;

				break;

			case(2):
				ofstream fout("MACHINE_OUT.txt");
				if (fout.is_open())
					fout << contracts;
				fout.close();
				cout << "MACHINE >> |OUTPUTED|\n";

				break;
			}

			break;

		case(2):

			string temp = GetWord("MACHINE >> Enter file name: ");
			ifstream fin(temp + ".txt", ios_base::in);
			if (fin.is_open()) {
				fin >> contracts;
				DelRepeats(contracts);
				QSort(contracts,0,contracts.size()-1);
				fin.close();
				switch (variant2)
				{
				case(1):
					cout << contracts;

					break;

				case(2):
					ofstream fout("MACHINE_OUT.txt");
					if (fout.is_open())
						fout << contracts;
					fout.close();
					cout << "MACHINE >> |OUTPUTED|\n";

					break;
				}

			}

			break;
		}

		rep = GetYN("MACHINE >> Prefer to continue working?[Y / N]: ");

	} while (rep == "y" || rep == "Y");
	vector<contract>().swap(contracts);
}