// Huge integer addition, subtraction, multiplication and division
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <fstream>
using std::istream;
using std::ostream;
using std::ifstream;
using std::ofstream;
using std::ios;

// enable user to input a positive huge integer
void input( istream &inFile, int hugeInt[], int &size );

// perform addition, subtraction, multiplication and division
void perform( ostream &outFile, int hugeInt1[], int hugeInt2[], int hugeInt3[],
              int hugeInt4[], int size1, int size2, int size3, int size4 );

// output the specified huge integer
void output( ostream &outFile, int hugeInt[], int size );

// returns true if and only if the specified huge integer is zero
bool isZero( int hugeInt[], int size );

// return true if and only if hugeInt1 == hugeInt2
bool equal( int hugeInt1[], int hugeInt2[], int size1, int size2 );

// returns true if and only if hugeInt1 < hugeInt2
bool less( int hugeInt1[], int hugeInt2[], int size1, int size2 );

// sum = addend + adder
void addition( int addend[], int adder[], int sum[], int addendSize, int adderSize, int &sumSize );

// difference = minuend - subtrahend
void subtraction( int minuend[], int subtrahend[], int difference[],
                  int minuendSize, int subtrahendSize, int &differenceSize );

// product = multiplicand * multiplier
void multiplication( int multiplicand[], int multiplier[], int product[],
                     int multiplicandSize, int multiplierSize, int &productSize );

// quotient = dividend / divisor; remainder = dividend % divisor
void division( int dividend[], int divisor[], int quotient[], int remainder[],
               int dividendSize, int divisorSize, int &quotientSize, int &remainderSize );

// hugeInt /= 10
void divideBy10( int hugeInt[], int &size );

const int numTestCases = 22; // the number of test cases
const int arraySize = 200;

int main()
{
   system( "mode con cols=122" );

   ifstream inFile( "Test cases.txt", ios::in );

   // exit program if ifstream could not open file
   if( !inFile )
   {
      cout << "File could not be opened" << endl;
      system( "pause" );
      exit( 1 );
   }

   ofstream outFile( "Result.txt", ios::out );

   // exit program if ofstream could not open file
   if( !outFile )
   {
      cout << "File could not be opened" << endl;
      system( "pause" );
      exit( 1 );
   }
   
   for( int i = 0; i < numTestCases; i++ )
   {
      int hugeInt1[ arraySize ] = {};
      int hugeInt2[ arraySize ] = {};
      int hugeInt3[ arraySize ] = {};
      int hugeInt4[ arraySize ] = {};
      int size1 = 1;
      int size2 = 1;
      int size3 = 1;
      int size4 = 1;

      input(inFile, hugeInt1, size1);
      input( inFile, hugeInt2, size2 );
      perform( cout, hugeInt1, hugeInt2, hugeInt3, hugeInt4, size1, size2, size3, size4 );
      perform( outFile, hugeInt1, hugeInt2, hugeInt3, hugeInt4, size1, size2, size3, size4 );
   }

   inFile.close();
   outFile.close();

   system( "pause" );
}

// enable user to input a positive huge integer
void input( istream &inFile, int hugeInt[], int &size )
{
   char numericString[ arraySize ];

   inFile >> numericString;

   size = strlen( numericString );
   for( int i = 0; i < size; ++i )
      hugeInt[ i ] = numericString[ size - i - 1 ] - '0';
}

// perform addition, subtraction, multiplication and division
void perform( ostream &outFile, int hugeInt1[], int hugeInt2[], int hugeInt3[],
              int hugeInt4[], int size1, int size2, int size3, int size4 )
{
   output( outFile, hugeInt1, size1 );
   output( outFile, hugeInt2, size2 );

   // hugeInt3 = hugeInt1 + hugeInt2
   addition( hugeInt1, hugeInt2, hugeInt3, size1, size2, size3 );
   output( outFile, hugeInt3, size3 );

   // if hugeInt1 < hugeInt2
   if( less( hugeInt1, hugeInt2, size1, size2 ) )
   {
      outFile << '-';
      // hugeInt3 = hugeInt2 - hugeInt1
      subtraction( hugeInt2, hugeInt1, hugeInt3, size2, size1, size3 );
      output( outFile, hugeInt3, size3 ); // outputs n2 - n1
   }
   else
   {
      // hugeInt3 = hugeInt1 - hugeInt2
      subtraction( hugeInt1, hugeInt2, hugeInt3, size1, size2, size3 );
      output( outFile, hugeInt3, size3 ); // outputs n1 - n2
   }

   // hugeInt3 = hugeInt1 * hugeInt2
   multiplication( hugeInt1, hugeInt2, hugeInt3, size1, size2, size3 );
   output( outFile, hugeInt3, size3 ); // outputs n1 * n2

   if( isZero( hugeInt2, size2 ) )
   {
      outFile << "DivideByZero!\n";
      outFile << "DivideByZero!\n";
   }
   else
   {
      division( hugeInt1, hugeInt2, hugeInt3, hugeInt4, size1, size2, size3, size4 );
      output( outFile, hugeInt3, size3 );         // outputs n1 / n2
      output( outFile, hugeInt4, size4 );         // outputs n1 % n2
   }

   outFile << endl;
}

// output the specified huge integer
void output( ostream &outFile, int hugeInt[], int size )
{
   if( isZero( hugeInt, size ) )
      outFile << 0;
   else
      for( int i = size - 1; i >= 0; i-- )
         if( hugeInt[ i ] < 10 )
            outFile << hugeInt[ i ];

   outFile << endl;
}

