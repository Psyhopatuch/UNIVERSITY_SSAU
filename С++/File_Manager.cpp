#include<iostream>
#include<string>
#include<regex>
#include<fstream>
#include<locale>


using namespace std;


// Типы сидений
enum struct Seat : unsigned char {
	// нет места (дырка)
	None,
	// занято
	Occupied,
	// обычное место
	Regular,
	// вип место дороже
	Vip,
	// диванчик стоит как вип место, но если
	// они стоят подряд, то их можно купить
	// только все разом
	Sofa,
};

struct Snack {
	// придумайте какие поля имеют снэки
	// название и цена или ещё что-то?
	// написать максиму для хранения этого в файле
};

struct Movie {
	// название фильма
	string Title;
	// время начала в минутах от начала суток
	int StartTime;
	// длительность в минутах
	int Duration;
	// множитель цены сидений
	int PriceCoefficient;
	// снэки
	vector<Snack> Snacks;
	// кинозал - вектор рядов (векторов) сидений
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
