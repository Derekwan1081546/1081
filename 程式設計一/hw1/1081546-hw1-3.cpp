// Determine whether a number is a palindrome.
#include <iostream>
using namespace std; 

int main()
{
   int num; // user input number
   

   cout << "Enter a 5-digit number: "; // prompt for a number
   cin >>num;
	int rev=0,val;
   val = num;
   while(num > 0) { 
      rev = rev * 10 + num % 10; 
      num = num / 10; 
   } 
   if(val==rev)
      cout<<val<<" is a palindrome"<<endl;
   else 
      cout<<val<<" is not a palindrome"<<endl;
  

	return 0;
} // end main
