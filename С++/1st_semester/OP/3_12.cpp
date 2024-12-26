#include <iostream>
#include <time.h>
#include <regex>

using namespace std;
regex reg_repeat("[Yy]|[Nn]");
regex Int("[0-9]{0,9}"); 
int n = rand() % 30;
vector <int> arr{ n };
string error = "|ERROR. Incorrect input|\n";

string GetYN(string what)
{
	string temp;
	cout << what;
	getline(cin, temp);
	while (!regex_match(temp.c_str(), reg_repeat))
	{
		cout << error;
		cout << what;
		getline(cin, temp);
	}
	return temp;
}

string GetInt(string what)
{
	string user_data;
	cout << what;
	getline(cin, user_data);
	while (!regex_match(user_data.c_str(), Int)) 
	{
		cout << error;
		cout << what;
		getline(cin, user_data);
	}
	return user_data;
}

void GetRand(int lenth)
{
	for (int i = 0; i < lenth; ++i)
	{
		int rnd_elem = rand() % 30;
		arr.push_back(rnd_elem);
	}

	cout << "Array_______: ";
	if (lenth <= 25)
	{
		for (int i = 0; i < lenth; ++i)
		{
			cout << arr[i] << " ";
		}
	}
	else
	{
		for (int i = 0; i < 25; ++i)
		{
			cout << arr[i] << " ";
		}
	}
	cout << "\n\n";
}

void SortPrintArr(int lenth)
{
	int i, k, temp, step;

	for (step = lenth / 2; step > 0; step /= 2)
	{
		for (i = step; i < lenth; i++)
		{
			temp = arr[i];
			for (k = i; k >= step; k -= step)
			{
				if (temp < arr[k - step])
					arr[k] = arr[k - step];
				else
					break;
			}
			arr[k] = temp;
		}
	}

	cout << "Sorted array: ";
	if (lenth <= 25)
	{
		for (int i = 0; i < lenth; ++i)
		{
			cout << arr[i] << " ";
		}
	}
	else
	{
		for (int i = 0; i < 25; ++i)
		{
			cout << arr[i] << " ";
		}
	}
	cout << "\n\n";
}

int main()
{
	string repeat;
	do
	{
		srand(time(NULL));

		int lenth = stoi(GetInt("Enter array lenth: "));

		GetRand(lenth);

		SortPrintArr(lenth);

		repeat = GetYN("Prefer to continue working?[Y / N]: ");

		cout << "---------------------------------------------------------------------------------- \n";

		arr.clear();
		n = rand() % 30;
		arr.push_back(n);
	} while (repeat == "Y" || repeat == "y");
}