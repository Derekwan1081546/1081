#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
using namespace std;

int adultTicketPrice[ 13 ][ 13 ] = {
   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   0,    0,    0,    0,  500,  700,  920, 1330, 1510, 1660, 1880, 2290, 2500,
   0,   40,    0,    0,  440,  640,  850, 1250, 1430, 1600, 1820, 2230, 2440,
   0,   70,   40,    0,  400,  590,  800, 1210, 1390, 1550, 1780, 2180, 2390,
   0,  200,  160,  130,    0,  400,  620, 1010, 1210, 1370, 1580, 1990, 2200,
   0,  330,  290,  260,  130,    0,  410,  820, 1010, 1160, 1390, 1790, 2000,
   0,  480,  430,  400,  280,  140,    0,  610,  790,  950, 1160, 1580, 1790,
   0,  750,  700,  670,  540,  410,  270,    0,  400,  550,  770, 1180, 1390,
   0,  870,  820,  790,  670,  540,  390,  130,    0,  370,  580, 1000, 1210,
   0,  970,  930,  900,  780,  640,  500,  230,  110,    0,  430,  830, 1040,
   0, 1120, 1080, 1050,  920,  790,  640,  380,  250,  150,    0,  620,  820,
   0, 1390, 1350, 1320, 1190, 1060,  920,  650,  530,  420,  280,    0,  410,
   0, 1530, 1490, 1460, 1330, 1200, 1060,  790,  670,  560,  410,  140,    0 };

char departureTimes[ 37 ][ 8 ] = { "",
   "06:00", "06:30", "07:00", "07:30", "08:00", "08:30", "09:00", "09:30",
   "10:00", "10:30", "11:00", "11:30", "12:00", "12:30", "13:00", "13:30",
   "14:00", "14:30", "15:00", "15:30", "16:00", "16:30", "17:00", "17:30",
   "18:00", "18:30", "19:00", "19:30", "20:00", "20:30", "21:00", "21:30",
   "22:00", "22:30", "23:00", "23:30" };

char stationName[13][12] = { "" ,"Nangang","Taipei","Banqiao","Taoyuan","Hsinchu","Miaoli","Taichung","Changhua","Yunlin","Chiayi","Tainan","Zuoying" };//add

struct Reservation
{
   char reservationNumber[ 12 ]; // used to identify a reservation
   char trainNumber[ 8 ];  // used to identify a train
   char idNumber[ 12 ];    // the id number of the contact person
   char phone[ 12 ];       // the (local or mobile) phone number of the contact person
   char date[ 12 ];        // outbound date
   int originStation;      // the origin station code
   int destinationStation; // the destination station code
   int carClass;           // the car class code; 1:standard car, 2:business car
   int adultTickets;       // the number of adult tickets
   int concessionTickets;  // the number of concession tickets
};

struct Train
{
   char trainNumber[ 8 ];          // used to identify a train
   char departureTimes[ 13 ][ 8 ]; // the departure time of a train for each station,
};                                 // departureTimes[0] is not used

// input an integer in the range [ begin, end ]
int inputAnInteger( int begin, int end );

void makingReservation( Train southboundTimetable[ 100 ], Train northboundTimetable[ 100 ] );

// inputs originStation, destinationStation, carClass,
// date, departureTime, adultTickets and concessionTickets
void inputReservationDetails( Reservation &reservation, int &departureTime );

// loads the southbound timetable from the file "Southbound timetable.dat"
void loadSouthboundTimetable( Train southboundTimetable[ 100 ], int &numSouthboundTrains );

// loads the northbound timetable from the file "Northbound timetable.dat"
void loadNorthboundTimetable( Train northboundTimetable[ 100 ], int &numNorthboundTrains );

// displays timetables for 10 coming southbound trains, then let user select one
void selectSouthboundTrain( Train southboundTimetable[ 100 ], int numSouthboundTrains,
                            Reservation &reservation, int departureTime );

