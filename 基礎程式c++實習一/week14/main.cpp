#include <iostream>
#include <fstream>
#include <vector>
#include "matrix.h"
using namespace std;

int main() {


	int nm1[2], nm2[2];
	ifstream data1("A.csv", ios::in); 
	ifstream data2("B.csv", ios::in);

	int **d1=load(data1, nm1); //讀檔
	int **d2=load(data2, nm2);
	int col1 = nm1[0];
	int col2 = nm2[0];
	int row1 = nm1[1];
	int row2 = nm2[1];
	int col3 = row2; //運算後的行列數
	int row3 = col1;
	if (row1 != col2) { //無法運算
		cout << "陣列無法運算\n";
		exit(1);
	}
	cout << "mat1: " << endl; //輸出
	cout << endl;
	printMatrix(d1, nm1[0], nm1[1]);
	cout << endl;
	cout << "mat2: " << endl;
	cout << endl;
	printMatrix(d2, nm2[0], nm2[1]);
	//cout << col3 << row3 << endl;
	int **result = matrix(d1, d2, col1, col2 ,col3, row1, row2, row3); //計算
	cout << endl;
	cout << "result: " << endl;
	cout << endl;
	printMatrix(result, row3, col3);

	return 0;
}