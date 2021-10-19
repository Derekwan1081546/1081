#ifndef MATRIX_H 
#define  MATRIX_H 
#include <fstream>
#include <vector>
using namespace std;
int **matrix(int **mat1, int **mat2, int col1,int col2,int col3,int row1,int row2,int row3);
int **load(ifstream &data , int nm[]);
int printMatrix(int** mat, int row, int col);
#endif 
