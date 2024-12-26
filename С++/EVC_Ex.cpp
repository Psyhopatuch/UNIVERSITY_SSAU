#include <iostream>
#include <string>

using namespace std;

//Общий вид
//void CalcEvcExt(int n, int k, int rem, int* gcd, int* a, int* b)
//Вывод--Таблица [индекс|частное|остаток|коэф при a|коэф при b]
/*https://ru.wikipedia.org/wiki/Расширенный_алгоритм_Евклида*/

void CalcEvcExt(int n, int k)
{
	//an+bk=1
	int cur_rem = n % k, cur_quotient = n / k; 

	int* a = new int[3];//{a_last}{a_curr}{a_next}
	int* b = new int[3];

	a[0] = 1;	b[0] = 0;
	a[1] = 0;	b[1] = 1;
	cout << 0 << ") " << "|-| " << n << " " << a[0] << " " << b[0] << endl;
	cout << 1 << ") " << "|-| " << k << " " << a[1] << " " << b[1] << endl;
	int iter_count = 2;

	while (cur_rem > 0)
	{
		
		cur_quotient = n / k;
		cur_rem = n % k;

		n = k;
		k = cur_rem;

		a[2] = a[0] - cur_quotient * a[1];
		b[2] = b[0] - cur_quotient * b[1];

		a[0] = a[1];	b[0] = b[1];
		a[1] = a[2];	b[1] = b[2];
		cout << iter_count << ") " << cur_quotient << " " << cur_rem << " " << a[1] << " " << b[1] << " " << endl;

		iter_count += 1;
	}
	delete[] a;
	delete[] b;
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
		else{
			a[0] = 1;	
			a[1] = 0;	

			while (cur_rem > 1){
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
					return to_string(k+a[1]);
		}
}

int main(){
	cout<< CalcEvcExtRe(23, 145);
	return 0;
}