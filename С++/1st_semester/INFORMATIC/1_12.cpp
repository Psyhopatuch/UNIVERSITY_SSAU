#include <iostream>
#include <string>
#include <regex>

using namespace std;

string error_text = "|ERROR.Incorect input|\n";

bool YNCheck(string user_data) //�������� ������� �����������
{
	regex regular("[Y]|[N]");
	if (regex_match(user_data.c_str(), regular))
		return 1; //���������� ������� �������� "������"
	else
		return 0; //���������� ������� �������� "����"
}

bool IntCheck(string x) //�������� ��������� �������
{
	regex regular("[1-9]|[1-9][0-9]{1,8}"); //���������� ���������
	if (regex_match(x.c_str(), regular))
		return 1;
	else
		return 0;
}

string CalcEvcExtRe(int n, int mod)
{

	//an+bk=1
	int cur_rem = n % mod, cur_quotient = n / mod, k = mod;

	int* a = new int[3];//{a_last}{a_curr}{a_next}
	if (n % mod == 0 || mod % n == 0)
		return "Result not found";
	else
		if (cur_rem == 1)
			return to_string(cur_rem);
		else {
			a[0] = 1;
			a[1] = 0;

			while (cur_rem > 1) {
				cur_quotient = n / mod;
				cur_rem = n % mod;
				n = mod;
				mod = cur_rem;
				a[2] = a[0] - cur_quotient * a[1];
				a[0] = a[1];
				a[1] = a[2];
			}

			if (a[1] > 0)
				return to_string(a[1]);
			else
				return to_string(k + a[1]);
		}
}

int main()
{
	string user_continue;
	do //������� ������� ���������
	{

		string temp;

		cout << "Enter int: ";
		getline(cin, temp);
		while (!IntCheck(temp))
		{
			cout << error_text;
			cout << "Enter int: ";
			getline(cin, temp);
		}
		int n = stoi(temp);

		cout << "Enter mod: ";
		getline(cin, temp);
		while (!IntCheck(temp))
		{
			cout << error_text;
			cout << "Enter module: ";
			getline(cin, temp);
		}
		int mod = stoi(temp);


		cout << "Result: " << CalcEvcExtRe(n, mod) << "\n";

		cout << "Prefer to continue working?[Y/N]"; //������ ������� ���������
		getline(cin, user_continue); //�������� ������ �������--std::getline(������,���� ��������)
		while (!YNCheck(user_continue)) //���� ���� �� ����� �������� ���������� ������, �������� �� ������������ ����������� ���������
		{
			cout << error_text;
			cout << "Prefer to continue working?[Y/N]";
			getline(cin, user_continue); //�������� ������ �������--std::getline(������,���� ��������)
		}

	} while (user_continue == "Y");
}