// displays timetables for 10 coming northbound trains, then let user select one
void selectNorthboundTrain( Train northboundTimetable[ 100 ], int numNorthboundTrains,
                            Reservation &reservation, int departureTime );

// inputs idNumber and phone, and randomly generate reservationNumber
void inputContactInfo( Reservation &reservation );

// save reservation to the end of the file Reservation details.dat
void saveReservation( Reservation reservation );

void reservationHistory( Train southboundTimetable[ 100 ],
                         Train northboundTimetable[ 100 ] );

// inputs idNumber and reservationNumber, and
// checks if the corresponding reservation exists
bool existReservation( fstream &ioFile, Reservation &reservation );


void displayReservations( Train southboundTimetable[ 100 ],
                          Train northboundTimetable[ 100 ], Reservation reservation );

// displays date, originStation, destinationStation, departureTime, arrival time,
// fare for adultTickets, fare for concessionTickets and total fare
void display( Reservation reservation, Train trainTimetable[ 100 ],
              char stations[ 13 ][ 12 ], char carClass[ 12 ] );

// reduces adultTickets and/or concessionTickets in reservation
void reduceSeats( fstream &ioFile, Train southboundTimetable[ 100 ],
                  Train northboundTimetable[ 100 ], Reservation &reservation );

int main()
{
   cout << "Taiwan High Speed Rail Booking System\n";
   srand( static_cast< unsigned int >( time( 0 ) ) );

   Train southboundTimetable[ 100 ];
   Train northboundTimetable[ 100 ];
   int choice; // store user choice

   // enable user to specify action
   while( true )
   {
      cout << "\nEnter Your Choice\n"
         << "1. Booking\n"
         << "2. Booking History\n"
         << "3. End Program";

      do cout << "\n? ";
      while( ( choice = inputAnInteger( 1, 3 ) ) == -1 );
      cout << endl;

      switch( choice )
      {
      case 1:
         makingReservation( southboundTimetable, northboundTimetable );
         break;
      case 2:
         reservationHistory( southboundTimetable, northboundTimetable );
         break;
      case 3:
         cout << "Thank you! Goodbye!\n\n";
         system( "pause" );
         return 0;
      default: // display error if user does not select valid choice
         cerr << "Incorrect Choice!\n";
         break;
      }
   }

   system( "pause" );
} // end main

// input an integer in the range [ begin, end ]
int inputAnInteger(int begin, int end)
{

	char num[100];
	cin >> num;
	int j = -1;
	for (int i = 0; num[i]!=0 && i < 3; i++)
	{
		if ('0' > num[i] && num[i] > '9')
		{
			return-1;
		}
		j++;
	}
	if (j + 1 > 2)
		return 0;

	if (j == 0)
	{
		int number = num[0] - '0';
		if (begin <= number && number <= end)
			return number;
		return-1;
	}
	else
	{
		int number = (num[0] - '0') * 10 + num[1] - '0';
		if (begin <= number && number <= end)
		{
			return number;
		}
		return -1;
	}
}

void makingReservation(Train southboundTimetable[100], Train northboundTimetable[100])
{
	Reservation Reservation;
	char carclass[3][12] = { "","Standard","bussness" };//add
	int departureTime;
	loadSouthboundTimetable(southboundTimetable, departureTime);
	loadNorthboundTimetable(northboundTimetable, departureTime);
	inputReservationDetails(Reservation, departureTime);
	if (Reservation.originStation < Reservation.destinationStation)
	{
		selectSouthboundTrain(southboundTimetable, Reservation.originStation, Reservation, departureTime);
		display(Reservation,southboundTimetable, stationName, carclass[Reservation.carClass]);//add
	}
	else if (Reservation.originStation > Reservation.destinationStation)
	{
		selectNorthboundTrain(northboundTimetable, Reservation.originStation, Reservation, departureTime);
		display(Reservation, northboundTimetable, stationName, carclass[Reservation.carClass]);//add
	}
	inputContactInfo(Reservation);
	saveReservation(Reservation);
	return;
}

