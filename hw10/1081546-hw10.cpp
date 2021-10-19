#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <ctime>
using namespace::std;

struct Date
{
   int year;
   int month;
   int day;
   int hour;
};

struct MemberRecord
{
   char IDNumber[ 12 ];   // account number
   char password[ 24 ];   // password
   char name[ 8 ];        // name
};

struct ReservationRecord
{
   char IDNumber[ 12 ]; // account number
   int branchCode;      // branch code
   Date date;           // reservation date
   int numCustomers;    // number of customers
};

char branchNames[ 17 ][ 24 ] = { "", "Taipei Dunhua South", "Taipei SOGO",
                                     "Taipei Songjiang",    "Taipei Nanjing",
                                     "Taipei Linsen",       "Taipei Zhonghua New",
                                     "Banqiao Guanqian",    "Yonghe Lehua",
                                     "Taoyuan Zhonghua",    "Taoyuan Nankan",
                                     "Zhongli Zhongyang",   "Hsinchu Beida",
                                     "Taichung Ziyou",      "Chiayi Ren'ai",
                                     "Tainan Ximen",        "Kaohsiung Zhonghua New" };

// input memberDetails from the file Members.dat
void loadMemberDetails( vector< MemberRecord > &memberDetails );

// input reservations from the file Reservations.dat
void loadReservations( vector< ReservationRecord > &reservations );

// input an integer in the range [ begin, end ]
int inputAnInteger( int begin, int end );

// login and display the submenu
void login( const vector< MemberRecord > &memberDetails,
            vector< ReservationRecord > &reservations );

// there exists a member with specified IDNumber and password
bool valid( char IDNumber[], char password[],
            const vector< MemberRecord > &memberDetails );

// add a new reservation for the member with specified IDnumber
void reservation( char IDNumber[], vector< ReservationRecord > &reservations );

// compute the current date
void compCurrentDate( Date &currentDate );

// compute 7 dates which is starting from the current date
void compAvailableDates( Date currentDate, Date availableDates[] );

// display all fields of reservation
void output( ReservationRecord reservation );

// display all reservations for the member with specified IDnumber,
// then let the member to choose one of them to delete
void queryDelete( char IDNumber[], vector< ReservationRecord > &reservations );

// add a new member
void registration( vector< MemberRecord > &memberDetails );

// return true if IDNumber is a legal ID number
bool legalID( char IDNumber[] );

// return true if IDNumber belongs to memberDetails
bool existingID( char IDNumber[], const vector< MemberRecord > &memberDetails );

// output all memberDetails into the file Members.dat
void saveMemberDetails( const vector< MemberRecord > &memberDetails );

// output all reservations into the file Reservations.dat
void saveReservations( const vector< ReservationRecord > &reservations );

int main()
{
   vector< MemberRecord > memberDetails; // member details for all members
   vector< ReservationRecord > reservations; // all reservations

   loadMemberDetails( memberDetails );
   loadReservations( reservations );

   cout << "Welcome to the Cashbox Party World!\n\n";

   int choice;

   while( true )
   {
      cout << "1 - Login\n";
      cout << "2 - Registration\n";
      cout << "3 - End\n";

      do cout << "\nEnter your choice (1~3): ";
      while( ( choice = inputAnInteger( 1, 3 ) ) == -1 );
      cout << endl;

      switch ( choice )
      {
      case 1:
         login( memberDetails, reservations );
         break;

      case 2:
         registration( memberDetails );
         break;

      case 3:
         saveMemberDetails( memberDetails );
         saveReservations( reservations );
         cout << "Thank you! Goodbye!\n\n";
         system( "pause" );
         return 0;

      default:
         cout << "\nIncorrect choice!\n";
         break;
      }
   }

   system( "pause" );
}

