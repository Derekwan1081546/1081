//calculate charges for each customers
#include <iostream> //std::cout,fixed,lrft .right
#include <iomanip>  // std::setprecision,setw

using namespace std;
double hours, charge;

double calculatecharge(double hours)//use function to calculate charge per hour and define the range of hour
{
	if (hours <0)
	{
		cout <<"error";
	}
	else if (hours < 2)
	{
		charge = 3.00;
	}
	else if (hours > 24)
	{
		cout << "There are no cars park for longer than 24 hours at a time.";
	}
	else if (hours >20)
	{
		charge = 15.00;
	}
	else if (hours>2)
	{
		charge = 3 + (hours-2) * 0.6;
	}
	
	
	return charge;//return to main function
}

int main(int argc, const char* argv[])
{
	double TOTAL;//declare total
	double hr[3];//use array to declare parking hours
	cin >> hr[0] >> hr[1] >> hr[2];//input hours

	cout << "Car" << setw(10) << right << "Hours" << setw(12) << right << "Charge" <<endl;
	cout << fixed;
	for (int i= 0; i <= 2; i++)
	{
		
		cout << i + 1 << setw(12) << right << setprecision(1) << hr[i] << setw(12) << right << setprecision(2) << calculatecharge(hr[i]) << endl;
		TOTAL += calculatecharge(hr[i]);//total=the sum of parking charge
	}
	cout << "TOTAL" << setw(8) << right << hr[0] + hr[1] + hr[2] << setw(12) << right << TOTAL;//output the total and the sum of hours
	
	return 0;
}