// inputs originStation, destinationStation, carClass,
// date, departureTime, adultTickets and concessionTickets
void inputReservationDetails(Reservation& reservation, int& departureTime)
{
	Reservation Reservation;
	int choice;
	cout << "Origin Station " << endl;
	cout << "1. Nangang\n";
	cout << "2. Taipei\n";
	cout << "3. Banqiao\n";
	cout << "4. Taoyuan\n";
	cout << "5. Hsinchu\n";
	cout << "6. Miaoli\n";
	cout << "7. Taichung\n";
	cout << "8. Changhua\n";
	cout << "9. Yunlin\n";
	cout << "10. Chiayi\n";
	cout << "11. Tainan\n";
	cout << "12. Zuoying\n";
	do cout << "? ";
	while ((choice = inputAnInteger(1, 12)) == -1);
	Reservation.originStation = choice;
	cout << "Destination Station\n";
	cout << "1. Nangang\n";
	cout << "2. Taipei\n";
	cout << "3. Banqiao\n";
	cout << "4. Taoyuan\n";
	cout << "5. Hsinchu\n";
	cout << "6. Miaoli\n";
	cout << "7. Taichung\n";
	cout << "8. Changhua\n";
	cout << "9. Yunlin\n";
	cout << "10. Chiayi\n";
	cout << "11. Tainan\n";
	cout << "12. Zuoying\n";
	do cout << "? ";
	while ((choice = inputAnInteger(1, 12)) == -1);
	Reservation.destinationStation = choice;
	if (Reservation.originStation == Reservation.destinationStation)
	{
		inputReservationDetails(reservation, departureTime);
		return;
	}
	cout << "Car Class\n";
	cout << "1. Standard Car\n";
	cout << "2. Business Car\n";
	do cout << "? ";
	while ((choice = inputAnInteger(1, 2)) == -1);
	Reservation.carClass = choice;
	cout << "Departure Date:";
	cin >> Reservation.date;
	cout << "Departure Time\n";
	for (int i = 1; i < 35; i++) //add
		cout << setw(2) << right <<i << ". " << departureTimes[i] << endl;//modify
	do cout << "? ";
	while ((choice = inputAnInteger(1, 36)) == -1);
	departureTime = choice ;
	do cout << "How many adult tickets?";
	while ((choice = inputAnInteger(0, 99)) == -1);
	Reservation.adultTickets = choice;
	do cout << "How many concession tickets?";
	while ((choice = inputAnInteger(0, 99)) == -1);
	Reservation.concessionTickets = choice;
	reservation = Reservation;//add
}

// loads the southbound timetable from the file "Southbound timetable.dat"
void loadSouthboundTimetable(Train southboundTimetable[100], int& numSouthboundTrains)
{
	fstream infile("Southbound timetable.txt", ios::in);//modify
	infile.seekg(0, ios::end); 
	int numline = infile.tellg() / sizeof(Train); 
	infile.seekg(0, ios::beg);

	for (int i = 0; i < numline; i++)//modify
	{
		infile.getline(reinterpret_cast<char*>(&southboundTimetable[i].trainNumber),8, '\t');//add
		for (int j = 1; j < 13; j++) {//add
			if(j==12)//add
				infile.getline(reinterpret_cast<char*>(&southboundTimetable[i].departureTimes[j]),8, '\n');//add
			else//add
				infile.getline(reinterpret_cast<char*>(&southboundTimetable[i].departureTimes[j]),8, '\t');//add
		}
		//infile.write(reinterpret_cast<char*>(&southboundTimetable[i]), sizeof(Train)); delete
	}
	infile.close();
}

