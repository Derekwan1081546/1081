#include <iostream> // allows program to perform input and output
using namespace std; // program uses names from the std namespace

int main()
{
   int num; // integer read from user

   cout << "Enter a five-digit integer: "; // prompt
   cin >> num; // read integer from user
   cout<<num/10000<< " " ;
   num=num%10000;
   cout<<num/1000<< " " ;
   num=num%1000;
   cout<<num/100<< " " ;
   num=num%100;
   cout<<num/10<< " " ;
   num=num%10;
   cout<<num<<endl;
   
   system( "pause" ); 
} // end main 
