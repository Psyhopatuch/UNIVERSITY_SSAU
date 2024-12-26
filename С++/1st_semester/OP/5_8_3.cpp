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
regex reg_double("[1-9][0-9]{0,8}|[0-9]{1,9}[.][0-9]{0,8}[1-9]");
regex reg_date("([0][1-9]|[1-2][0-9]|[3][0-1]).([0][1-9]|[1][0-2]).([1][9][9][1-9]|[2][0][0-9][0-9])");
regex reg_inp_str("([0-9.]{10}) ([A-Z]{3}) ([1-9][0-9]{0,8}|[0-9]{1,9}[.][0-9]{0,8}[1-9])");
regex reg_inp_str2("([0-9.]{10}) ([A-Z]{3})");

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
	cout << endl;
	return temp;
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

	double GetRate(double h) {
		return h / this->rate;
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

	cur_exchange operator=(cur_exchange& other) {
		this->SetDate(other.OutDate());
		this->SetName(other.OutName());
		this->SetRate(other.OutRate());
		return *this;
	}

	friend istream& operator>>(istream& cin, cur_exchange& object);
	friend ifstream& operator>>(ifstream& fin, vector<cur_exchange>& data);
	friend istream& operator>>(istream& cin, vector<cur_exchange>& data);
	friend ostream& operator<<(ostream& cout, cur_exchange& object);
	friend ofstream& operator<<(ofstream& fout, vector<cur_exchange>& data);
	friend ostream& operator<<(ostream& cout, vector<cur_exchange>& data);
	friend bool operator==(cur_exchange& obj1, cur_exchange& obj2);
	friend void QSort(vector<cur_exchange>& data, int left, int right);
	friend void swap(cur_exchange& obj1, cur_exchange& obj2);
	friend int VecFind(vector<cur_exchange>& data, string object);
	friend void GetRate(ifstream& fin, ofstream& fout, vector<cur_exchange>& data);
	friend void GetRate(istream& cin, ostream& cout, vector<cur_exchange>& data);
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
		cout << "MACHINE >> Repeat entry: " << endl;
		getline(cin, temp);
		temp1 = temp;
	}

	regex_match(temp, parts, reg_inp_str);

	object.SetDate(parts.str(1));
	object.SetName(parts.str(2));
	object.SetRate(parts.str(3));

	return cin;
}

ifstream& operator>>(ifstream& fin, vector<cur_exchange>& data) 
{
	string temp;
	string temp1;
	smatch parts;
	cur_exchange object;

	while (!fin.eof()) {
		getline(fin, temp);
		temp1 = temp;
		if (regex_match(temp, reg_inp_str) && CheckDate(temp1.erase(10, 50))){
			regex_match(temp, parts, reg_inp_str);
			object.SetDate(parts.str(1));
			object.SetName(parts.str(2));
			object.SetRate(parts.str(3));
			data.push_back(object);
		}
	}

	return fin;
}

istream& operator>>(istream& cin, vector<cur_exchange>& data) 
{
	string temp;
	string temp1;
	smatch parts;
	cur_exchange object;

	getline(cin, temp);
	temp1 = temp;
	while (!(regex_match(temp, reg_inp_str) && CheckDate(temp1.erase(10, 50)))) {
		cout << error;
		cout << "MACHINE >> Repeat entry: " << endl;
		getline(cin, temp);
		temp1 = temp;
	}

	regex_match(temp, parts, reg_inp_str);

	object.SetDate(parts.str(1));
	object.SetName(parts.str(2));
	object.SetRate(parts.str(3));

	data.push_back(object);

	return cin;
}

ostream& operator<<(ostream& cout, cur_exchange& object) 
{
	cout << object.OutDate() + ' ' + object.OutName() + ' ' << object.OutRate();

	return cout;
}

ofstream& operator<<(ofstream& fout, vector<cur_exchange>& data) 
{

	for (int i = 0; i < data.size(); i++) {
		fout << data[i] << endl;
	}

	return fout;
}

