#include <iostream>
#include <string>
#include <regex>

using namespace std;

string error_text = "|ERROR.INCORRECT INPUT|\n";
regex regular_rad("[1-9][0-9]{0,8}|[0-9]{1,9}[.][0-9]{0,8}[1-9]");
regex regular_coord("([-]?[0-9]{1,4}[.]?[0-9]{0,3});([-]?[0-9]{1,4}[.]?[0-9]{0,3})");
regex regular_repeat("[Y]|[N]");
smatch parts;

struct cord
{
public:

	double x;
	double y;
	string str_xy;

};


double Ruler(double x1,double x2)
{
	return abs(x1 - x2);
}

double Algebroic(double x, double y, double rad)
{
	return pow(pow(x, 2) + pow(y, 2), 0.5) - rad;
}

bool YNCheck(string user_data)
{
	if (regex_match(user_data.c_str(), regular_repeat))
		return 1; //���������� ������� �������� "������"
	else
		return 0; //���������� ������� �������� "����"
}

bool CoordinatesCheck(string x) 
{
	//regular("[-][0-9]{1,9}|[0-9]{1,9}|[-][0-9]{1,9}[.][0-9]{1,9}|[0-9]{1,9}[.][0-9]{1,9}"); //���������� ���������
	if (regex_match(x.c_str(), regular_coord))
		return 1;
	else
		return 0;
}

bool RadCheck(string user_data) 
{
	if (regex_match(user_data.c_str(), regular_rad))
		return 1;
	else
		return 0;
}

void Spliter(string *xy_str, double *x, double *y)
{
	regex_match(*xy_str, parts, regular_coord);
	 *x = stod(parts.str(1));
	 *y = stod(parts.str(2));
}

int main()
{
	string user_continue;
	do //������� ������� ���������
	{
		cord centre;
		cout << "Enter center coordinates (x;y): ";
		getline(cin, centre.str_xy);
		while (!CoordinatesCheck(centre.str_xy)) //���� ���� �� ����� �������� ���������� ������, �������� �� ������������ ����������� ���������
		{
			cout << error_text;
			cout << "Enter center coordinates (x;y): ";
			getline(cin, centre.str_xy); //�������� ������ �������--std::getline(������,���� ��������)
		}

		cord point;
		cout << "Enter point coordinates (x;y): ";
		getline(cin, point.str_xy);
		while (!CoordinatesCheck(point.str_xy)) //���� ���� �� ����� �������� ���������� ������, �������� �� ������������ ����������� ���������
		{
			cout << error_text;
			cout << "Enter center coordinates (x;y): ";
			getline(cin, point.str_xy); //�������� ������ �������--std::getline(������,���� ��������)
		}

		Spliter(&centre.str_xy, &centre.x, &centre.y);
		Spliter(&point.str_xy, &point.x, &point.y);

		cout << "Enter radius: ";
		string rad_str;
		getline(cin, rad_str);
		while (!RadCheck(rad_str)) //���� ���� �� ����� �������� ���������� ������, �������� �� ������������ ����������� ���������
		{
			cout << error_text;
			cout << "Enter radius: ";
			getline(cin, rad_str); //�������� ������ �������--std::getline(������,���� ��������)
		}

		double rad = stod(rad_str);
		cout << abs(Algebroic(Ruler(centre.x, point.x), Ruler(centre.y, point.y), rad));


		cout << "\nPrefer to continue working?[Y/N]:"; //������ ������� ���������
		getline(cin, user_continue); //�������� ������ �������--std::getline(������,���� ��������)
		while (!YNCheck(user_continue)) //���� ���� �� ����� �������� ���������� ������, �������� �� ������������ ����������� ���������
		{
			cout << error_text;
			cout << "Prefer to continue working?[Y/N]:";
			getline(cin, user_continue); //�������� ������ �������--std::getline(������,���� ��������)
		}

	} while (user_continue == "Y");
}