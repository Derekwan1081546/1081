#include<iostream>
#include <iomanip>
#include <cmath>
using namespace std;
double ConvertToFahrenheit(double Celsius);
double ConvertToCelsius(double Fahrenheit);
int main()
{
	int a, b, c;
	cout << "Please choose which conversion you want to use: " << endl << "1.Celsius to Fahrenheit" << endl << "2. Fahrenheit to Celsius" << endl;
	cin >> a;
	cout << "Please input the lower bond and the upper bond of the temperature you want to convert: " << endl;
	cout << "lower bond: "; cin >> b;
	cout << "upper bond: "; cin >> c;
	double d = b;
	if (a == 1)
	{
		cout << setw(10) << "Celsius" << setw(15) << "Fahrenheit" << setw(10) << "Celsius" << setw(15) << "Fahrenheit" << endl;
		cout << fixed << setprecision(1);
		if (b+c%2==1)
		{
		for (int i = 0; i < (c-b)/2+1; i++)
		{
			cout << setw(10) << fixed << setprecision(1)<< d+i << setw(15) << ConvertToFahrenheit(d+i) 
			<< setw(10) << d+i + (c - b ) / 2+1 << setw(15) << ConvertToFahrenheit(b+i+(c - b) / 2+1) << endl;
		}
		}
		
		if(b+c%2==0)
		{
		for (int i = 0; i < (c-b)/2; i++)
		{
			cout << fixed << setprecision(1)<< setw(10) << d+i << setw(15) << ConvertToFahrenheit(b+i) 
			<< setw(10) << d+i + (c - b ) / 2+1 << setw(15) << ConvertToFahrenheit(b+i+(c - b) / 2+1) << endl;
		}
		cout << fixed << setprecision(1)<< setw(10) <<(c-d)/2 << setw(15) << ConvertToFahrenheit((c-b)/2) ;
		}
	}
	if (a == 2)
	{
		cout << "Fahrenheit" << setw(10) << "Celsius" << setw(15) << right << "Fahrenheit" << setw(10) << "Celsius" << endl;
		cout << fixed << setprecision(1);
		for (int i = 0; i < (c - b) / 2 + 1; i++)
		{
			cout << fixed << setprecision(1)<< setw(10) << b+i << setw(10) << ConvertToCelsius(b+i) << setw(15) << b+i + (c - b) / 2+1 << setw(10) 
			<< ConvertToCelsius(b+i + (c - b) / 2+1) << endl;
		}
	}

}
double ConvertToFahrenheit(double Celsius)
{


	return Celsius * 9 / 5 + 32;
}
double ConvertToCelsius(double Fahrenheit)
{


	return (Fahrenheit - 32) * 5 / 9;

}
