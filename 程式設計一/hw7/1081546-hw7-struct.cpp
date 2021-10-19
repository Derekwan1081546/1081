// Huge integer addition, subtraction, multiplication and division
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;

#include <fstream>
using std::ifstream;
using std::ofstream;
using std::ios;

const int numTestCases = 22;
const int arraySize = 200;

// HugeInt struct definition
struct HugeInt
{
   int size = 1;       // the number of digits of the integer; it can never be zero
   int *elems = new int[ 1 ](); // used to store a nonnegative integer, one digit per element
};

// enable user to input a positive huge integer
void input( istream &inFile, HugeInt &hugeInt );

// perform addition, subtraction, multiplication and division
void perform( ostream &outFile, HugeInt &hugeInt1, HugeInt &hugeInt2,
              HugeInt &hugeInt3, HugeInt &hugeInt4 );

// outputs hugeInt.elems[ hugeInt.size - 1 .. 0 ]
void output( ostream &outFile, HugeInt &hugeInt );

// a recursive function that outputs hugeInt.elems[ last .. 0 ]
void recursiveOutput( ostream &outFile, HugeInt &hugeInt, int last );

// returns true if and only if the specified huge integer is zero
bool isZero( HugeInt &hugeInt );

// return true if and only if hugeInt1 == hugeInt2
bool equal( HugeInt &hugeInt1, HugeInt &hugeInt2 );

// a recursive function that returns true if and only if
// hugeInt1.elems[ 0 .. last ] == hugeInt2.elems[ 0 .. last ]
// provided that hugeInt1.size == hugeInt2.size
bool recursiveEqual( HugeInt &hugeInt1, HugeInt &hugeInt2, int last );

// return true if and only if hugeInt1 < hugeInt2
bool less( HugeInt &hugeInt1, HugeInt &hugeInt2 );

// a recursive function that returns true if and only if hugeInt1 < hugeInt2
// provided that hugeInt1.size == hugeInt2.size
bool recursiveLess( HugeInt &hugeInt1, HugeInt &hugeInt2, int last );

// sum = addend + adder
void addition( HugeInt &addend, HugeInt &adder, HugeInt &sum );

// difference = minuend - subtrahend
// provided that the minuend is greater than or equal to the subtrahend
void subtraction( HugeInt &minuend,
                  HugeInt &subtrahend, HugeInt &difference );

// product = multiplicand * multiplier
void multiplication( HugeInt &multiplicand,
                     HugeInt &multiplier, HugeInt &product );

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that the divisor is not equal to 0
void division( HugeInt &dividend, HugeInt &divisor,
               HugeInt &quotient, HugeInt &remainder );

// hugeInt2 = hugeInt1; assignment
void assign( HugeInt &hugeInt1, HugeInt &hugeInt2 );

// hugeInt /= 10
void divideByTen( HugeInt &hugeInt );

void reset( HugeInt &hugeInt );

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

   HugeInt hugeInt1;
   HugeInt hugeInt2;
   HugeInt hugeInt3;
   HugeInt hugeInt4;

   for( int i = 0; i < numTestCases; i++ )
   {
      input( inFile, hugeInt1 );
      input( inFile, hugeInt2 );
      perform( cout, hugeInt1, hugeInt2, hugeInt3, hugeInt4 );
      perform( outFile, hugeInt1, hugeInt2, hugeInt3, hugeInt4 );
      reset( hugeInt1 );
      reset( hugeInt2 );
   }

   delete[] hugeInt1.elems;
   delete[] hugeInt2.elems;
   delete[] hugeInt3.elems;
   delete[] hugeInt4.elems;

   inFile.close();
   outFile.close();

   system( "pause" );
}

// enable user to input a positive huge integer
void input( istream &inFile, HugeInt &hugeInt )
{
   char numericString[ arraySize ];

   inFile >> numericString;

   hugeInt.size = strlen( numericString );
   delete[] hugeInt.elems;
   hugeInt.elems = new int[ hugeInt.size ];
   for( int i = 0; i < hugeInt.size; i++ )
      hugeInt.elems[ i ] = numericString[ hugeInt.size - i - 1 ] - '0';
}

