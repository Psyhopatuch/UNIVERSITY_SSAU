#include<iostream>
#include<string>
#include<regex>
#include<fstream>
#include<locale>


using namespace std;


// ���� �������
enum struct Seat : unsigned char {
	// ��� ����� (�����)
	None,
	// ������
	Occupied,
	// ������� �����
	Regular,
	// ��� ����� ������
	Vip,
	// �������� ����� ��� ��� �����, �� ����
	// ��� ����� ������, �� �� ����� ������
	// ������ ��� �����
	Sofa,
};

struct Snack {
	// ���������� ����� ���� ����� �����
	// �������� � ���� ��� ��� ���-��?
	// �������� ������� ��� �������� ����� � �����
};

struct Movie {
	// �������� ������
	string Title;
	// ����� ������ � ������� �� ������ �����
	int StartTime;
	// ������������ � �������
	int Duration;
	// ��������� ���� �������
	int PriceCoefficient;
	// �����
	vector<Snack> Snacks;
	// ������� - ������ ����� (��������) �������
public:
	vector<vector<Seat>> Hall;
};

istream& operator>>(istream& instr, Movie &Movie) {
	string temp;
	while (!instr.eof()) {
		int n = 1, nn = 0;
		vector<Seat> v;
		getline(instr, temp);
		for (int j = 0; j < temp.size() - 1; j++) {
			switch (temp[j])
			{
			case('s'):
				for (int g = 1; g < n; g++)
					v.push_back(Seat::Sofa);
				n = 1;
				nn = 0;
				break;
			case('v'):
				for (int g = 1; g < n; g++)
					v.push_back(Seat::Vip);
				n = 1;
				nn = 0;
			case('r'):
				for (int g = 1; g < n; g++)
					v.push_back(Seat::Regular);
				n = 1;
				nn = 0;
				break;
			case('x'):
				for (int g = 1; g < n; g++)
					v.push_back(Seat::Occupied);
				n = 1;
				nn = 0;
				break;
			case('_'):
				for (int g = 1; g < n; g++)
					v.push_back(Seat::None);
				n = 1;
				nn = 0;
				break;
			default:
				try{
				n += temp[j] * pow(10, nn);
				nn++;
				}
				catch(...){
					instr.setstate(instr.failbit);
					cerr << "Input Fail";
				}
				break;
			}
		}
		Movie.Hall.push_back(v);
	}
	return instr;
}

ostream& operator<<(Movie& Movie, ostream& oustr) {
	string temp;
	for (int i = 0; i < Movie.Hall.size();i++) {
		for (int j = 0; j < Movie.Hall[i].size(); j++) {
			switch (Movie.Hall[i][j])
			{
			case(Seat::Regular):
				temp.push_back('r');
				break;
			case(Seat::Vip):
				temp.push_back('v');
				break;
			case(Seat::Occupied):
				temp.push_back('x');
				break;
			case(Seat::Sofa):
				temp.push_back('s');
				break;
			case(Seat::None):
				temp.push_back('_');
				break;
			default:
				cerr << "Output Fail";
				break;
			}
		}
		for (int g = 0; g < temp.size(); g++)
			oustr << temp[g];
		oustr << endl;
	}
	return oustr;
}

int main() {
	Movie nothing;
	cin >> nothing;
}
