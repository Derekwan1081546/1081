//�䤤���
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

float findMedianScore(int* ptrScore, int amounts)
{
	for (int pass = amounts - 1; pass >= 0; pass--) //bubble sort
		for (int i = 0; i < pass; i++)
			if (*(ptrScore + i) > * (ptrScore + i + 1))
			{
				int hold = *(ptrScore + i);
				*(ptrScore + i) = *(ptrScore + i + 1);
				*(ptrScore + i + 1) = hold;
			}
	cout << "    1    2    3    4    5    6    7    8    9   10" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << setw(5) << *(ptrScore + i); //�L�X�Ҧ�����
	}
	if (amounts&2==0)
		return (*(ptrScore + 4) + *(ptrScore + 5)) / 2.0;
	else
		return (*(ptrScore + 5 ));
}

int main()
{
	srand(time(NULL));
	int studentScore[10] = { 0 };
	float median = 0;
	for (int i = 0; i < 10; i++) //��J�ǥͦ��Z
	{
		studentScore[i] = rand() % 100;//�H�����ͦ��Z 
	}
	int size = sizeof(studentScore) / sizeof(studentScore[0]);//�w�qsize 
	median = findMedianScore(studentScore, size);//�I�s findMedianScore function 
	
	cout << endl;
	cout << median << endl; //�L�X���G
	system("pause");
}
