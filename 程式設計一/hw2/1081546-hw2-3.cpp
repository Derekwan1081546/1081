#include<iostream>
using namespace std;
int main()
{
	cout <<"all Armstrong numbers of three digits: "<<endl;
	int num,i,digit,sum;
	for(i=100;i<=999;i++)
	{
		sum=0;

		for(num=i;num>0;num/=10)
		{
			digit=num%10;
			sum=sum+digit*digit*digit;
		}
		if(sum==i)
		{
			cout << i <<endl;
		}
	}

	

	return 0;
}