// loads the northbound timetable from the file "Northbound timetable.dat"
void loadNorthboundTimetable(Train northboundTimetable[100], int& numNorthboundTrains)
{
	fstream input("Northbound timetable.txt", ios::in | ios::out | ios::binary);
	input.seekg(0, ios::end);
	int numline = input.tellg() / sizeof(Train);
	input.seekg(0, ios::beg);
	for (int i = 0; i < numline; i++)//modify
	{
		input.getline(reinterpret_cast<char*>(&northboundTimetable[i].trainNumber),8, '\t');//add
		for (int j = 1; j < 13; j++) {//add
			if (j == 12)//add
				input.getline(reinterpret_cast<char*>(&northboundTimetable[i].departureTimes[j]),8, '\n');//add
			else//add
				input.getline(reinterpret_cast<char*>(&northboundTimetable[i].departureTimes[j]),8, '\t');//add
		}
		//infile.write(reinterpret_cast<char*>(&northboundTimetable[i]), sizeof(Train)); delete
	}
	input.close();
}

// displays timetables for 10 coming southbound trains, then let user select one
void selectSouthboundTrain(Train southboundTimetable[100], int numSouthboundTrains,
	Reservation& reservation, int departureTime)
{
	Train train[10];
	int k = 0;
	cout <<setw(9)<<right<< "Train No." << setw(11) << right << "Departure" << setw(10) << right << " Arrival " << endl;
	for (int i = 0; i < 100; i++) { //add
		if (strcmp(southboundTimetable[i].departureTimes[reservation.originStation], departureTimes[departureTime]) == 1) {//add
			for (int j = i; j < i + 10; j++) {//add
				train[k] = southboundTimetable[j];//add
				k++;//add
			}
			break;//add
		}
	}
	for (int i = 0; i < 10; i++)
	{	
		cout << setw(9) << right << train[i].trainNumber << setw(11) << right << train[i].departureTimes[reservation.originStation] << setw(9) << right << train[i].departureTimes[reservation.destinationStation] << endl;//modify
	}
	bool same = 0;//add
	do {//add
		cout << "\nEnter Train Number: ";
		cin >> reservation.trainNumber;//add
		for (int i = 0; i < 10; i++) {//add
			if (strcmp(reservation.trainNumber, train[i].trainNumber) == 0) {//add
				same = 1;//add
				break;//add
			}
		}
	} while (!same);//add
}

// displays timetables for 10 coming northbound trains, then let user select one
void selectNorthboundTrain(Train northboundTimetable[100], int numNorthboundTrains,
	Reservation& reservation, int departureTime) 
{
	Train train[10];
	int k = 0;
	cout <<setw(9)<<right<< "Train No." << setw(11) << right << "Departure" << setw(10) << right << " Arrival " << endl;
	for (int i = 0; i < 100; i++) { //add
		if (strcmp(northboundTimetable[i].departureTimes[(reservation.originStation-13)*-1], departureTimes[(departureTime-13)*-1]) == 1) {//add
			for (int j = i; j < i + 10; j++) {//add
				train[k] = northboundTimetable[j];//add
				k++;//add
			}
			break;
		}
	}
	for (int i = 0; i < 10; i++)
	{
		cout << setw(9) << right << train[i].trainNumber << setw(11) << right << train[i].departureTimes[reservation.originStation] << setw(9) << right << train[i].departureTimes[reservation.destinationStation] << endl;//modify
	}
	bool same = 0;//add
	do {//add
		cout << "\nEnter Train Number: ";//add
		cin >> reservation.trainNumber;//add
		for (int i = 0; i < 10; i++) {//add
			if (strcmp(reservation.trainNumber, train[i].trainNumber) == 0) {//add
				same = 1;//add
				break;//add
			}
		}
	} while (!same);//add
}

