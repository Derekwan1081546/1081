#include <iostream>
#include <fstream>
#include <vector>
using namespace::std;

struct MemberRecord
{
	char IDNumber[12];   // account number
	char password[24];   // password
	char name[8];        // name
};

// input memberDetails from the file Members.dat
void loadMemberDetails(vector< MemberRecord >& memberDetails);

// input an integer in the range [ begin, end ]
int inputAnInteger(int begin, int end);

// login
void login(const vector< MemberRecord >& memberDetails);

// there exists a member with specified IDNumber and password
bool valid(char IDNumber[], char password[],
	const vector< MemberRecord >& memberDetails);

// add a new member
void registration(vector< MemberRecord >& memberDetails);

// return true if IDNumber is a legal ID number
bool legalID(char IDNumber[]);

// return true if IDNumber belongs to memberDetails
bool existingID(char IDNumber[], const vector< MemberRecord >& memberDetails);

// output all memberDetails into the file Members.dat
void saveMemberDetails(const vector< MemberRecord >& memberDetails);

int main()
{
	vector< MemberRecord > memberDetails = {}; // member details for all members
	int numMembers = 0;                     // number of members

	loadMemberDetails(memberDetails);

	cout << "Welcome to the Cashbox Party World!\n\n";

	int choice;

	while (true)
	{
		cout << "1 - Login\n";
		cout << "2 - Registration\n";
		cout << "3 - End\n";

		do cout << "\nEnter your choice (1~3): ";
		while ((choice = inputAnInteger(1, 3)) == -1);
		cout << endl;

		switch (choice)
		{
		case 1:
			login(memberDetails);
			break;

		case 2:
			registration(memberDetails);
			break;

		case 3:
			saveMemberDetails(memberDetails);
			cout << "Thank you! Goodbye!\n\n";
			system("pause");
			return 0;

		default:
			cout << "\nIncorrect choice!\n";
			break;
		}
	}

	system("pause");
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

// input an integer in the range [ begin, end ]
int inputAnInteger(int begin, int end)
{
	char num;
	cin >> num;
	if ('1' <= num && num <= '3')
		return(num - '0');
	return -1;
}

// login
void login(const vector< MemberRecord >& memberDetails)
{
	char id[12], password[24];
	int i = 0;
	while (i == 0)
	{
		cout << "Please enter your ID number:";
		cin >> id;
		cout << "Enter your password: ";
		cin >> password;
		if (!valid(id, password, memberDetails))
			cout << endl << "Invalid account number or password. Please try again." << endl << endl;
		else
			i++;
	}
}

// there exists a member with specified IDNumber and password
bool valid(char IDNumber[], char password[], const vector< MemberRecord >& memberDetails)
{
	for (int i = 0; i < memberDetails.size(); i++)
	{
		if (strcmp(IDNumber, memberDetails[i].IDNumber) == 0 && strcmp(password, memberDetails[i].password) == 0)
			return true;
	}
	return false;
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
	int num = 0;
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

	num += IDNumber[9] - '0';
	if (num % 10 == 0)
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