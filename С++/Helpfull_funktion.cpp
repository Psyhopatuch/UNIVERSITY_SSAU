#include <iostream>
#include <regex> 

using namespace std;
int main()
{
	char cont;
	do
	{
		setlocale(LC_ALL, "RU");

		string user_data; //���������� ��� ��������
		cout << "������� �����\n";
		cin >> user_data; //���� ���������� ��� ��������
		//���������� ���������
		double user_data_1;
		regex regular("([0-9:]{0,})");
		//�������, �������� �� ������������ ����������� ���������
		if (regex_match(user_data.c_str(), regular))//Regex_match ���������, �����. �� ��� ������ ���������, regex_search ��������� ��������� �� ������������ ������� ���������
		{
			cout << "������ ����\n";
			user_data_1 = stod(user_data);// �������������� string � double/stoi/stof/etc.
			cout << user_data_1 << "\n";
		}
		else
		{
			cout << "�������� ����\n";
		}

		cout << "������?[Y/N]\n";
		cin >> cont;
	} while (cont == 'Y');
	return 0;
}

int HHMMSStoSec(string time_in)
{
	string replace;
	int replace_int, time_out;
	time_out = 0;
	for (int i = 0; i <= 7; i++) //������� ������ ��������� �������
	{
		if (time_in[i] != ':') // ������� �������� ���������, ������� ������� � ����������� ����� ��������� ������ � ������ ���
		{
			replace = time_in[i];
			replace_int = stoi(replace); // ������� ���� ������ char � �.�. int
			switch (i)
			{
			case 0:time_out += replace_int * 36000; break; //�������. ������� ����� � �������
			case 1:time_out += replace_int * 3600; break; //�������. ������� ����� � �������
				//Case 2 ��� ���������, ����������� ��������
			case 3:time_out += replace_int * 600; break; //�������. ������� ����� � �������
			case 4:time_out += replace_int * 60; break; //�������. ������� ����� � �������
				//Case 5 ��� ���������, ����������� ��������
			case 6:time_out += replace_int * 10; break; //�������. ������� ������ � �������
			case 7:time_out += replace_int; break; //����������� ���������� ������ ������
			}
		}
	}
	return time_out; //���������� ������� ����������� ��������
}

bool doubleCheck_0(string x) //�������� ��������� �������
{
	regex regular("[-][0-9]{1,9}|[0-9]{1,9}|[-][0-9]{1,9}[.][0-9]{1,9}|[0-9]{1,9}[.][0-9]{1,9}"); //���������� ���������
	if (regex_match(x.c_str(), regular))
		return 1;
	else
		return 0;
}

bool doubleCheck_1(string x) //�������� ��������� �������
{
	regex regular("[-]?[0-9]{1,9}[.]?[0-9]{0,9}"); //���������� ��������� ?-������ ����� ����, � ����� �� ����.
	//regular("[-][0-9]{1,9}|[0-9]{1,9}|[-][0-9]{1,9}[.][0-9]{1,9}|[0-9]{1,9}[.][0-9]{1,9}"); //���������� ���������
	if (regex_match(x.c_str(), regular))
		return 1;
	else
		return 0;
}

bool IntCheck(string x) //�������� ��������� �������
{
	regex regular("[1-9]{1}|[10]{1}"); //���������� ���������
	if (regex_match(x.c_str(), regular))
		return 1;
	else
		return 0;
}

bool IsTime(string x)
{
	regex regular("([0-1][0-9]|[2][0-3])""(:)""([0-5][0-9])""(:)""([0-5][0-9])"); //���������� ���������
	if (regex_match(x.c_str(), regular)) //�������� �� ������������ ����������� ��������� � ���������� ��������
	{
		return true;
	}
	else
	{
		return false;
	}
}



