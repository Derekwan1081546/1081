#include<iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;
struct record //建立一個struct
{
	int id;
	unsigned char name[16];
	int weight;
	int height;
	float bmi;
};
int main()
{
	ifstream infile("records.csv", ios::in);//開檔
	stringstream ss, sn;

	string value;
	string buf[10][4];
	int count = 0;//行數
	record file[10];//宣告一個struct
	if (!infile)
	{
		cout << "File could not be opened.";
		exit(1);
	}
	
	while (getline(infile, value ))//先把所有的資料都讀進來
	{
		sn.str("");
		sn.clear();
		sn << value;
		
		for (int i = 0; i < 4; i++)//再一行一行讀
		{
			getline(sn, buf[count][i], ',');//然後裡面的內容用逗號隔開
		}
		count++;//換下一行
	}

	for (int i = 0; i < 10; i++)//把剛剛讀入的每一行的第一個值讀到struct裡面的id
	{
		ss.str("");
		ss.clear();
		ss << buf[i][0];
		ss >> file[i].id;

	}
	for (int i = 0; i < 10; i++)//把剛剛讀入的每一行的第二個值讀到struct裡面的name
	{
		ss.str("");
		ss.clear();
		ss << buf[i][1];
		ss >> file[i].name;
	}
	for (int i = 0; i < 10; i++)//把剛剛讀入的每一行的第三個值讀到struct裡面的weight
	{
		ss.str("");
		ss.clear();
		ss << buf[i][2];
		ss >> file[i].weight;
	}


	for (int i = 0; i < 10; i++)//把剛剛讀入的每一行的第四個值讀到struct裡面的height
	{
		ss.str("");
		ss.clear();
		ss << buf[i][3];
		ss >> file[i].height;
	}
	//計算BMI
	float height[10];
	for (int i = 0; i < 10; i++)//先計算身高(公尺)的平方
	{
		height[i] = pow(file[i].height / 100.0, 2);
	}

	for (int i = 0; i < 10; i++)//然後再計算BMI
	{
		file[i].bmi = file[i].weight / height[i];
	}

	ofstream outfile("records.dat", ios::binary | ios::out);//開一個dat檔
	for (int i = 0; i < 10; i++)
	{
		outfile.write(reinterpret_cast<char*>(&file[i]), sizeof(file[i]));	//先把資料寫入檔案內並把string轉成char
	}
	outfile.close();//先關檔

	ifstream binaryfile("records.dat", ios::binary | ios::in);//再開檔
	for (int i = 0; i < 10; i++)
	{
		binaryfile.read(reinterpret_cast<char*>(&file[i]), sizeof(file[i]));//再把剛剛寫入的東西讀入
		if(file[i].bmi<18.5)//最後印出BMI小於18.5的條件
			cout << file[i].id << setw(15) << file[i].name << setw(15) << file[i].weight << setw(15) << file[i].height << setw(15) << file[i].bmi << endl;
	}
	system("pause");
}