// perform addition, subtraction, multiplication and division
void perform( ostream &outFile, HugeInt &hugeInt1, HugeInt &hugeInt2,
                                HugeInt &hugeInt3, HugeInt &hugeInt4 )
{
   output( outFile, hugeInt1 );
   output( outFile, hugeInt2 );

   addition( hugeInt1, hugeInt2, hugeInt3 ); // hugeInt3 = hugeInt1 + hugeInt2
   output( outFile, hugeInt3 );
   reset( hugeInt3 );

   if( less( hugeInt1, hugeInt2 ) )
   {
      outFile << '-';
      subtraction( hugeInt2, hugeInt1, hugeInt3 ); // hugeInt3 = hugeInt2 - hugeInt1
      output( outFile, hugeInt3 );
   }
   else
   {
      subtraction( hugeInt1, hugeInt2, hugeInt3 ); // hugeInt3 = hugeInt1 - hugeInt2
      output( outFile, hugeInt3 );
   }
   reset( hugeInt3 );

   multiplication( hugeInt1, hugeInt2, hugeInt3 ); // hugeInt3 = hugeInt1 * hugeInt2
   output( outFile, hugeInt3 );
   reset( hugeInt3 );

   if( isZero( hugeInt2 ) )
   {
      outFile << "DivideByZero!\n";
      outFile << "DivideByZero!\n";
   }
   else
   {
      // hugeInt3 = hugeInt1 / hugeInt2;   hugeInt4 = hugeInt1 % hugeInt2
      division( hugeInt1, hugeInt2, hugeInt3, hugeInt4 );
      output( outFile, hugeInt3 );
      output( outFile, hugeInt4 );
      reset( hugeInt3 );
      reset( hugeInt4 );
   }

   outFile << endl;
}

// outputs hugeInt.elems[ hugeInt.size - 1 .. 0 ]
void output( ostream &outFile, HugeInt &hugeInt )
{
   recursiveOutput( outFile, hugeInt, hugeInt.size - 1 );
   outFile << endl;
}

// a recursive function that outputs hugeInt.elems[ last .. 0 ]
void recursiveOutput( ostream &outFile, HugeInt &hugeInt, int last )
{
	outFile << hugeInt.elems[last];
	if (last > 0)
		recursiveOutput(outFile, hugeInt, last - 1);

}

// returns true if and only if the specified huge integer is zero
bool isZero( HugeInt &hugeInt )
{
   if( hugeInt.size == 1 && hugeInt.elems[ 0 ] == 0 )
      return true;
   return false;
}

// return true if and only if hugeInt1 == hugeInt2
bool equal( HugeInt &hugeInt1, HugeInt &hugeInt2 )
{
   if( hugeInt1.size != hugeInt2.size )
      return false;

   return recursiveEqual( hugeInt1, hugeInt2, hugeInt1.size - 1 );
}

// a recursive function that returns true if and only if
// hugeInt1.elems[ 0 .. last ] == hugeInt2.elems[ 0 .. last ]
// provided that hugeInt1.size == hugeInt2.size
bool recursiveEqual( HugeInt &hugeInt1, HugeInt &hugeInt2, int last )
{
	if (last == 0)
		return true;
	if (hugeInt1.elems[last] != hugeInt2.elems[last])
		return false;
	return recursiveEqual(hugeInt1, hugeInt2, last - 1);

}

// returns true if and only if hugeInt1 < hugeInt2
bool less( HugeInt &hugeInt1, HugeInt &hugeInt2 )
{
   if( hugeInt1.size < hugeInt2.size )
      return true;
   if( hugeInt1.size > hugeInt2.size )
      return false;

   return recursiveLess( hugeInt1, hugeInt2, hugeInt1.size - 1 );
}

// a recursive function that returns true if and only if
// hugeInt1.elems[ 0 .. last ] < hugeInt2.elems[ 0 .. last ]
// provided that hugeInt1.size == hugeInt2.size
bool recursiveLess( HugeInt &hugeInt1, HugeInt &hugeInt2, int last )
{
	if (hugeInt1.elems[last] < hugeInt2.elems[last])
		return true;
	if (hugeInt1.elems[last] > hugeInt2.elems[last])
		return false;
	if (last < 0)
		return false;
	return recursiveLess(hugeInt1, hugeInt2, last - 1);

}

// sum = addend + adder
void addition( HugeInt &addend, HugeInt &adder, HugeInt &sum )
{
   sum.size = ( addend.size >= adder.size ) ? addend.size + 1 : adder.size + 1;

   delete [] sum.elems;
   sum.elems = new int[ sum.size ]();

   for( int i = 0; i < addend.size; i++ )
      sum.elems[ i ] = addend.elems[ i ];

   for( int i = 0; i < adder.size; i++ )
      sum.elems[ i ] += adder.elems[ i ];

   for( int i = 0; i < sum.size - 1; i++ )
      if( sum.elems[ i ] > 9 ) // determine whether to carry a 1
      {
         sum.elems[ i ] -= 10; // reduce to 0-9
         sum.elems[ i + 1 ]++;
      }

   if( sum.elems[ sum.size - 1 ] == 0 )
      sum.size--;
}

