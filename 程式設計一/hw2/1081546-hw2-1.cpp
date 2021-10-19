#include<iostream>
using namespace std;
int main()
{
	int n1,n2,array[100],octal[100],i=0,j,k,a;
	cout <<"Enter a positive decimal integer of at most 8 digits: ";
	cin >>n1;
	n2=n1;
	a=n1;
	while(n1!=0)
	{
		array[i]=n1%2;
		i++;
		n1=n1/2;		
	}
	cout <<"The binary equivalent of "<< a <<" is: "<<endl;
	for(j=i-1;j>=0;j--)
	{
		cout <<array[j];
	}
	i=0;
	while(n2!=0)
	{
		octal[i]=n2%8;	
		n2=n2/8;
		i++;		
	}
	cout <<endl<<"The octal equivalent of "<< a <<" is: "<<endl;
	for(k=i-1;k>=0;k--)
	{
		cout <<octal[k];
	}
	return 0;
 } 