// returns true if and only if the specified huge integer is zero
bool isZero( int hugeInt[], int size )
{
   for( int i = 0; i < size; i++ )
      if( hugeInt[ i ] != 0 )
         return false;
   return true;
}

// return true if and only if hugeInt1 == hugeInt2
bool equal( int hugeInt1[], int hugeInt2[], int size1, int size2 )
{
	if (size1 == size2)
	{
		return true;
		for (int i = 0; i < size1; i++)
		{
			if (hugeInt1[i] != hugeInt2[i])
				return false;
		}
		return true;
	}
	else
	{
		return false;
	}

}

// returns true if and only if hugeInt1 < hugeInt2
bool less( int hugeInt1[], int hugeInt2[], int size1, int size2 )
{
	if (size1 < size2)
		return true;
	if (size1 > size2)
		return false;
	for (int i = size1 - 1; i >= 0; i--)
	{
		if (hugeInt1[i] > hugeInt2[i])
			return false;
		if (hugeInt1[i] < hugeInt2[i])
			return true;
	}
	return false;

}

// sum = addend + adder
void addition( int addend[], int adder[], int sum[], int addendSize, int adderSize, int &sumSize )
{
   sumSize = ( addendSize >= adderSize ) ? addendSize + 1 : adderSize + 1;

   for( int i = 0; i < addendSize; i++ )
      sum[ i ] = addend[ i ];

   for( int i = addendSize; i < sumSize; i++ )
      sum[ i ] = 0;

   for( int i = 0; i < adderSize; i++ )
      sum[ i ] += adder[ i ];

   for( int i = 0; i < sumSize - 1; i++ )
      if( sum[ i ] > 9 ) // carrying
      {
         sum[ i ] -= 10;
         sum[ i + 1 ]++;
      }

   if( sum[ sumSize - 1 ] == 0 )
      sumSize--;
}

// difference = minuend - subtrahend
void subtraction( int minuend[], int subtrahend[], int difference[],
                  int minuendSize, int subtrahendSize, int &differenceSize )
{
	differenceSize = minuendSize;

	for (int i = 0; i < minuendSize; i++)
		difference[i] = minuend[i];

	for (int i = 0; i < subtrahendSize; i++)
		difference[i] -= subtrahend[i];

	for (int i = 0; i < minuendSize; i++)
	{
		if (difference[i] < 0)
		{
			difference[i] += 10;
			difference[i + 1]--;
		}
	}
	for (int i = minuendSize - 1; difference[i] == 0; i--)
		differenceSize--;

}

// product = multiplicand * multiplier
void multiplication( int multiplicand[], int multiplier[], int product[],
                     int multiplicandSize, int multiplierSize, int &productSize )
{
	 productSize = multiplicandSize + multiplierSize;

	for (int i = 0; i < productSize; i++)
		product[i] = 0;

	for (int i = 0; i < multiplierSize; i++)
	{
		for (int j = 0; j < multiplicandSize; j++)
			product[i + j] += multiplier[i] * multiplicand[j];
	}

	for (int i = 0; i < productSize; i++)
		while (product[i] > 9)
		{
			product[i] -= 10;
			product[i + 1]++;
		}

	for (int i = productSize - 1; product[i] == 0; i--)
		productSize--;

}

// quotient = dividend / divisor; remainder = dividend % divisor
void division( int dividend[], int divisor[], int quotient[], int remainder[],
               int dividendSize, int divisorSize, int &quotientSize, int &remainderSize )
{
	quotientSize = dividendSize - divisorSize + 1;//define quotientSize
	remainderSize = dividendSize;//put dividendSize into remainderSize
	for (int i = 0; i < dividendSize; i++)
		remainder[i] = dividend[i];//put dividend into remainder
	for (int i = 0; i < quotientSize; i++)
		quotient[i] = 0;
	if (!less(dividend, divisor, dividendSize, divisorSize))//if dividend is larger than or equal to divisor,execute the following instructions.
	{
		int buffer[arraySize] ;
		int bufferSize = dividendSize; 
		for (int i = 0; i < divisorSize; i++)
			buffer[dividendSize - divisorSize + i] = divisor[i];//move buffer to left
		for (int i = 0; i < dividendSize - divisorSize; i++)
			buffer[i] = 0;
		for (int i = 1; i <= quotientSize; i++)
		{
			while (!less(remainder, buffer, remainderSize, bufferSize))//when remainder is  larger than or equal to divisor,execute the following instructions.
			{

				int buf2[arraySize];
				int buf2Size = remainderSize;
				for (int j = 0; j < buf2Size; j++)
					buf2[j] = remainder[j];
				subtraction(buf2, buffer, remainder, buf2Size, bufferSize, remainderSize);//execute subtraction function
				quotient[quotientSize - i]++;
			}
			for (int j = 0; j < bufferSize - 1; j++)//let buffer to right
				buffer[j] = buffer[j + 1];
			buffer[bufferSize - 1] = 0;
			bufferSize--;
		}
	}

	for (int i = remainderSize - 1; remainder[i] == 0; i--)
		remainderSize--;
	for (int i = quotientSize - 1; quotient[i] == 0; i--)
		quotientSize--;



}

// hugeInt /= 10
void divideBy10( int hugeInt[], int &size )
{
   if( size == 1 )
      hugeInt[ 0 ] = 0;
   else
   {
      for( int i = 1; i < size; i++ )
         hugeInt[ i - 1 ] = hugeInt[ i ];

      size--;
      hugeInt[ size ] = 0;
   }
}