// difference = minuend - subtrahend
// provided that the minuend is greater than or equal to the subtrahend
void subtraction( HugeInt &minuend,
                  HugeInt &subtrahend, HugeInt &difference )
{
	difference.size = minuend.size;
	delete[] difference.elems;
	difference.elems = new int[difference.size]();

	for (int i = 0; i < minuend.size; i++)
		difference.elems[i] = minuend.elems[i];

	for (int i = 0; i < subtrahend.size; i++)
		difference.elems[i] -= subtrahend.elems[i];

	for (int i = 0; i < difference.size-1; i++)
	{
		if (difference.elems[i] < 0)
		{
			difference.elems[i] += 10;
			difference.elems[i + 1]--;
		}
	}
	for (int i = minuend.size - 1; difference.elems[i] == 0 && i > 0; i--)
		difference.size--;

}

// product = multiplicand * multiplier
void multiplication( HugeInt &multiplicand,
                     HugeInt &multiplier, HugeInt &product )
{
	product.size = multiplicand.size + multiplier.size;
	delete[] product.elems;
	product.elems = new int[product.size]();


	for (int i = 0; i < multiplier.size; i++)
	{
		for (int j = 0; j < multiplicand.size; j++)
			product.elems[i + j] += multiplier.elems[i] * multiplicand.elems[j];
	}

	for (int i = 0; i < product.size-1; i++)
		while (product.elems[i] > 9)
		{
			product.elems[i] -= 10;
			product.elems[i + 1]++;
		}

	for (int i = product.size - 1; product.elems[i] == 0 && i > 0; i--)
		product.size--;

}

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that the divisor is not equal to 0
void division( HugeInt &dividend, HugeInt &divisor,
               HugeInt &quotient, HugeInt &remainder )
{
   if( isZero( dividend ) )
   {
      reset( quotient );
      reset( remainder );
      return;
   }
   if (!less(dividend, divisor))//if dividend is larger than or equal to divisor,execute the following instructions.
	{
		quotient.size = dividend.size - divisor.size + 1;//define quotientSize
		remainder.size = dividend.size;//put dividendSize into remainderSize
		delete[] quotient.elems;
		quotient.elems = new int[quotient.size] ();
		delete[] remainder.elems;
		remainder.elems = new int[remainder.size] ();

		HugeInt buffer, buf2;
		
		buffer.size = dividend.size;
		buf2.size = remainder.size;
		delete[] buffer.elems;
		buffer.elems = new int[buffer.size]();
		delete[] buf2.elems;
		buf2.elems = new int[buf2.size]();

		for (int i = divisor.size - 1, j = dividend.size - 1; i >= 0; i--, j--)
			buffer.elems[j] = divisor.elems[i];

		for (int i = 0; i < dividend.size; i++)
			remainder.elems[i] = dividend.elems[i];//put dividend into remainder

		for (int i = quotient.size - 1; i >= 0; i--)
	   {
			while (!less(remainder, buffer))//when remainder is  larger than or equal to divisor,execute the following instructions.
			{
				 buf2.size = remainder.size;

				for (int j = 0; j < buf2.size; j++)
					buf2.elems[j] = remainder.elems[j];
				subtraction(buf2, buffer, remainder);//execute subtraction function
				quotient.elems[i]++;
				
			}
			for (int j = 0; j < buffer.size - 1; j++)//let buffer to right
				buffer.elems[j] = buffer.elems[j + 1];
			buffer.elems[buffer.size - 1] = 0;
			buffer.size--;
			
		}
		for (int i = remainder.size - 1; remainder.elems[i] == 0 && i > 0; i--)
			remainder.size--;
		for (int i = quotient.size - 1; quotient.elems[i] == 0 && i > 0; i--)
			quotient.size--;
		delete[] buffer.elems;
		delete[] buf2.elems;
	}
	else
	{
		quotient.size = 1;
		remainder.size = dividend.size;

		delete[] quotient.elems;
		quotient.elems = new int[quotient.size]();
		delete[] remainder.elems;
		remainder.elems = new int[remainder.size]();

		quotient.elems[0] = 0;
		for (int i = 0; i < dividend.size; i++)
			remainder.elems[i] = dividend.elems[i];
	}

}

// hugeInt2 = hugeInt1; assignment
void assign( HugeInt &hugeInt1, HugeInt &hugeInt2 )
{
   hugeInt2.size = hugeInt1.size;
   delete[] hugeInt2.elems;
   hugeInt2.elems = new int[ hugeInt2.size ];
   for( int i = 0; i < hugeInt2.size; i++ )
      hugeInt2.elems[ i ] = hugeInt1.elems[ i ];
}

// hugeInt /= 10
void divideByTen( HugeInt &hugeInt )
{
   if( hugeInt.size == 1 )
      hugeInt.elems[ 0 ] = 0;
   else
   {
      for( int i = 1; i < hugeInt.size; i++ )
         hugeInt.elems[ i - 1 ] = hugeInt.elems[ i ];

      hugeInt.size--;
      hugeInt.elems[ hugeInt.size ] = 0;
   }
}

void reset( HugeInt &hugeInt )
{
   hugeInt.size = 1;
   delete[] hugeInt.elems;
   hugeInt.elems = new int[ 1 ]();
}
