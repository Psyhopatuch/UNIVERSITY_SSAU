#include <iostream> //����������� ��������� ����-�����
#include<string> //����������� ��������� �����, �������� ��������� iostream, �� �� ������ ������� �++ ������� �����������
#include <regex> //����������� ��������� ���������� ���������

using namespace std; //����� �� ����������� ������ ��� std:: ����� �������� � ���� ������������ ���

int getInt(string TextOutput, string TextError) // �������, ������������ �� ���� ����� ������/������ ����� ������
{
	regex regular("[0-9]{0,9}"); //���������� ���������
	string user_data;
	getline(cin, user_data);
	while (!regex_match(user_data.c_str(), regular)) //���� ���� �� ����� �������� ���������� ������, �������� �� ������������ ����������� ���������
	{
		cout << TextError<<endl;
		cout << TextOutput;
		getline(cin, user_data);
	}
	return stoi(user_data); //���������� ������� �������� ���������� � ���� int
}

double getDoubleEl(string TextOutput, string TextError,int i,int j) // �������, ������������ �� ���� ����� ������/������ ����� ������/������� ������ �������
{
	regex regular("[-][0-9]{0,9}|[0-9]{0,9}|[-][0-9]{0,9}[.][0-9]{0,9}|[0-9]{0,9}[.][0-9]{0,9}"); //���������� ���������
	string user_data;
	getline(cin,user_data);
	while (!regex_match(user_data.c_str(), regular)) //���� ���� �� ����� �������� ���������� ������, �������� �� ������������ ����������� ���������
	{
		cout << TextError<<endl;
		cout << TextOutput<<"["<<i<<"]["<<j<<"]: ";
		getline(cin, user_data);
	}
return stod(user_data); //���������� ������� �������� ���������� � ���� double
}

int main()
{
	char user_continue;
	do //������ ��������� 
	{ 
		cout << "Enter matrix length(max=10): ";
		int length = getInt("Enter matrix length: ", "Error, incorrect input");

		cout << "Enter matrix width: ";
		int width = getInt("Enter matrix width(max=10): ", "Error, incorrect input");

		//�������� �� ������������ ������ � ������
		if (length > 10)
		{
			length = 10;
		}

		if (width > 10)
		{
			width = 10;
		}

		double matrix[10][10]; //���������� �������
		for (int i = 0; i < length;i++)
		{
			for (int j = 0; j < length; j++)
			{
				cout << "Enter element[" << i << "][" << j << "]: ";
				matrix[i][j] = getDoubleEl("Enter element", "Error, incorrect input ", i, j);
			}
		}

		double min = matrix[0][0], max = matrix[0][0];//���������� � ������������� ���������� ����������� �������� �������� � ���������

		for (int i = 0; i < length; i++)
		{
			for (int j = 0; j < length; j++)
			{
				if (matrix[i][j]>max) //���� ������� ������� ������ ��� ���������� ���������, �� ����������� � �������� �������� ��������
				{
					max = matrix[i][j];
				}

				if (matrix[i][j]<min) //����������
				{
					min = matrix[i][j];
				}
			}


		}

		cout << "Min: " << min;
		cout << "\nMax: " << max;

		cout << "\nPrefer to continue working?[Y/N]"; //������ ������� ���������
		cin >> user_continue;
	} while (user_continue == 'Y'); //������� ������� ���������
	return 0;
}