// inputs idNumber and phone, and randomly generate reservationNumber
void inputContactInfo(Reservation& reservation)
{
	Reservation Reservation;

	cout << "Enter Contact Person Information\n";
	cout << "ID Number: ";
	cin >> reservation.idNumber;//modify
	cout << "Phone: ";
	cin >> reservation.phone;//modify
	cout << "Reservation Number: ";
	srand(static_cast<unsigned int>(time(0)));
	char number[10]{};
	for (int i = 0; i < 8; i++)
	{
		reservation.reservationNumber[i] = '0' + rand() % 10;//modify
	}
	reservation.reservationNumber[8] = '\0';//modify
	cout << reservation.reservationNumber;//modify
	cout << "\nReservation Completed!";
	cout << endl << endl;

}

// save reservation to the end of the file Reservation details.dat
void saveReservation(Reservation reservation)
{
	fstream save("Reservation details.dat", ios::in | ios::out | ios::binary);
	if (!save) {
		ofstream save("Reservation details.dat", ios::out | ios::binary);
		save.write(reinterpret_cast<char*>(&reservation), sizeof(reservation));
		return;
	}
	save.seekg(0, ios::end);
	int numline = save.tellg() / sizeof(Train);
	save.seekg(0, ios::beg);
	Reservation Reservations;
	for (int i = 0; i < numline; i++)
	{
		save.read(reinterpret_cast<char*>(&Reservations), sizeof (Reservations));
		if (strcmp(reservation.reservationNumber, Reservations.reservationNumber) == 0 && strcmp(reservation.idNumber, Reservations.idNumber) == 0) {//add
			save.seekp(i * sizeof(Reservation), ios::beg);//add
			save.write(reinterpret_cast<char*>(&reservation), sizeof(reservation));//add
			return;//add
		}//add
	}
	save.close();
	fstream save2("Reservation details.dat", ios::in | ios::out | ios::binary);
	//for (int i = 0; i < numline; i++) delete

	save.seekg(0, ios::end);//add
	save2.write(reinterpret_cast<char*>(&reservation), sizeof(reservation));

	save2.close();
}

void reservationHistory(Train southboundTimetable[100],
	Train northboundTimetable[100])
{
	fstream infile("Reservation details.dat", ios::in | ios::out | ios::binary);
	Reservation Reservations;
	int choice;
	bool exist = 0;
	do {
		if (existReservation(infile, Reservations))
		{
			displayReservations(southboundTimetable, northboundTimetable, Reservations);
			exist = 1;
		}
	} while (!exist);
	do {//add
		cout << "Enter Your Choice\n";
		cout << "1. Cancellation\n";
		cout << "2. Reduce\n";
		cout << "3. End\n";
		do cout << "?";
		while ((choice = inputAnInteger(1, 3)) == -1);
		cout << endl;
		switch (choice)
		{
		case 1: 
			break;//modify
		case 2:
			reduceSeats(infile, southboundTimetable, northboundTimetable, Reservations);
			break;
		case 3:
			return;
		default: // display error if user does not select valid choice
			cerr << "Incorrect Choice!\n";
			break;
		}
		if (Reservations.adultTickets <= 0 && Reservations.concessionTickets <= 0) {//add
			choice = 1;//add
		}//add
	} while (choice == 2);//add
		infile.seekg(0, ios::beg);//add
		Reservation zero = {};//add
		int cancel = 0;//add
		while (!infile.eof()) {//add
			Reservation reservation;//add
			infile.read(reinterpret_cast<char*>(&reservation), sizeof(reservation));//add
			if (strcmp(reservation.idNumber, Reservations.idNumber) == 0//add
				&& strcmp(reservation.reservationNumber, Reservations.reservationNumber) == 0) {//add
				cancel = infile.tellg() / sizeof(Reservation);//add
				break;//add
			}
		}
		infile.seekp((cancel - 1) * sizeof(Reservation), ios::beg);//add
		infile.write(reinterpret_cast<const char*>(&zero), sizeof(zero));//add
		cout << "Reservation Cancelled!";
}

