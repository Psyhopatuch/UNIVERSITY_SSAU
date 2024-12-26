#include <iostream> // ����������� ��������� ����-�����
#include <string> // ����������� ��������� �����, �������� ��������� iostream, �� �� ������ ������� �++ ������� �����������
#include <regex> // ����������� ��������� ���������� ���������


using namespace std; //������ � ������������ ��� ����������� ���������� 

string error_text = "|ERROR.INCORRECT INPUT|\n";
regex r_size("[2-9][0-9]{0,3}"); // ���������� ���������
regex r_elem("[-]?[0-9]{1,5}[.]?[0-9]{0,3}"); // ���������� ���������
regex r_cont("[Y]|[N]"); // ���������� ���������

bool IntCheck(string x) // �������� ��������� �������
{
	if (regex_match(x.c_str(), r_size))
		return 1; // ���������� ������� �������� "������"
	else
		return 0; // ���������� ������� �������� "����"
}

bool DoubleCheck(string x) // �������� �������� �������
{
	if (regex_match(x.c_str(), r_elem))
		return 1; // ���������� ������� �������� "������"
	else
		return 0; // ���������� ������� �������� "����"
}

bool YNCheck(string user_data) // �������� ������� �����������
{
	if (regex_match(user_data.c_str(), r_cont))
		return 1; // ���������� ������� �������� "������"
	else
		return 0; // ���������� ������� �������� "����"
}


int main()
{
	
	string user_continue, temp; // ���������� ����������
	do // ������ ��������� 
	{
		cout << "Enter matrix length(max=9*10^3): "; // ���� ������ �������
		getline(cin, temp); // �������� � ����� �������--std::getline(������,���� ��������)
		while (!IntCheck(temp)) // ���� ������� �������� �� "true"
		{
			cout << error_text; // ����� ������ ������
			cout << "Enter matrix length(max=9*10^3): ";
			getline(cin, temp); // �������� � ����� �������--std::getline(������,���� ��������)
		}
		int len = stoi(temp);

		cout << "Enter matrix width(max=9*10^3): ";
		getline(cin, temp); // �������� � ����� �������--std::getline(������,���� ��������)
		while (!IntCheck(temp)) // ���� ������� �������� �� "true"
		{
			cout << error_text; // ����� ������ ������
			cout << "Enter matrix length(max=9*10^3): ";
			getline(cin, temp); // �������� � ����� �������--std::getline(������,���� ��������)
		}
		int wid = stoi(temp);

		// ���������� �������
		double** matrix = new double* [len];
		for (int i = 0; i < len; i++) 
		{       
			matrix[i] = new double[wid]; 
		}

		for (int i = 0; i < len; i++) //���� ������� ��������� � ���������
		{
			for (int j = 0; j < wid; j++)
			{
				cout << "Enter element[" << i+1 << "][" << j+1 << "]: ";

				getline(cin, temp); // �������� � ����� �������--std::getline(������,���� ��������)

				while (!DoubleCheck(temp)) // ���� ������� �������� �� "true"
				{
					cout << error_text; // ����� ������ ������
					cout << "Enter element[" << i+1 << "][" << j+1 << "]: ";
					getline(cin, temp); // �������� � ����� �������--std::getline(������,���� ��������)
				}
				matrix[i][j] = stod(temp); //String to double
			}
		}

		for (int i = 0; i < len; i++)
		{
			for (int j = 0; j < wid; j++)
			{
				cout << matrix[i][j] << " ";
			}
			cout << endl;
		}

		double min = matrix[0][0], max = matrix[0][0];//���������� � ������������� ���������� ����������� �������� �������� � ���������

		for (int i = 0; i < len; i++)
		{
			for (int j = 0; j < wid; j++)
			{
				if (matrix[i][j] > max) // ���� ������� ������� ������ ��� ���������� ���������, �� ����������� �� �������� �������� ��������
				{
					max = matrix[i][j];
				}

				if (matrix[i][j] < min) // ����������
				{
					min = matrix[i][j];
				}
			}
		}

		for (int i = 0; i < len; i++) 
		{
			delete[] matrix[i];  // ������� ������
		}

		cout << "Min: " << min;
		cout << "\nMax: " << max;

		cout << "\nPrefer to continue working?[Y/N]"; // ������ ������� ���������
		getline(cin, user_continue); // �������� ������ �������--std::getline(������,���� ��������)
		while (!YNCheck(user_continue)) // ���� ������� �������� �� "true"
		{
			cout << error_text; // ����� ������ ������
			cout << "Prefer to continue working?[Y/N]:";
			getline(cin, user_continue); // �������� ������ �������--std::getline(������,���� ��������)
		}

	} while (user_continue == "Y"); // ������� ������� ���������
	return 0;
}