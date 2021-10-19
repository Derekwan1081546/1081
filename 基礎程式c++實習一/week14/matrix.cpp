#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "matrix.h"
using namespace std;
int **load(ifstream &data, int nm[]) {

	stringstream sn,sm;
	string input,output;
	data >> input;
	sn << input;
	int i = 0;
	while (getline(sn, output, ',')) //先讀矩陣行列數
	{ 
		sm.str("");
		sm.clear();
		sm << output;
		sm >> nm[i];
		i++;
	}
	sn.str("");
	sn.clear();
	int** d = new int* [nm[0]](); //宣告二元陣列
	for (int k = 0; k < nm[0]; k++) 
	{
		d[k] = new int[nm[1]]();
	}

	int j = 0;
	int k;
	while (data >> input)//把數字放入陣列
	{ 
		i = 0;
		sn.str("");
		sn.clear();
		sn << input;	//先放到stringstream

		while (getline(sn, output, ','))	//把數字讀入然後逗號隔開
		{
			sm.str("");
			sm.clear();
			sm << output;
			sm >> k;
			d[j][i] += k;	//最後放到二微陣列裡面
			i++;
		}
		j++;
	}

	return d;
}

int **matrix(int** mat1, int** mat2, int col1,int col2, int col3, int row1, int row2, int row3) {


	int** result = new int* [col3](); //宣告一個二維陣列
	for (int i = 0; i < col3; i++) {
		result[i] = new int[row3]();
	}

	for (int i = 0; i < row3; i++) { //作矩陣計算
		for (int j = 0; j < col3; j++) {
			for (int k = 0; k < col2; k++) {
				result[i][j] += mat1[i][k] * mat2[k][j];
			}
		}
	}

	return result;
}

int printMatrix(int** mat, int row, int col) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << mat[i][j] << "  "; //做輸出 
		}
		cout << endl;
	}

	return 0;
}