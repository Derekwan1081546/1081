#include<iostream>
using namespace std;
int main()
{
	int n1, n2, n3, n4;
	int x1, x2, x3, x4;//input the daily sales of pencils and ballpoint pens
	cout << "Please input the daily sales of pencils for the first four days( use a space to separate each character ): " << endl;
	cin >> n1 >> n2 >> n3 >> n4;
	cout << "Plese input the daily sales of ballpoint pens for the first four days( use a space to separate each character ): " << endl;
	cin >> x1 >> x2 >> x3 >> x4;
	int sum1 = n1 + x1;//calculating the sum of sales repectively
	int sum2 = n2 + x2;
	int sum3 = n3 + x3;
	int sum4 = n4 + x4;
	int sum[4] = { sum1,sum2,sum3,sum4 };//using array to run the loop
	int x[4] = { x1,x2,x3,x4 };
	if (n1<0||n1>5||n2<0||n2>5||n3<0||n3>5||n4<0||n4>5||x1<0||x1>5||x2<0||x2>5||x3<0||x3>5||x4<0||x4>5) //check if the total should must be in the range of 0~5
	{
		cout <<"error";
		return 0;
	}
	else if(sum1>5||sum2>5||sum3>5||sum4>5)
	{
		cout <<"error";
		return 0;
	}
	for (int level = 5; level > 0; level--)//using for ioop to finish the bar graph
	{
		for (int i = 0; i <= 3; i++)
		{			
			if (sum[i] >= level &&sum[i]<=5)
			{
				if (x[i] < level)
					cout << "* ";
				else
					cout << "+ ";
			}
			else
				cout << "  ";
		}
		cout << endl;



	}
	cout << "1" << " " << "2" << " " << "3" << " " << "4" <<endl;
	
	
	return 0;
}
