#include <iostream>
using namespace std;

int main()
{
   int n;
   cout << "Enter a year ( 1583-3000 ): ";
   while(cin>>n)
   {if(n%400==0 or(n%4==0 and n%100!=0))
	cout << "Year " << n << " is a leap year.";
   else
   	cout << "Year " << n << " is a common year.";
   }



   system( "pause" );
}
