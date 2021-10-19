#include<iostream>
#include <iomanip>
using namespace std;
int main()
{
	float n1, n2, n3, n4,s,TDEE,activity; //input gender age mass height activity list
	cout << "Input Gender(Male:1/Female:2): ";
	cin >> n1;
	cout << "Input Age(year): ";
	cin >> n2;	
	cout << "Input mass(kg): ";
	cin >> n3;
	cout << "Input height(cm): ";
	cin >> n4;
	cout << "Activity List" << endl << "1. Sedentary(office job)" << "2. Light Exercise(1 - 2 days / week)" << endl << "3. Moderate Exercise(3 - 5 days / week)" << endl << "4. Heavy Exercise(6 - 7 days / week)" << endl << "5. Athlete(2x per day)" << endl <<"Input activity: "<<endl;
	cin >> activity;
	if (n1 == 1)
	{
		cout << "Gender: Male" <<endl;
	}
	else {
		cout << "Gender: Female" <<endl;
	}
	cout <<"Age(year): "<<n2<<endl;
	cout <<"Mass(kg): "<<n3<<endl;
	cout <<"Height(cm): "<<n4<<endl; 
	if (n1 == 1)
	{
		s = 5;
	}
	else	
	{	s = -161;
	}
	float BMI = n3 / ((n4 / 100) * (n4 / 100)); //calculating BMI and output BMI
	cout << "BMI: " <<setprecision(3)<<fixed<< BMI <<endl;
	if (BMI <= 18.5) //check which types you belong to
	{
		cout << "You are Underweight" <<endl;
	}
	else if (18.5<BMI<=24)
	{
		cout << "You are Normal " <<endl;
	}
	else if (24<BMI<=27)
	{
		cout << "You are Overweight" <<endl;
	}
	else if (27<BMI<=30)
	{
		cout << "You are Moderately obese" <<endl;
	}
	else if (30<BMI<=35)
	{
		cout << "You are Severely obese" <<endl;
	}
	else
	{
		cout << "You are Very severely obese" <<endl;
	}
	float BMR = 10 * n3 + 6.25 * n4 - 5 * n2 + s; //calculating BMR and output
	cout << "BMR: "<< BMR <<endl;
	if (activity=1)//check which types you belong to and your TDEE
	{
		cout << "You are Sedentary" <<endl;
		cout << "TDEE: "<< BMR*1.2;
	}
	else if (activity=2)
	{
		cout << "You are Light Exercise" <<endl;
		cout << "TDEE: "<<BMR*1.375;
	}
	else if (activity=3)
	{
		cout << "You are Moderate Exercise" <<endl;
		cout << "TDEE: "<<BMR*1.55;
	}
	else if (activity=4)
	{
		cout << "You are Heavy Exercise" <<endl;
		cout << "TDEE: "<<BMR*1.725;
	}
	else
	{
		cout << "You are Athlete" <<endl;
		cout <<"TDEE: "<<BMR*1.9;
	}
	return 0;
}
