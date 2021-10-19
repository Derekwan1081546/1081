#include<iostream>
#include<cstdlib>
#include<ctime>
#include <iomanip>
using namespace std;

int main()
{
	double table[7][7]={0};	//set the times of each possible sum
	int dice1, dice2;	//set two dices
	double sum=0;	//set The probability of each possible sum 


	srand(time(NULL));
	for (int i = 0; i <= 36000; i++)	//roll two dices 36000 times
	{
		dice1 = rand() % 6 + 1;		//dice are in the range of 1~6
		dice2 = rand() % 6 + 1;		
		table[dice1][dice2]++;
	}
	cout << setw(10) << "1" <<setw(10) <<"2" <<setw(10) <<"3"<<setw(10)<<"4"<<setw(10)<<"5"<<setw(10)<<"6"<<endl;

	for (int i = 1; i <= 6; i++)
	{
		cout << i;
		for (int j = 1; j <= 6; j++)
		{
			cout << setw(10) << table[i][j] ;			
		}
		cout << endl;
	}

	for (int i = 2; i <= 7; i++)	//Print the probability of each possible sum which vary from 2 to 7.
	{
		
		cout << "p(" << i << ") =";

		for (int j=1;j<i;j++)
			if (j<i-1)
				cout << fixed << setprecision(6) << " p(" << j << "+" <<i-j <<")"<<"+";
			else
				cout <<  " p(" << j << "+" <<i-j <<")" << " = " << fixed << setprecision(6) ;
		for (int j=1;j<i;j++)
		{
			if (i==2)
				cout <<table[j][i-j]/36000 ;	
			else if (j<i-1)
			cout <<table[j][i-j]/36000 << "+";
			else
			cout <<table[j][i-j]/36000 << "=";
			sum+=table[j][i-j]/36000;
		}
		if (i!=2)
		cout <<sum;	
		cout <<endl;
		sum=0;
	}
	for (int i = 8; i <= 12; i++)	// Print the probability of each possible sum which vary from 8 to 12.
	{
		cout << "p(" << i << ") =";

		for (int k=6;k>=i-6;k--)
			if (k>=i-5)
				cout << fixed << setprecision(6) << " p(" << k << "+" <<i-k <<")"<<"+";
			else
				cout << " p(" << k << "+" <<i-k <<")" << " = " << fixed << setprecision(6) ;

		
		for (int k=6;k>=i-6;k--)
		{
			if (i==12)
				cout <<table[k][i-k]/36000 ;	
			else if (k>=i-5)
			cout <<table[k][i-k]/36000 << "+";
			else
			cout <<table[k][i-k]/36000 << "=";
			sum+=table[k][i-k]/36000;
		}
		if (i!=12)
			cout <<sum;
		cout <<endl;
		sum=0;
	}
	return 0;
}
