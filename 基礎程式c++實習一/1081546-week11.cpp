#include <iostream>
#include <sstream>
#include <fstream> 
#include <string>
#include <iomanip>
using namespace std;
int main(int argc, const char* argv[])
{
	stringstream ss;
	ifstream infile("records.csv",ios::in);
	string id[11], name[11], weight[11], height[11];
	int buf[11];
	if (!infile)
	{
		cout << "File could not be opened.";
		exit(1);
	}
	for (int i = 0;getline(infile, id[i], ','); i++)
	{
		
		getline(infile, name[i], ',');
		getline(infile, weight[i], ',');
		getline(infile, height[i], '\n');
	}
	//Convert string to integer
	for (int i = 0; i < 10; i++)
	{
		ss.str("");
		ss.clear();
		ss << weight[i];
		ss >> buf[i];
	}
	//calculate the average weight
	float result = 0;
	for (int i = 0; i < 10; i++)
	{
		result += buf[i];
	}
	cout << "average weight: " << result/10 << endl;

	//Convert string to integer

	for (int i = 0; i < 10; i++)
	{
		ss.str("");
		ss.clear();
		ss << height[i];
		ss >> buf[i];
	}
	//calculate the average height
	result = 0;
	for (int i = 0; i < 10; i++)
	{
		result += buf[i];
	}
	cout << "average height: " << result/10 << endl;
	//Output all the datawhich is sorted by height.
	int big[10];
	for (int i = 0; i < 10; i++)
	{
		big[i] = 0;
		for (int j = 0; j < 10; j++)
		{
			if (buf[big[i]] < buf[j])//orif (buf[big[i]] > buf[j])
			{
				big[i] = j;
			}
		}
		buf[big[i]] = 0;//or buf[big[i]] = 999
	}
	for (int i = 0; i < 10; i++)
	{
		cout << i + 1 << " " << name[big[i]] << " " << weight[big[i]] << " " << height[big[i]] << endl;
	}
	
	return 0;
} 