// input memberDetails from the file Members.dat
void loadMemberDetails(vector< MemberRecord >& memberDetails)
{
	ofstream outfile("memberDetails.dat", ios::app | ios::binary);
	ifstream input("memberDetails.dat", ios::binary);

	MemberRecord buf;

	while (input && !input.eof())
	{
		input.read(reinterpret_cast<char*>(&buf), sizeof(MemberRecord));
		memberDetails.push_back(buf);
	}
}


// input reservations from the file Reservations.dat
void loadReservations(vector< ReservationRecord >& reservations)
{
	ofstream outfile("reservations.dat", ios::app | ios::binary);
	ifstream input("reservations.dat", ios::binary);

	ReservationRecord buf;

	while (input && !input.eof())
	{
		input.read(reinterpret_cast<char*>(&buf), sizeof(ReservationRecord));
		reservations.push_back(buf);
	}
}

// input an integer in the range [ begin, end ]
int inputAnInteger(int begin, int end)
{
	if (end < 10)	//判斷結尾的數字是否為個位數
	{
		char num;
		cin >> num;
		if ('0' <= num && num <= '9')	//判斷輸入的數字是否介於0~9之間
		{
			int n = (num - '0');
			if (begin <= n && n <= end)
				return n;	
		}
		return -1;
	}
	else	//結尾數字為多位數
	{
		char num[100];
		cin >> num;
		int j = -1;
		for (int i = 0; num[i] != 0 && i < 3; i++)	//先判斷第一個數字是否為空字元且小於三位數
		{
			if ('0' > num[i] || num[i] > '9')	//如果輸入數字小於0或大於9就重新輸入
				return -1;
			j++;
		}
		if (j + 1 > 2)	//判斷輸入數字是否小於三位數
			return -1;
		if (j == 0)		//做個位數字的判斷
		{
			int n = (num[0] - '0');
			if (begin <= n && n <= end)
				return n;
			return -1;
		}
		else		//做多位數字的判斷
		{
			int n = (num[0] - '0') * 10 + (num[1] - '0');
			if (begin <= n && n <= end)
				return n;
			return -1;
		}
	}
}

// login and display the submenu
void login(const vector< MemberRecord >& memberDetails,
	vector< ReservationRecord >& reservations)
{
	char id[12], password[24];
	int choice = 0;
	while (choice == 0)
	{
		cout << "Please enter your ID number:";
		cin >> id;
		cout << "Enter your password: ";
		cin >> password;
		if (!valid(id, password, memberDetails))
			cout << endl << "Invalid account number or password. Please try again." << endl << endl;
		else
			choice++;
	}
	while (true)
	{
		cout << "1 - Make Reservation\n";
		cout << "2 - Reservation Enquiry/Canceling\n";
		cout << "3 - End\n";

		do cout << "\nEnter your choice (1~3): ";
		while ((choice = inputAnInteger(1, 3)) == -1);
		cout << endl;

		switch (choice)
		{
		case 1:
			reservation(id, reservations);
			break;

		case 2:
			queryDelete(id, reservations);
			break;

		case 3:
			return;

		default:
			cout << "\nIncorrect choice!\n";
			break;
		}
	}
}

// there exists a member with specified IDNumber and password
bool valid(char IDNumber[], char password[],
	const vector< MemberRecord >& memberDetails)
{
	for (int i = 0; i < memberDetails.size(); i++)
	{
		if (strcmp(IDNumber, memberDetails[i].IDNumber) == 0 && strcmp(password, memberDetails[i].password) == 0)
			return true;
	}
	return false;

}

