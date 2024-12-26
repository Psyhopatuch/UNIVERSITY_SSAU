#include<iostream>
#include<string>
#include<regex>
#include<fstream>

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
	while (!regex_match(temp.c_str(), reg_YN)) {
		cout << error;
		cout << what;
		getline(cin, temp);
	}
	cout << endl;
	return temp;
}

void FileReader(ifstream &fin, vector<string>& data) {
	string temp;
	if (fin.is_open()) {
		while (!fin.eof()) {
			getline(fin, temp);
			data.push_back(" "+temp+" ");
		}
	}
}

string ToLowReg(string old_word) {
	string word = old_word;
	for (int n = 0; n < old_word.size(); n++) {
		if ((int)old_word[n] >= 65 && (int)old_word[n] <= 90)
			word[n] = (char)tolower(old_word[n]);
	}
	return word;
}

void VecDeleteElement(vector<int>& vec, int n, int old_len, int new_len, bool first) {
	vector<int> temp_vec;
	int g = -90;
	int f = 0;

	for (int b = 0; b < vec.size(); b++)
	{

		if (vec[b] != n) {
			temp_vec.push_back(vec[b]);
			f += 1;
		}
		else
			g = f;
		if (vec[b] > n && g== -90) {
			g = b;
		}
	}

	//cout << g << endl;


	if (first&&g!=-90) {
		for (int b = g; b < temp_vec.size(); b++)
		{
			temp_vec[b] = temp_vec[b] - old_len + new_len;
		}
		//cout << 2452245 << endl;
	}

	vector<int>().swap(vec);


	temp_vec.swap(vec);


	vector<int>().swap(temp_vec);//Vector delete
}

void CheckRegist(string line, vector<int> &up_regist) {
	for (int b = 0; b < line.size(); b++)
	{
		if ((int)line[b] >= 65 && (int)line[b] <= 90) {
			up_regist.push_back(b);
		}
	}
}

void UnderReplacer(int i, vector<string>& data, string old_word, string new_word) {
	size_t old_len = old_word.size() + 2;
	size_t new_len = new_word.size() + 2;
	string pref_post = "\'\"_-() ?.,!;:";
	vector<int> up_regist;
	
	CheckRegist(data[i], up_regist);
	
	//To lower regist:
	data[i] = ToLowReg(data[i]);
	//for (int n = 0; n < data[i].size(); n++) {
	//	string temp = to_string(data[i][n]);
	//	if ((int)data[i][n] >= 65 && (int)data[i][n] <= 90) {
	//		data[i][n] = tolower(data[i][n]);
	//	}
	//}

	//for (int g = 0; g < up_regist.size(); g++) {
	//	cout << up_regist[g] << " ";
	//}
	//cout << endl;

	bool first = true;

	//cout << data[i];
	//cout << endl;

	for (int g = 0; g < 7; g++) {

		for (int j = 0; j < pref_post.size(); j++) {
			
			while ((data[i].find(pref_post[g] + old_word + pref_post[j]) != std::string::npos)) {
				first = true;
				size_t pos = data[i].find(pref_post[g] + old_word + pref_post[j]);
				data[i].replace(pos, old_len, pref_post[g] + new_word + pref_post[j]);
				
				for (int r = pos + 1; r < pos + old_len-1; r++) {
					VecDeleteElement(up_regist, r, old_len, new_len, first);
					first = false;
				}
				
			}
		}
	}

	//for (int g = 0; g < up_regist.size(); g++) {
	//	cout << up_regist[g] << " ";
	//}
	//cout << endl;

	//Return regist:
	for (int n = 0; n < up_regist.size(); n++) {
		data[i][up_regist[n]] = toupper(data[i][up_regist[n]]);
	}
}

void Replacer(vector<string> &data, string old_word, string new_word) {
	for (int i = 0; i < data.size(); i++) {
		if(i%2)
			cout << "Progress:" << i*100 / data.size()<<"%\r";
		UnderReplacer(i, data, old_word, new_word);
	}
}

void VecPrinter(vector<string>& data) {
	for (int i = 0; i <= data.size() - 1; i++) {
		cout << data[i].erase(0, 1).erase(data[i].size() - 2, 1) << endl;
	}
}


void VecPrinter(ofstream& fout, vector<string>& data) {
	for (int i = 0; i <= data.size() - 1; i++) {
		fout << data[i].erase(0, 1).erase(data[i].size()-2, 1) << endl;
	}
}

int main() {
	string rep;
	do
	{ 
		system("cls");
		string temp;

		cout << "Files:\nJane_Eyre\n" << "The_Adventures_of_Sherlock_Holmes\n";

		temp = GetWord("Enter file name: ");

		ifstream fin(temp + ".txt", ios_base::in);

		if (fin.is_open()) {
			cout << "|File connected succesfully|\n";

			ofstream fout(temp + "(compleated).txt");

			vector<string> data;

			FileReader(fin, data);

			string old_word = ToLowReg(GetWord("Enter replase word: "));
			string new_word = GetWord("Enter word to replase: ");

			temp = ToLowReg(new_word);
			

			while (old_word == temp)
			{
				cout << "I'm so sorry, there is no reathon in that, maybe we know more words?\n";
				new_word = GetWord("Enter word to replase: ");
				temp = ToLowReg(new_word);
			}


			Replacer(data, old_word, new_word);

			VecPrinter(fout, data);

			cout << "|Succesfully|\n";

			fin.close();
			fout.close();
		}
		else
			cout << "|File not found|\n";

		rep = GetYN("Prefer to continue working?[Y / N]: ");
	} while (rep == "y" || rep == "Y");
}