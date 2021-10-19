#include <iostream>
#include <fstream>
using namespace::std;

// reads in a C++ program from a cpp file, and put it to the array program
void load(char(*program)[100], int& numLines);

// deletes the comment beginning with "//" from sourceLine if any
void delComment(char sourceLine[]);

// deletes all string constants from sourceLine
void delStrConsts(char sourceLine[]);

// deletes all character constants from sourceLine
void delCharConsts(char sourceLine[]);

// extracts all identifiers from sourceLine, and put them into the array identifiers
void extractIdentifiers(char sourceLine[], char identifiers[][32], int& numIdentifiers);

// stores all non-keyword strings in the array identifiers into a text file
void store(char(*identifiers)[32], int numIdentifiers);

// returns true if and only if str is a C++ keyword
bool keyword(char str[]);

// returns true if and only if identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate(char(*identifiers)[32], int pos);

const char keywords[][20] = { "auto", "break", "case", "char", "const",
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
	char(*program)[100] = new char[500][100];
	int numLines = 0;

	// reads in a C++ program from a cpp file, and put it to the array program
	load(program, numLines);

	char(*identifiers)[32] = new char[500][32];
	int numIdentifiers = 0;

	for (int i = 0; i < numLines; i++)
	{
		delComment(program[i]); // deletes the comment beginning with "//" from program[ i ]
		delStrConsts(program[i]); // deletes all string constants from program[ i ]
		delCharConsts(program[i]); // deletes all character constants from program[ i ]

		if (strcmp(program[i], "") != 0)
			extractIdentifiers(program[i], identifiers, numIdentifiers);
		// extracts all identifiers from program[ i ], and put them into the array identifiers
	}
	// stores all non-keyword strings in the array identifiers into a text file
	store(identifiers, numIdentifiers);

	system("pause");
}
// reads in a C++ program from a cpp file, and put it to the array program
void load(char(*program)[100], int& numLines)
{
	ifstream inFile("test.cpp", ios::in);	//Open an existing file

	if (!inFile)//if could not find the file
	{
		cout << "File could not be opened" << endl;
		exit(1);
	}
	while (inFile.getline(program[numLines], 100, '\n'))
		if (strcmp(program[numLines], "") != 0)	//確認是否為空字串 
			numLines++;
	inFile.close();
}

// deletes the comment beginning with "//" from sourceLine if any
void delComment(char sourceLine[])
{
	int i = 0, size = strlen(sourceLine);
	while (sourceLine[i] != '/'&& sourceLine[i+1] !='/' && i < size)	//刪掉註解
		i++;
	if (i < size)
		sourceLine[i] = '\0';
}

// deletes all string constants from sourceLine
void delStrConsts(char sourceLine[])
{
	int size = strlen(sourceLine);
	for (int i = 0; i < size; i++)		//把字串的符號刪掉並且轉換成空白鍵
		if (sourceLine[i] == '"')
		{
			sourceLine[i] = ' ';
			while (sourceLine[i] != '"')
			{
				sourceLine[i] = ' ';
				i++;
			}
			sourceLine[i] = ' ';
		}
}

// deletes all character constants from sourceLine
void delCharConsts(char sourceLine[])
{
	int size = strlen(sourceLine);
	for (int i = 0; i < size; i++)	//把字元的符號刪掉並且轉換成空白鍵
		if (sourceLine[i] == '\'')
		{
			sourceLine[i] = ' ';
			while (sourceLine[i] != '\'')
			{
				sourceLine[i] = ' ';
				i++;
			}
			sourceLine[i] = ' ';
		}
}

// extracts all identifiers from sourceLine, and put them into the array identifiers
void extractIdentifiers(char sourceLine[], char identifiers[][32], int& numIdentifiers)
{
	int size = strlen(sourceLine), j = 0;
	for (int i = 0; i < size; i++)	//delete the alphabet notation and the number range from 0 to 9 to extract identifiers
	{
		if ('0' <= sourceLine[i] && sourceLine[i] <= '9')
			if (sourceLine[i - 1] == ' ')
				sourceLine[i] = ' ';
		if ('!' <= sourceLine[i] && sourceLine[i] <= '/' && sourceLine[i] != '"')
			sourceLine[i] = ' ';
		if (':' <= sourceLine[i] && sourceLine[i] <= '@')
			sourceLine[i] = ' ';
		if ('[' <= sourceLine[i] && sourceLine[i] <= '^')
			sourceLine[i] = ' ';
		if ('{' <= sourceLine[i] && sourceLine[i] <= '~')
			sourceLine[i] = ' ';
	}
	size = strlen(sourceLine);
	for (int i = 0; i < size; i++)	//刪掉空白建然後每輸出一個就換行
	{
		while (sourceLine[i] == ' ')
			i++;
		j = 0;
		while (sourceLine[i] != ' ')
		{
			identifiers[numIdentifiers][j] = sourceLine[i];
			j++;
			i++;
		}
		identifiers[numIdentifiers][j] = '\0';
		if (!duplicate(identifiers, numIdentifiers) && strcmp(identifiers[numIdentifiers], "") != 0)	//確認是否重複輸出相同的數字且是否為空字串
			numIdentifiers++;
		else
			identifiers[numIdentifiers][0] = '\0';
	}
}

// stores all non-keyword strings in the array identifiers into a text file
void store(char(*identifiers)[32], int numIdentifiers)
{
	ofstream outfile("ans1.txt",ios::out);
	for (int i = 0; i < numIdentifiers; i++)
	{
		if (!keyword(identifiers[i]))
			outfile << identifiers[i] << endl;	//output identifiers
	}
	outfile.close();
}

// returns true if and only if str is a C++ keyword
bool keyword(char str[])
{
	for (int i = 0; i < 62; i++)	//確認是否為上面所提到的keyword 
	{
		if (strcmp(str, keywords[i]) == 0)
			return true;
	}
	return false;
}

// returns true if and only if identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate(char(*identifiers)[32], int pos)
{
	for (int i = 0; i < pos; i++)	//確認identifier是否重複 
	{
		if (strcmp(identifiers[pos], identifiers[i]) == 0)	
			return true;
	}
	return false;
}
