#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

void printSolution(int path[], int V);
/* A recursive utility function to solve hamiltonian cycle problem */
void hamCycleUtil(bool** graph, int path[], int V, int last, int turn, bool** ori)
{
	if (turn == V)
	{
		if (ori[path[0]][path[V - 1]] == 1)
			printSolution(path, V);
		else
			path[V - 1] = -1;
		return;
	}
	bool** data;
	data = new bool* [V];
	for (int i = 0; i < V; i++)
		data[i] = new bool[V];
	for (int i = 0; i < V; i++)
		if (graph[last][i] == 1)
		{
			for (int k = 0; k < V; k++)
				for (int j = 0; j < V; j++)
					data[k][j] = graph[k][j];
			for (int j = 0; j < V; j++)
				data[j][last] = 0;
			path[turn] = i;
			hamCycleUtil(data, path, V, i, turn + 1, ori);
		}
	for (int j = 0; j < V; j++)
		delete[] data[j];
	delete[] data;
	return;
}

/* solves the Hamiltonian Cycle problem using Backtracking.*/
void hamCycle(bool** graph, int V, int start)
{
	int num = 1;
	int* path = new int[V];
	for (int i = 0; i < V; i++)
		path[i] = -1;
	path[0] = start;
	hamCycleUtil(graph, path, V, start, num, graph);
	if (path[V - 1] == -1)
		cout << "\nSolution does not exist" << endl;
	delete[] path;
}

/* A utility function to print solution */
void printSolution(int path[], int V)
{
	char num;
	for (int i = 0; i < V; i++)
	{
		num = (char)(path[i] + 65);
		cout << num;
	}
	num = (char)(path[0] + 65);	//print the first vertex again  to show the complete cycle
	cout << num << endl;
}

int main()
{
	int point = 0, line = 0, start = 0, U = 0, L = 0;
	char st, up, left;
	cin >> point >> line >> st;
	start = int(st) - 65;
	bool** data;
	data = new bool* [point];
	for (int i = 0; i < point; i++)
		data[i] = new bool[point];
	for (int i = 0; i < point; i++)
		for (int j = 0; j < point; j++)
			data[i][j] = 0;
	while (line > 0)
	{
		cin >> up >> left;
		U = int(up) - 65;
		L = int(left) - 65;
		data[U][L] = 1;
		data[L][U] = 1;
		line--;
	}
	hamCycle(data, point, start);

	for (int i = 0; i < point; i++)
		delete[] data[i];
	delete[] data;
	return 0;
}