// inputs idNumber and reservationNumber, and
// checks if the corresponding reservation exists
bool existReservation(fstream& ioFile, Reservation& reservation)
{
	Reservation Reservation;
	char idNumber[10], ReservationNumber[10];
	cout << "Enter ID Number:";
	cin >> reservation.idNumber;//modify
	cout << "Enter Reservation Number: ";
	cin >> reservation.reservationNumber;//modify
	for (int i = 0; i < 10; i++)
	{
		ioFile.read(reinterpret_cast<char*>(&Reservation), sizeof(Reservation));//add
		if (strcmp(Reservation.idNumber, reservation.idNumber) == 0 && strcmp(Reservation.reservationNumber, reservation.reservationNumber) == 0)//modify
		{
			reservation = Reservation;//add
			return true;
		}
	}
	return false;
}

void displayReservations(Train southboundTimetable[100],
	Train northboundTimetable[100], Reservation reservation)
{
	int departureTime;
	loadSouthboundTimetable(southboundTimetable, departureTime);
	loadNorthboundTimetable(northboundTimetable, departureTime);
	char stations[13][12], carClass[3][12] = { "","standard","bussness" };
	cout << "Reservation Details " << endl;
	if (reservation.originStation < reservation.destinationStation)//add
	{
		display(reservation, southboundTimetable, stations, carClass[reservation.carClass]);
	}
	else display(reservation, northboundTimetable, stations, carClass[reservation.carClass]);//add
}

// displays date, originStation, destinationStation, departureTime, arrival time,
// fare for adultTickets, fare for concessionTickets and total fare
void display(Reservation reservation, Train trainTimetable[100],
	char stations[13][12], char carClass[12])
{
	Train train;
	int price;
	if (reservation.carClass == 1) {
		price = adultTicketPrice[reservation.destinationStation][reservation.originStation];//add
	}
	else price = adultTicketPrice[reservation.originStation][reservation.destinationStation];//add
	for (int i = 0; i < 100; i++) {
		if (strcmp(reservation.trainNumber, trainTimetable[i].trainNumber) == 0) {
			train = trainTimetable[i];
		}
	}
	cout << setw(10) << right << "Date  Train" << setw(11) << right << "No." << setw(8) << right << "From" << setw(10) << right << "To" << setw(11) << right << "Departure " << setw(9) << right << "Arrival" << setw(8) << right << "Adult" << setw(12) << right << "Concession" << setw(6) << right << "Fare" << setw(11) << right << "Class" << endl;
	cout << setw(11) << right << reservation.date << setw(11) << right << reservation.trainNumber << setw(8) << right <<stationName[reservation.originStation] << setw(10) << right << stationName[reservation.destinationStation] << setw(11) << right << train.departureTimes[reservation.originStation] << setw(9) << right <<train.departureTimes[reservation.destinationStation]<<setw(6)<<right<< price<<"*"<< reservation.adultTickets << setw(10) << right << price/2<< "*"<< reservation.concessionTickets << setw(6) << right << (price * reservation.adultTickets) + (price/2 * reservation.concessionTickets) << setw(11) << right << carClass << endl << endl;
}

// reduces adultTickets and/or concessionTickets in reservation
void reduceSeats(fstream& ioFile, Train southboundTimetable[100],
	Train northboundTimetable[100], Reservation& reservation)
{
	int choice1,choice2;
	do cout << "How many adult tickets to cancel¡H";
	while ((choice1 = inputAnInteger(0, 99)) == -1);
	do cout << "How many concession tickets to cancel¡H";
	while ((choice2 = inputAnInteger(0, 99)) == -1);
	if (choice1 == 0 && choice2 == 0)
	{
		return;
	}
	else
	{
		reservation.adultTickets -= choice1;//modify
		reservation.concessionTickets -= choice2;//modify
	}
	displayReservations(southboundTimetable, northboundTimetable, reservation);
	saveReservation(reservation);//add
	cout << "You have successfully reduced the number of tickets!" << endl << endl << endl;
}