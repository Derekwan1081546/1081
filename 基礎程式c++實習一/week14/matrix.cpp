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
	while (getline(sn, output, ',')) //��Ū�x�}��C��
	{ 
		sm.str("");
		sm.clear();
		sm << output;
		sm >> nm[i];
		i++;
	}
	sn.str("");
	sn.clear();
	int** d = new int* [nm[0]](); //�ŧi�G���}�C
	for (int k = 0; k < nm[0]; k++) 
	{
		d[k] = new int[nm[1]]();
	}

	int j = 0;
	int k;
	while (data >> input)//��Ʀr��J�}�C
	{ 
		i = 0;
		sn.str("");
		sn.clear();
		sn << input;	//�����stringstream

		while (getline(sn, output, ','))	//��ƦrŪ�J�M��r���j�}
		{
			sm.str("");
			sm.clear();
			sm << output;
			sm >> k;
			d[j][i] += k;	//�̫���G�L�}�C�̭�
			i++;
		}
		j++;
	}

	return d;
}

int **matrix(int** mat1, int** mat2, int col1,int col2, int col3, int row1, int row2, int row3) {


	int** result = new int* [col3](); //�ŧi�@�ӤG���}�C
	for (int i = 0; i < col3; i++) {
		result[i] = new int[row3]();
	}

	for (int i = 0; i < row3; i++) { //�@�x�}�p��
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
			cout << mat[i][j] << "  "; //����X 
		}
		cout << endl;
	}

	return 0;
}