// add a new reservation for the member with specified IDnumber
void reservation(char IDNumber[], vector< ReservationRecord >& reservations)
{
	int choice;
	ReservationRecord buf;
	for (int i = 1; i < 10; i++)
		cout << " " << i << ". " << branchNames[i] << endl;
	for (int i = 10; i < 17; i++)
		cout << i << ". " << branchNames[i] << endl;
	do cout << "\nEnter your choice(0 to end): ";
	while ((buf.branchCode = inputAnInteger(0, 16)) == -1);
	cout << endl;
	if (buf.branchCode == 0)
		return;
	compCurrentDate(buf.date);
	cout << "The current hour is " << buf.date.year << "/" << buf.date.month << "/" << buf.date.day << ":" << buf.date.hour << "\n\nAvailable days:\n\n";
	Date days[8];
	compAvailableDates(buf.date, days);
	for (int i = 1; i < 8; i++)
		cout << i << ". " << days[i].year << "/" << days[i].month << "/" << days[i].day << endl;
	do cout << "\nEnter your choice(0 to end): ";
	while ((choice = inputAnInteger(0, 7)) == -1);
	cout << endl;
	if (choice == 0)
		return;
	buf.date = days[choice];
	do cout << "Enter hour(" << buf.date.hour << "~23): ";
	while ((choice = inputAnInteger(buf.date.hour, 23)) == -1);
	cout << endl;
	buf.date.hour = choice;
	do cout << "\nEnter the number of customers (1~30, 0 to end): ";
	while ((buf.numCustomers = inputAnInteger(0, 30)) == -1);
	cout << endl;
	if (buf.numCustomers == 0)
		return;
	for (int i = 0; i < 10; i++)
		buf.IDNumber[i] = IDNumber[i];
	output(buf);
	reservations.push_back(buf);
	cout << endl << "Reservation Completed!" << endl << endl;
}

// compute the current date
void compCurrentDate(Date& currentDate)		//計算目前時間為多少
{
	tm structuredTime;
	time_t rawTime = time(0);
	localtime_s(&structuredTime, &rawTime);

	currentDate.year = structuredTime.tm_year + 1900;
	currentDate.month = structuredTime.tm_mon + 1;
	currentDate.day = structuredTime.tm_mday;
	currentDate.hour = structuredTime.tm_hour;
}

// compute 7 dates which is starting from the current date
void compAvailableDates(Date currentDate, Date availableDates[])
{
	tm structuredTime;
	time_t rawTime = time(0);
	if (currentDate.hour == 23)		//如果目前時間為23時則接下來的時段會是從明天開始
	{
		for (int i = 1; i < 8; i++)
		{
			rawTime += 24 * 60 * 60;
			localtime_s(&structuredTime, &rawTime);
			availableDates[i].year = structuredTime.tm_year + 1900;
			availableDates[i].month = structuredTime.tm_mon + 1;
			availableDates[i].day = structuredTime.tm_mday;
			availableDates[i].hour = 0;
		}
	}
	else
	{
		//先輸出第一天剩餘的時間
		availableDates[1].year = currentDate.year;
		availableDates[1].month = currentDate.month;
		availableDates[1].day = currentDate.day;
		availableDates[1].hour = currentDate.hour + 1;
		for (int i = 2; i < 8; i++)		//在輸出其他天的時間
		{
			rawTime += 24 * 60 * 60;
			localtime_s(&structuredTime, &rawTime);
			availableDates[i].year = structuredTime.tm_year + 1900;
			availableDates[i].month = structuredTime.tm_mon + 1;
			availableDates[i].day = structuredTime.tm_mday;
			availableDates[i].hour = 0;
		}
	}

}

// display all fields of reservation
void output(ReservationRecord reservation)
{
	cout << setw(26) << "Branch" << setw(14) << "Date" << setw(8) << "Hour" << setw(19) << "No of Customers" << endl;
	cout << setw(26) << branchNames[reservation.branchCode] << setw(8) << reservation.date.year << "-" << setw(2) << reservation.date.month << "-" << setw(2) << reservation.date.day << setw(8) << reservation.date.hour << setw(19) << reservation.numCustomers << endl;
}