ostream& operator<<(ostream& cout, vector<cur_exchange>& data) 
{
	for (int i = 0; i < data.size(); i++) {
		cout << "MACHINE >> " << i + 1 << ") " << data[i] << endl;
	}
	return cout;
}

bool operator==(cur_exchange& obj1, cur_exchange& obj2)
{
	if (obj1.OutDate() == obj2.OutDate()) {
		if (obj1.OutName() == obj2.OutName()) {
			return 1;
		}
	}
	return 0;
}

int VecFind(vector<cur_exchange>& data, string temp) 
{
	string temp1 = temp;
	string temp2 = temp;
	temp1=temp1.erase(10, 10);
	temp2=temp2.erase(0, 11);

	for (int i = 0; i < data.size(); i++) {
		if (data[i].OutDate()==temp1)
			if (data[i].OutName()==temp2)
				return i;
	}
	return -1;
}

void VecDeleteEl(vector<cur_exchange>& sys_data, int n) 
{
	vector<cur_exchange> temp_vec;
	for (int b = 0; b < sys_data.size(); b++){
		if (b != n) {
			temp_vec.push_back(sys_data[b]);
		}
	}
	vector<cur_exchange>().swap(sys_data);
	sys_data.swap(temp_vec);
	vector<cur_exchange>().swap(temp_vec);
}

void DelRepeats(vector<cur_exchange>& sys_data) 
{
	for (int i = 0; i < sys_data.size() - 1; i++) {
		for (int j = sys_data.size() - 1; j > i; j--) {
			if (sys_data[i] == sys_data[j]) {
				VecDeleteEl(sys_data, i);
			}
		}
	}
}

void swap(cur_exchange &obj1, cur_exchange &obj2) 
{
	cur_exchange temp;
	temp = obj1;
	obj1 = obj2;
	obj2 = temp;
}

void QSort(vector<cur_exchange>& data, int left, int right)
{
	if (left <= right) {
		int pivot = data[(left + right) / 2].OutIntDate();
		int i = left;
		int j = right;

		while (i <= j) {

			while (data[i].OutIntDate() < pivot) i++;
			while (data[j].OutIntDate() > pivot) j--;

			if (i <= j)
				swap(data[i], data[j]);
			i++;
			j--;
		}

		QSort(data, left, j);
		QSort(data, i, right);
	}
}

ostream& operator<<(ostream& cout, vector<string>& temp)
{
	for (int i = 0; i < temp.size(); i++) {
		cout << "MACHINE >> " << i + 1 << ") " << temp[i] << endl;
	}
	return cout;
}

void GetRate(ifstream& fin, ofstream& fout, vector<cur_exchange>& data) 
{
	string temp;
	string temp1;
	smatch parts;
	int pos=-1;
	while (!fin.eof()) {

		getline(fin, temp);
		temp1 = temp;
		if (regex_match(temp, reg_inp_str) && CheckDate(temp1.erase(10, 100)))
		{
			cur_exchange object;
			regex_match(temp, parts, reg_inp_str);
			object.SetDate(parts.str(1));
			object.SetName(parts.str(2));
			object.SetRate(parts.str(3));
			data.push_back(object);
			fout << object << " |SAVED| " << endl;
			DelRepeats(data);
			QSort(data,0,data.size()-1);
		}
		else
		{
			if (regex_match(temp, reg_inp_str2) && CheckDate(temp1.erase(10, 100)))
			{

				pos=VecFind(data, temp);
				fout << temp + " |INSTALL|" << endl;
			}
			else 
			{
				if (regex_match(temp.c_str(), reg_double) && pos != - 1) 
				{
					fout << temp + " RUB = " << data[pos].GetRate(stod(temp)) << " " + data[pos].OutName() << endl;
				}
				else 
				{
					if (temp != "")
					fout << temp + " |ERROR DATA|" << endl;
				else
					fout << endl;
				}
			}
		}
	}
}

