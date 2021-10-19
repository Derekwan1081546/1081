#include<iostream>
using namespace std;
int main()
{
	cout << "Enter a positive integer of at most 8 digits: ";
	int i;
	int sum=0;
	cin >>i;
	while(i!=0 and i<100000000)
	{	
	sum=sum+(i%10);
	i=i/10;
    }
	cout <<"The sum of all digits of "<< i <<" is "<<sum;	
	return 0;
 } 