// display all reservations for the member with specified IDnumber,
// then let the member to choose one of them to delete
void queryDelete(char IDNumber[], vector< ReservationRecord >& reservations)
{
	int choise = -1;
	cout << setw(29) << "Branch" << setw(14) << "Date" << setw(8) << "Hour" << setw(19) << "No of Customers" << endl;
	for (int i = 1; i < reservations.size(); i++)
		cout << i << "." << setw(27) << branchNames[reservations[i].branchCode] << setw(8) << reservations[i].date.year << "-" << setw(2) << reservations[i].date.month << "-" << setw(2) << reservations[i].date.day << setw(8) << reservations[i].date.hour << setw(19) << reservations[i].numCustomers << endl;
	do cout << endl << "Choose a reservation to cancel (0: keep all reservations): ";
	while ((choise = inputAnInteger(0, reservations.size() - 1)) == -1);
	cout << endl;
	if (choise == 0)
		return;
	reservations.erase(reservations.begin() + choise);
}

// add a new member
void registration(vector< MemberRecord >& memberDetails)
{
	MemberRecord buf;
	cout << "Please enter your ID number:";
	cin >> buf.IDNumber;
	if (!legalID(buf.IDNumber))
	{
		cout << endl << "The ID number " << buf.IDNumber << " is illegal." << endl << endl;
		return;
	}
	if (existingID(buf.IDNumber, memberDetails))
	{
		cout << endl << "You are already a member!" << endl << endl;
		return;
	}
	cout << endl << "Input your Name: ";
	cin >> buf.name;
	cout << endl << "Choose a password: ";
	cin >> buf.password;
	memberDetails.push_back(buf);
	cout << endl << "Registration Completed!" << endl << endl;
}

// return true if IDNumber is a legal ID number
bool legalID(char IDNumber[])
{
	if ('1' > IDNumber[1] || IDNumber[1] > '2')
		return false;
	int num = 0;
	if ('a' <= IDNumber[0] && IDNumber[0] <= 'z')
		num = IDNumber[0] - 32;
	if ('A' <= IDNumber[0] && IDNumber[0] <= 'H')
		num = IDNumber[0] - 55;
	if (IDNumber[0] == 'I')
		num = IDNumber[0] - 39;
	if ('J' <= IDNumber[0] && IDNumber[0] <= 'N')
		num = IDNumber[0] - 56;
	if (IDNumber[0] == 'O')
		num = IDNumber[0] - 44;
	if ('P' <= IDNumber[0] && IDNumber[0] <= 'V')
		num = IDNumber[0] - 57;
	if (IDNumber[0] == 'W')
		num = IDNumber[0] - 55;
	if ('X' <= IDNumber[0] && IDNumber[0] <= 'Y')
		num = IDNumber[0] - 58;
	if (IDNumber[0] == 'Z')
		num = IDNumber[0] - 57;
	num = (num / 10) + (num % 10 * 9);
	for (int i = 1; i < 9; i++)
		num += (IDNumber[i] - '0') * (9 - i);

	num = 10 - (num % 10);

	if (num % 10 == IDNumber[9] - '0')
		return true;
	return false;

}

// return true if IDNumber belongs to memberDetails
bool existingID(char IDNumber[], const vector< MemberRecord >& memberDetails)
{
	for (int i = 0; i < memberDetails.size(); i++)
	{
		if (strcmp(IDNumber, memberDetails[i].IDNumber) == 0)
			return true;
	}
	return false;

}

// output all memberDetails into the file Members.dat
void saveMemberDetails(const vector< MemberRecord >& memberDetails)
{
	MemberRecord buf;
	ofstream outfile("memberDetails.dat", ios::binary);
	for (int i = 0; i < memberDetails.size(); i++)
		outfile.write(reinterpret_cast<const char*> (&memberDetails[i]), sizeof(MemberRecord));

}

// output all reservations into the file Reservations.dat
void saveReservations(const vector< ReservationRecord >& reservations)
{
	ReservationRecord buf;
	ofstream outfile("Reservations.dat", ios::binary);
	for (int i = 1; i < reservations.size(); i++)
		outfile.write(reinterpret_cast<const char*> (&reservations[i]), sizeof(MemberRecord));
}