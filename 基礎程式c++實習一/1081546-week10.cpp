//uva10035
#include <iostream>
using namespace std;

int main() {
	long int a, b, c, d, e, result, carry;

	while (cin >> a >> b) {
		if (a == 0 && b == 0) break;	//判斷a和b是否為零,如果是則跳出

		carry = 0, c = 0;	//先歸零

		while (a != 0 || b != 0)	//判斷a或b其中之一是否不為零,如果成立則繼續執行
		{
			d = a % 10;	//算a的個數
			a = a / 10;	
			e = b % 10;	//算b的個數
			b = b / 10;

			result = d + e + c;
			if (result >= 10)	//判斷單位數相加是否大於等於10
			{
				c = 1;	//進位
				carry ++;	
			}
			else
			{
				c = 0;
			}
		}
		//輸出
		if (carry == 0) 
		{
			cout << "No carry operation." << endl;
		}
		else if (carry == 1)
		{
			cout << carry << " carry operation." << endl;
		}
		else if (carry > 1)
		{
			cout << carry << " carry operations." << endl;
		}
	}

	return 0;
}
