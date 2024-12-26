#include<iostream>
#include<fstream>
#include<regex>

using namespace std;

class my_string {

private:
	//int pointer = 0;
	int n = 1;

public:

	char* str = new char[n];

	void push_back(char h) {

		char* temp_str = new char[n];
		for (int i = 0; i < n - 1; i++) {
			temp_str[i] = str[i];
		}
		temp_str[n - 1] = h;

		for (int i = 0; i <= n - 1; i++) {
			str[i] = temp_str[i];

		}
		n++;

		delete[] temp_str;
	}

	void push_back(int h) {

		char* temp_str = new char[n];
		for (int i = 0; i < n - 1; i++) {
			temp_str[i] = str[i];
		}
		temp_str[n - 1] = static_cast<char>(h);

		for (int i = 0; i <= n - 1; i++) {
			str[i] = temp_str[i];

		}
		n++;

		delete[] temp_str;
	}

	int size() {
		return n - 1;
	}

};


ostream& operator<<(ostream& cout, my_string& object) {
	for (int i = 0; i < object.size(); i++) {
		cout << (char)object.str[i];
	}
	return cout;
}

istream& operator>>(istream& cin, my_string& object) {
	char temp;
	while (!cin.eof()) {
		cin >> temp;
		object.push_back(temp);
	}
	return cin;
}

ifstream& operator>>(ifstream& fin, my_string& object) {
	char temp;
	while (!fin.eof()) {
		fin >> temp;
		object.push_back((char)temp);
	}
	return fin;
}

ofstream& operator<<(ofstream& fout, my_string& object) {
	for (int i = 0; i < object.size(); i++) {
		fout << (char)object.str[i];
	}
	return fout;
}


regex reg_YN("[Yy]|[Nn]");
regex reg_word("[A-z0-9_]+");
string error = "|ERROR. Incorrect input|\n";



string GetWord(string what) {
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
	while (!regex_match(temp.c_str(), reg_YN)) //÷икл пока не будут получены корректные данные, проверка на соответствие регул€рному выражению
	{
		cout << error;
		cout << what;
		getline(cin, temp);
	}
	return temp;
}

void Splitter(ifstream& fin, ofstream &fout) {
	my_string str_of_char;
	my_string str_of_int;
	char temp;
	while (fin >> temp) {
		if ((int)temp > 47 && (int)temp < 58)
			str_of_int.push_back((char)temp);
		else
			str_of_char.push_back((char)temp);
		if (fin.peek() == ' ')
			str_of_char.push_back(' ');
	}
	fout << str_of_int << endl;
	fout << str_of_char << endl;
}

int main() {
	string rep;
	do
	{
		system("cls");
		string temp;

		temp = GetWord("Enter file name: ");

		ifstream fin(temp + ".txt", ios_base::in);

		if (fin.is_open()) {

			cout << "|File connected succesfully|\n";

			ofstream fout(temp + "(compleated).txt");
			
			cout << "|Succesfully|\n";

			Splitter(fin, fout);

			fin.close();
			fout.close();
		}
		else
			cout << "|File not found|\n";

		rep = GetYN("Prefer to continue working?[Y / N]: ");
	} while (rep == "y" || rep == "Y");
	return 0;
}