#include <iostream> //Подключение директивы ввод-вывод
#include<string> //Подключение директивы строк, является элементом iostream, но на старых версиях С++ требует подключения

using namespace std;

int main()
{
	int n, k, factorial_n = 1, factorial_k = 1, factorial_nminusk = 1;

	cout <<"n:";
	cin >> n;

	cout << "k:";
	cin >> k;

	for (int i = 1; i <= n; i++)
	{
		factorial_n = factorial_n * i;
	}

	for (int i = 1; i <= k; i++)
	{
		factorial_k = factorial_k * i;
	}

	for (int i = 1; i <= n-k; i++)
	{
		factorial_nminusk = factorial_nminusk * i;
	}

	int result = factorial_n / (factorial_k * factorial_nminusk);

	cout << "result: " << result;
}