void GetRate(istream& cin, ostream& cout, vector<cur_exchange>& data) 
{
	string temp;
	string temp1;
	smatch parts;
	vector<string> out_vec;
	int pos = -1;
	do 
	{
		getline(cin, temp);
		temp1 = temp;
		if (temp == "!LIST") {
			cout << data;
		}
		if (regex_match(temp, reg_inp_str) && CheckDate(temp1.erase(10, 100)))
		{
			cur_exchange object;
			regex_match(temp, parts, reg_inp_str);
			object.SetDate(parts.str(1));
			object.SetName(parts.str(2));
			object.SetRate(parts.str(3));
			data.push_back(object);
			DelRepeats(data);
			QSort(data, 0, data.size() - 1);
			cout <<"MACHINE >> " << object << " |SAVED| " << endl;
		}
		else
		{
			if (regex_match(temp, reg_inp_str2) && CheckDate(temp1.erase(10, 100)))
			{
				pos = VecFind(data, temp);
				
				if (pos != -1) {
					cout << "MACHINE >> " << "|INSTALL|" << endl;
				}
				else {
					cout << "MACHINE >> " << temp + " |ERROR DATA|" << endl;
				}
			}
			else
			{
				if (regex_match(temp.c_str(), reg_double) && pos != -1)
				{
					out_vec.push_back(temp + " RUB = " + data[pos].GetRate(temp) + " " + data[pos].OutName());
				}
				else
				{
					if(temp != "!STOP" && temp != "!LIST")
					 cout << "MACHINE >> " << temp + " |ERROR DATA|" << endl;
				}
			}


		}
	} while (temp != "!STOP");
	cout << out_vec;
	vector<string>().swap(out_vec);
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
	while (!regex_match(user_data.c_str(), reg_var)){
		cout << error;
		cout << what;
		getline(cin, user_data);
	}
	return user_data; //Возвращает функции значение считанного
}

int main() {
	string rep;

	do {
		system("cls");

		string temp;
		cout << fixed << setprecision(4);
		vector<cur_exchange> sys_data;

		ifstream sys_in("SYS_DATA.txt", ios_base::in);
		if (sys_in.is_open()) {
			sys_in >> sys_data;
			sys_in.close();
			DelRepeats(sys_data);
			QSort(sys_data, 0, sys_data.size() - 1);
		}

		cur_exchange object;

		cout << "MACHINE >> 1 - clickboard completion\n";
		cout << "MACHINE >> 2 - file completion\n";

		int variant = stoi(GetVar("MACHINE >> Enter completion variant(1 | 2): "));

		switch (variant)
		{
		case(1):

			cout << "MACHINE >> Enter data in format[date(DD.MM.YYYY) name(YYY) rate(double)](split information with spase)" << endl;
			cout << "to push_back in saved list and continue or enter data in format[date(DD.MM.YYYY) name(YYY)]" << endl;
			cout << "to get rate from saved list: " << endl;
			cout << "MACHINE >> |TO GET RATE ENTER !STOP|" << endl;
			cout << "MACHINE >> |TO GET SAVED LIST ENTER !LIST|" << endl;

			GetRate(cin, cout, sys_data);

			break;

		case(2):

			temp = GetWord("MACHINE >> Enter file name: ");
			ifstream fin(temp + ".txt", ios_base::in);

			if (fin.is_open()) {
				cout << "MACHINE >> |File connected succesfully|\n";

				ofstream fout(temp + "(compleated).txt");
				fout << fixed << setprecision(4);

				GetRate(fin, fout, sys_data);

				cout << "MACHINE >> |Succesfully|\n";

				fin.close();
				fout.close();

			}
			break;
		}

		ofstream sys_out("SYS_DATA.txt");
		if (sys_out.is_open()) {
			sys_out << sys_data;
			sys_out.close();
		}
		vector<cur_exchange>().swap(sys_data);
		rep = GetYN("MACHINE >> Prefer to continue working?[Y / N]: ");

	} while (rep == "y" || rep == "Y");
	
}