#include<iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;
struct record //�إߤ@��struct
{
	int id;
	unsigned char name[16];
	int weight;
	int height;
	float bmi;
};
int main()
{
	ifstream infile("records.csv", ios::in);//�}��
	stringstream ss, sn;

	string value;
	string buf[10][4];
	int count = 0;//���
	record file[10];//�ŧi�@��struct
	if (!infile)
	{
		cout << "File could not be opened.";
		exit(1);
	}
	
	while (getline(infile, value ))//����Ҧ�����Ƴ�Ū�i��
	{
		sn.str("");
		sn.clear();
		sn << value;
		
		for (int i = 0; i < 4; i++)//�A�@��@��Ū
		{
			getline(sn, buf[count][i], ',');//�M��̭������e�γr���j�}
		}
		count++;//���U�@��
	}

	for (int i = 0; i < 10; i++)//����Ū�J���C�@�檺�Ĥ@�ӭ�Ū��struct�̭���id
	{
		ss.str("");
		ss.clear();
		ss << buf[i][0];
		ss >> file[i].id;

	}
	for (int i = 0; i < 10; i++)//����Ū�J���C�@�檺�ĤG�ӭ�Ū��struct�̭���name
	{
		ss.str("");
		ss.clear();
		ss << buf[i][1];
		ss >> file[i].name;
	}
	for (int i = 0; i < 10; i++)//����Ū�J���C�@�檺�ĤT�ӭ�Ū��struct�̭���weight
	{
		ss.str("");
		ss.clear();
		ss << buf[i][2];
		ss >> file[i].weight;
	}


	for (int i = 0; i < 10; i++)//����Ū�J���C�@�檺�ĥ|�ӭ�Ū��struct�̭���height
	{
		ss.str("");
		ss.clear();
		ss << buf[i][3];
		ss >> file[i].height;
	}
	//�p��BMI
	float height[10];
	for (int i = 0; i < 10; i++)//���p�⨭��(����)������
	{
		height[i] = pow(file[i].height / 100.0, 2);
	}

	for (int i = 0; i < 10; i++)//�M��A�p��BMI
	{
		file[i].bmi = file[i].weight / height[i];
	}

	ofstream outfile("records.dat", ios::binary | ios::out);//�}�@��dat��
	for (int i = 0; i < 10; i++)
	{
		outfile.write(reinterpret_cast<char*>(&file[i]), sizeof(file[i]));	//�����Ƽg�J�ɮפ��ç�string�নchar
	}
	outfile.close();//������

	ifstream binaryfile("records.dat", ios::binary | ios::in);//�A�}��
	for (int i = 0; i < 10; i++)
	{
		binaryfile.read(reinterpret_cast<char*>(&file[i]), sizeof(file[i]));//�A����g�J���F��Ū�J
		if(file[i].bmi<18.5)//�̫�L�XBMI�p��18.5������
			cout << file[i].id << setw(15) << file[i].name << setw(15) << file[i].weight << setw(15) << file[i].height << setw(15) << file[i].bmi << endl;
	}
	system("pause");
}