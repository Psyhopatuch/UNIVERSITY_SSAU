#include<iostream>
#include<fstream>
#include<regex>

using namespace std;

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

void Splitter(ifstream& fin, ofstream& fout) {
	string nums="1234567890";
	string temp;
	
	getline(fin, temp);
	string temp1=temp;
	size_t pos=0;

	while (temp.find_first_of(nums) != string::npos) {
		pos = temp.find_first_of(nums);
		temp=temp.erase(pos, 1);
	}

	while (temp1.find_first_not_of(nums) != string::npos) {
		pos = temp1.find_first_not_of(nums);
		temp1 = temp1.erase(pos, 1);
	}

	fout << temp << endl;
	fout << temp1;
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
}