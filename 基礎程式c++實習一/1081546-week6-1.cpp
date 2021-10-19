//write a program to convert it from decimal numbers to hexadecimal numbers.
#include<iostream>
using namespace std;
int main()
{
	int num,i=1,num2;
	cout << "Please input an integer number(0~32767): ";
	cin >> num;
	num2=num;
	if (num<0||num>32767)//number should be in range of 0 from 32767
	return 0;
	while (num>=16)//if number is larger than 16,then do the following steps 
	{
		i*=16;
		num/=16;
	}
	while (num2>0)//determine whether number is dividended by 16
	{
		if (num2/i % 16 < 10)
		cout << num2/i % 16 ;
		else if (num2/i % 16 == 10)
		cout << "A";
		else if (num2/i % 16 == 11)
		cout << "B";
		else if (num2/i % 16 == 12)
		cout << "C";
		else if (num2/i % 16 == 13)
		cout << "D";
		else if (num2/i % 16 == 14)
		cout << "E";
		else
		cout << "F";
		i/=16;
	}
	return 0;
 } 
