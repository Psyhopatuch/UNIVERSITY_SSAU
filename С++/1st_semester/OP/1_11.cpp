#include <iostream> //����������� ��������� ����-�����
#include<string> //����������� ��������� �����, �������� ��������� iostream, �� �� ������ ������� �++ ������� �����������
#include <regex> //����������� ��������� ���������� ���������

using namespace std; //������ � ������������ ��� ����������� ����������

bool IsTime(string user_data) //�������� ������ �� ���������� ��:��:��
{
	regex regular("([0-1][0-9]|[2][0-3]):([0-5][0-9]):([0-5][0-9])"); //���������� ���������
	if (regex_match(user_data.c_str(), regular)) //�������� �� ������������ ����������� ��������� � ���������� ��������
		return 1; //���������� ������� �������� "������"
	else
		return 0; //���������� ������� �������� "����"
}

int HHMMSStoSec(string time_in) //������� ����������� ��:��:�� � ������� � ������ �����
{
	regex regular("([0-1][0-9]|[2][0-3]):([0-5][0-9]):([0-5][0-9])"); //���������� ���������
	smatch parts; //����������, ���������� �����
	regex_match(time_in, parts, regular); //��������� ��������� ������� �� ������� ������ � regular � ������ �� � smatch parts 

	int Hours = stoi(parts.str(1));
	int Min = stoi(parts.str(2));
	int Sec = stoi(parts.str(3));

	int time_out = Hours * 3600 + Min * 60 + Sec;

	return time_out; //���������� ������� ����������� ��������
}

bool YNCheck(string user_data) //�������� ������� �����������
{
	regex regular("[Y]|[N]");
	if (regex_match(user_data.c_str(), regular))
		return 1; //���������� ������� �������� "������"
	else
		return 0; //���������� ������� �������� "����"
}


int main() 
{
	string user_continue, begining_time, end_time;
	int result;
	do //������� ������� ���������
	{
		do //�������� �� ��������� ���������
		{
			cout << "Enter begining time[HH:MM:SS]: "; //���� ������� ������ ��������
			getline(cin, begining_time); //�������� � ����� �������--std::getline(������,���� ��������)

			while (!IsTime(begining_time)) //���� ���� �� ����� �������� ���������� ������, �������� �� ������������ ����������� ���������
			{
				cout << "Error. Incorrect format, try enter again:\n";
				cout << "Enter begining time[HH:MM:SS]: ";
				getline(cin, begining_time); //�������� ������ �������--std::getline(������,���� ��������)
			}

			cout << "Enter end time[HH:MM:SS]: "; //���� ������� ����� ��������
			getline(cin, end_time); //�������� ������ �������--std::getline(������,���� ��������)

			while (!IsTime(end_time)) //���� ���� �� ����� �������� ���������� ������, �������� �� ������������ ����������� ���������
			{
				cout << "Error. Incorrect format, try enter again:\n";
				cout << "Enter end time[HH:MM:SS]: ";
				getline(cin, end_time); //�������� ������ �������--std::getline(������,���� ��������)
			}

			result = HHMMSStoSec(end_time) - HHMMSStoSec(begining_time); //���������� ����� ������� HHMMSStoSec
			if (result > 0)
			{
				cout << result << "(seconds) or "; //����� ���������� � ��������
				cout << result / 60 << "(minutes)\n"; //����� ���������� � ������� (��������������)
			}
			else cout << "End time cannot be early than begining time, try again ^_^\n";
		} 
		while (result <= 0); //�������� �� ��������� ���������

		cout << "Prefer to continue working?[Y/N]:"; //������ ������� ���������
		getline(cin, user_continue); //�������� ������ �������--std::getline(������,���� ��������)
		while (!YNCheck(user_continue)) //���� ���� �� ����� �������� ���������� ������, �������� �� ������������ ����������� ���������
		{
			cout << "Error. Incorrect format, try enter again:\n";
			cout << "Prefer to continue working?[Y/N]:";
			getline(cin, user_continue); //�������� ������ �������--std::getline(������,���� ��������)
		}
	} while (user_continue == "Y"); //������� ������� ���������
return 0;
}