#include<iostream>
using namespace std;
int oddsum(int a, int b)
{
	if (a==b&&a%2==0)
	return 0;
	if (a % 2 == 0)
		a += 1;
	if (b % 2 == 0)
		b -= 1;
	if (a == b)
		return b;
	return a + oddsum(a + 2, b);

}
int main()
{
	int a, b, n;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> a >> b;
		cout <<"Case " << i <<": "<<oddsum(a, b) <<endl;
	}
	return 0;

}
