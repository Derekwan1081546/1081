//write a program to convert it from decimal numbers to hexadecimal numbers. 
#include<iostream>
using namespace std;
int Factorial_Recursive(int num,int i);
int main()
{
	int num ,i=1;
	cout << "Please input an integer number(0~32767): ";
	cin >> num;
	if(num>32767||num<0)//number should be in range of 0 from 32767
		return 0;
	while (i<=num)
		i*=16;
	i/=16;
	Factorial_Recursive(num,i);//return function
}
int Factorial_Recursive(int num,int i)
{
	if (num/i % 16 < 10)//determine which number is dividended by 16
		cout << num/i % 16 ;
	else if (num/i % 16 == 10)
		cout << "A";
	else if (num/i % 16 == 11)
		cout << "B";
	else if (num/i % 16 == 12)
		cout << "C";
	else if (num/i % 16 == 13)
		cout << "D";
	else if (num/i % 16 == 14)
		cout << "E";
	else
		cout << "F";
	if(i>1)//add condition to ensure that the function is correct
		return Factorial_Recursive(num, i/16 );
}

