#include<iostream>
using namespace std;
int f(int n)
{
	if (n < 10)
		return n;
	else
		return f(n / 10) + n % 10;

}
int main()
{
	int n;
	cin >> n;
	while (n != 0)
	{
		while (n > 9)
		{
			n = f(n);
		}
		cout << n << endl;
		cin >> n;
	}
}
