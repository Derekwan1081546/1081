#include <iostream>
#include <fstream>
#include <string>
using namespace::std;

// reads in a C++ program from a cpp file, and put it to the array program
void load(string* program, int& numLines);

// deletes the comment beginning with "//" from sourceLine if any
void delComment(string& sourceLine);

// deletes all string constants from sourceLine
void delStrConsts(string& sourceLine);

// deletes all character constants from sourceLine
void delCharConsts(string& sourceLine);

// deletes the first identifier from sourceLine, and returns it
string delFirstIdentifier(string& sourceLine);

// stores all non-keyword strings in the array identifiers into a text file
void store(string* identifiers, int numIdentifiers);

// return true if and only if "str" is a C++ keyword
bool keyword(string str);

// returns true if and only if identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate(string* identifiers, int pos);

const string keywords[] = { "auto", "break", "case", "char", "const",
							"continue", "default", "define","do", "double",
							"else", "enum", "extern", "float", "for",
							"goto", "if", "int", "long", "register",
							"return", "short", "signed", "sizeof",
							"static", "struct", "switch", "typedef",
							"union", "unsigned", "void", "volatile",
							"while", "bool", "catch", "class",
							"const_cast", "delete", "dynamic_cast",
							"explicit", "false", "friend", "inline",
							"mutable", "namespace", "new", "operator",
							"private", "protected", "public",
							"reinterpret_cast", "static_cast", "template",
							"this", "throw", "true", "try", "typeid",
							"typename", "using", "virtual", "include" };


int main()
{
	string* program = new string[500];
	int numLines = 0;

	// reads in a C++ program from a cpp file, and put it to the array program
	load(program, numLines);

	string* identifiers = new string[500];
	string firstIdentifier;
	string null;
	int numIdentifiers = 0;

	for (int i = 0; i < numLines; i++)
	{
		delComment(program[i]); // deletes the comment beginning with "//" from program[ i ]
		delStrConsts(program[i]); // deletes all string constants from program[ i ]
		delCharConsts(program[i]); // deletes all character constants from program[ i ]

		// extracts all identifiers from program[ i ], and put them into the array identifiers
		while ((firstIdentifier = delFirstIdentifier(program[i])) != null)
			identifiers[numIdentifiers++] = firstIdentifier;
	}

	// stores all non-keyword strings in the array identifiers into a text file
	store(identifiers, numIdentifiers);

	system("pause");
}
// reads in a C++ program from a cpp file, and put it to the array program
void load(string* program, int& numLines)
{
	ifstream input("test.cpp", ios::in);			//input file

	if (!input)			//if could not find the file
	{
		cout << "File could not be opened" << endl;
		exit(1);
	}
	while (getline(input, program[numLines], '\n'))
		numLines++;
	input.close();
}

// deletes the comment beginning with "//" from sourceLine if any
void delComment(string& sourceLine)
{
	if (sourceLine.find("//") != string::npos)				//刪掉註解
	{
		sourceLine.erase(sourceLine.begin() + sourceLine.find("//"), sourceLine.end());
	}
}

// deletes all string constants from sourceLine
void delStrConsts(string& sourceLine)
{
	if (sourceLine.find("\"") != string::npos)				//把字串的符號刪掉
	{
		int a = sourceLine.find("\"");
		sourceLine.erase(sourceLine.find("\"", a));
	}
}

// deletes all character constants from sourceLine
void delCharConsts(string& sourceLine)
{
	if (sourceLine.find("'") != string::npos)				//把字元的符號刪掉
	{
		int a = sourceLine.find("'");
		sourceLine.erase(sourceLine.find("'", a));
	}
}

// deletes the first identifier from sourceLine, and returns it
string delFirstIdentifier(string& sourceLine)		//delete the  notation and the number range from 0 to 9 to extract identifiers
{
	string buf;
	int num;
	if (sourceLine.find_first_of("_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != string::npos)
	{
		buf = sourceLine;
		num = sourceLine.find_first_of("_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
		sourceLine.erase(sourceLine.begin() + num, sourceLine.begin() + sourceLine.find_first_not_of("_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", num));
		num = buf.find_first_of("_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
		buf.erase(buf.begin(), buf.begin() + num);
		buf.erase(buf.begin() + buf.find_first_not_of("_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"), buf.end());
	}
	return buf;
}

// stores all non-keyword strings in the array identifiers into a text file
void store(string* identifiers, int numIdentifiers)
{
	ofstream outfile("ans2.txt",ios::out);	//open file
	for (int i = 0; i < numIdentifiers; i++)
	{
		if (!keyword(identifiers[i]) && !duplicate(identifiers, i))
			outfile << identifiers[i] << endl;	//output identifiers
	}
	outfile.close();
}

// return true if and only if "str" is a C++ keyword
bool keyword(string str)
{
	for (int i = 0; i < 62; i++)		//確認是否為上面所提到的keyword 
	{
		if (str == keywords[i])
			return true;
	}
	return false;
}

// returns true if and only if identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate(string* identifiers, int pos)
{
	for (int i = 0; i < pos; i++)		//確認identifier是否重複 
	{
		if (identifiers[pos] == identifiers[i])
			return true;
	}
	return false;
}
