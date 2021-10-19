//Dynamic memory allocation
#include<iostream>
using namespace std;
void createMatrixFromArray(int**&mat, int*array)
{
	mat = new int* [3]();
	for (int i = 0; i < 3; i++)
		mat[i] = new int[3]();

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			*(*(mat + i) + j) = *(array + i * 3 + j);	//一維資料指派到二維
}

int** multiplicateMatrix(int**mat1, int**mat2)	//做陣列乘法 
{
	int** result=NULL;
	result = new int*[3]();
	for (int i = 0; i < 3; i++)
		result[i] = new int[3]();
	for(int k=0;k<3;k++)	//先做橫排 
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				result[i][j]+= mat1[i][k]*mat2[k][j];	//橫先不動

	return result;
}

void printMatrix(int**result)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			cout << result[i][j] << " ";	//印出陣列 
		cout << endl;
	}
}

int destroyMatrix(int** mat)
{
	for (int i=0;i<3;i++)
	{
		delete[] mat[i];	//先刪橫排 
	}
	delete[] mat;	//在刪直排 
	mat = NULL;
	return 0;
}

int main()
{
	int array1[9] = {48,69,8,24,79,24,32,59,10};
	int array2[9] = { 18,26,47,90,31,36,2,47,98 };
	int** mat1 = NULL;
	int** mat2 = NULL;

	createMatrixFromArray(mat1, array1);
	createMatrixFromArray(mat2, array2);

	int** mat3 = multiplicateMatrix(mat1, mat2);

	printMatrix(mat1);
	cout << endl;
	printMatrix(mat2);
	cout << endl;
	printMatrix(mat3);
	cout << endl;

	destroyMatrix(mat1);
	destroyMatrix(mat2);
	destroyMatrix(mat3);

	system("pause");
}
