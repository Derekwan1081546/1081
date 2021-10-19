#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <ctime>
using namespace::std;

char foods[ 14 ][ 48 ] = { "",
                           "Pork XiaoLongBao (12)",
                           "Steamed Vegetable and Ground Pork Dumplings (8)",
                           "Steamed Shrimp and Pork Dumplings (8)",
                           "Steamed Fish Dumplings (8)",
                           "Steamed Vegetarian Mushroom Dumplings (8)",
                           "Steamed Shrimp and Pork Shao Mai (12)",
                           "Pork Buns (5)",
                           "Vegetable and Ground Pork Buns (5)",
                           "Red Bean Buns (5)",
                           "Sesame Buns (5)",
                           "Taro Buns (5)",
                           "Vegetarian Mushroom Buns (5)",
                           "Golden Lava Buns (5)" };

int price[ 14 ] = { 0, 220, 176, 216, 200, 200, 432, 225,
                       225, 200, 200, 225, 250, 225 };

struct Date
{
   int year;
   int month;
   int day;
};

struct Account
{
   char email[ 40 ]; // used as the account number
   char password[ 20 ];
   char name[ 12 ];
   char address[ 80 ];
   char phone[ 12 ];
   int cart[ 14 ]; // Cart[i] is the quantity of food #i in the shopping cart
};

struct Order
{
   char orderNumber[ 12 ];
   char email[ 40 ];
   Date deliveryDate;
   Date arrivalDate;
   int quantity[ 14 ]; // quantity[i] is the quantity of food #i in the order
};

// input an integer in the range [ begin, end ]
int inputAnInteger( int begin, int end );

// add a new account to the file Accounts.dat
void registration( vector< Account > &accountDetails );

// return true if email belongs to accountDetails
bool exists( char email[], const vector< Account > &accountDetails );

// save all elements in accountDetails to the file Accounts.dat
void saveAllAccounts( const vector< Account > &accountDetails );

// login and call shopping
void login( vector< Account > &accountDetails );

// load all accounts details from the file Accounts.dat
void loadAccountDetails( vector< Account > &accountDetails );

// return true if there exists an account with specified email and password; and
// put the account with specified email and password into account
bool valid( char email[], char password[], Account &account,
            const vector< Account > &accountDetails );

// add chosen Foods to the shopping cart
void shopping( Account &account );

// return true if the shopping cart is empty
bool emptyCart( const Account &account );

// display the shopping cart in account
bool displayCart( const Account &account );

// append account in the file Accounts.dat
void saveAccount( const Account &account );

// update the shopping cart in account
void updateCart( Account &account );

// generate a Bill and reset account.cart
void check( Account &account );

// compute the current date
void compCurrentDate( Date &currentDate );

// open the file Orders.txt and call displayOrderDetails twice
void createOrder( const Account &account, const Order &order );

// write an order to Orders.txt or display it on the output window depending on os
void displayOrderDetails( ostream &os, const Account &account, const Order &order );

int main()
{
   vector< Account > accountDetails; // account details for all accounts

   cout << "Welcome to DintaiFung Shopping Mall!\n";
   srand( static_cast< int >( time( 0 ) ) );

   int choice;

   while( true )
   {
      cout << "\n1 - Registration\n";
      cout << "2 - Login\n";
      cout << "3 - End\n";

      do cout << "\nEnter your choice (1~3): ";
      while( ( choice = inputAnInteger( 1, 3 ) ) == -1 );
      cout << endl;

      switch( choice )
      {
      case 1:
         registration( accountDetails );
         break;

      case 2:
         login( accountDetails );
         break;

      case 3:
         cout << "Thank you! Goodbye!\n\n";
         system( "pause" );
         return 0;
      }
   }

   system( "pause" );
}

// input an integer in the range [ begin, end ]
int inputAnInteger(int begin, int end)
{
    char num[100];
    cin >> num;
    int j = -1;
    for (int i = 0; num[i] != 0 && i < 3; i++)
    {
        if ('0' > num[i] || num[i] > '9')
            return -1;
        j++;
    }
    if (j + 1 > 2)
        return -1;
    if (j == 0)
    {
        int n = (num[0] - '0');
        if (begin <= n && n <= end)
            return n;
        return -1;
    }
    else
    {
        int n = (num[0] - '0') * 10 + (num[1] - '0');
        if (begin <= n && n <= end)
            return n;
        return -1;
    }
}

// add a new account to the file Accounts.dat
void registration(vector< Account >& accountDetails)
{
    loadAccountDetails(accountDetails);
    Account buffer;
    for (int i = 0; i < 14; i++) {
        buffer.cart[i] = 0;
    }
    cout << "Email address (Account number): ";
    cin >> buffer.email;
    if (exists(buffer.email, accountDetails)) {
        cout << "You are already a member!" << endl;
        return;
    }
    else {

        cout << "password: ";
        cin >> buffer.password;
        cout << "name: ";
        cin >> buffer.name;
        cout << "Shipping address: ";
        cin >> buffer.address;
        cout << "Contact phone number: ";
        cin >> buffer.phone;
    }
    accountDetails.resize(accountDetails.size() + 1);
    accountDetails[accountDetails.size() - 1] = buffer;
    cout << "Registration Completed!" << endl;
    for (int i = 0; i < 14; i++)
        buffer.cart[i] = 0;
    accountDetails.resize(accountDetails.size() + 1);
    accountDetails[accountDetails.size() - 1] = buffer;
    saveAllAccounts(accountDetails);
}

// return true if email belongs to accountDetails
bool exists(char email[], const vector< Account >& accountDetails)
{
    for (int i = 0; i < accountDetails.size(); i++) 
    {
        if (strcmp(email, accountDetails[i].email) == 0)
            return true;
    }
    return false;
}

// save all elements in accountDetails to the file Accounts.dat
void saveAllAccounts(const vector< Account >& accountDetails)
{
    ofstream outfile("Accounts.dat", ios::binary);
    for (int i = 0; i < accountDetails.size(); i++) 
    {
        outfile.write(reinterpret_cast<const char*>(&accountDetails[i]), sizeof(Account));
    }
}

// login and call shopping
void login(vector< Account >& accountDetails)
{
    loadAccountDetails(accountDetails);
    char email[40], password[20];
    Account buffer;
    do {
        cout << "Email address (0 to end): ";
        cin >> email;
        if (strcmp(email, "0") == 0) {
            return;
        }
        cout << "Password: ";
        cin >> password;
        if (!valid(email, password, buffer, accountDetails)) {
            cout << "Invalid account number or password.Please try again.\n";
        }
    } while (!valid(email, password, buffer, accountDetails));

    cout << endl;
    shopping(buffer);
    for (int i = 0; i < accountDetails.size(); i++) {
        if (strcmp(email, accountDetails[i].email) == 0) {
            if (strcmp(password, accountDetails[i].password) == 0)
                accountDetails[i] = buffer;
        }
    }
}

// load all accounts details from the file Accounts.dat
void loadAccountDetails(vector< Account >& accountDetails)
{
    fstream account("Accounts.dat", ios::in | ios::binary);
    account.seekg(0, ios::end);
    int numLine = account.tellg() / sizeof(accountDetails);
    account.seekg(0, ios::beg);
    accountDetails.resize(numLine);
    for (int i = 0; i < numLine; i++)
        account.read(reinterpret_cast<char*>(&accountDetails[i]), sizeof(accountDetails[i]));
}

// return true if there exists an account with specified email and password; and
// put the account with specified email and password into account
bool valid(char email[], char password[], Account& account,
    const vector< Account >& accountDetails)
{
    for (int i = 0; i < accountDetails.size(); i++) 
    {
        if (strcmp(email, accountDetails[i].email) == 0) 
        {
            if (strcmp(password, accountDetails[i].password) == 0)
            {
                account = accountDetails[i];
                return true;
            }
            else return false;
        }
    }
    return false;
}

// add chosen Foods to the shopping cart
void shopping(Account& account)
{
    int choice;
    for (int i = 1; i < 14; i++)
        cout << setw(3) << right << i << ". " << setw(48) << right << foods[i] << setw(10) << right << price[i] << endl;

    cout << endl;
    if (!emptyCart(account)) {
        cout << " 14. View your shopping cart\n";
        cout << endl;
        do cout << "Enter your choice (0 to logout): ";
        while ((choice = inputAnInteger(0, 14)) == -1);
    }
    else {
        cout << endl;
        do cout << "Enter your choice (0 to logout): ";
        while ((choice = inputAnInteger(0, 13)) == -1);
    }
    if (choice == 0)
        return;
    else if (choice == 14)
        displayCart(account);
    else {
        int num;
        do cout << "Enter the quantity: ";
        while ((num = inputAnInteger(1, 99)) == -1);
        account.cart[choice] += num;
        displayCart(account);
    }
    int choice2 = 0;
    while (choice2 != 1) {
        cout << "1. Continue Shopping\n";
        cout << "2. Update Cart\n";
        cout << "3. Check\n";
        do cout << "\nEnter your choice (1~3): ";
        while ((choice2 = inputAnInteger(1, 3)) == -1);
        cout << endl;
        switch (choice2)
        {
        case 1:
            shopping(account);
            break;
        case 2:
            updateCart(account);
            break;
        case 3:
            check(account);
        }
    }
    saveAccount(account);
}

// return true if the shopping cart is empty
bool emptyCart(const Account& account)
{
    for (int i = 1; i < 14; i++) 
    {
        if (account.cart[i] > 0) 
        {
            return false;
        }
    }
    return true;
}

// display the shopping cart in account
bool displayCart(const Account& account)
{
    int total = 0;
    cout << "Your Shopping Cart Contents:\n\n";
    cout << setw(4) << right << "Code" << setw(48) << right << "Item" << setw(10) << right << "Price" << setw(10) << "Quantity" << setw(10) << right << "Subtotal" << endl;
    for (int i = 1; i < 14; i++) {
        if (account.cart[i] > 0) {
            cout << setw(4) << right << i << setw(48) << right << foods[i] << setw(10) << right << price[i] << setw(10) << account.cart[i] << setw(10) << right << account.cart[i] * price[i] << endl;
            total += account.cart[i] * price[i];
        }
    }
    cout << endl;
    cout << "Total Cost: " << total << endl << endl;
    return true;
}

// append account in the file Accounts.dat
void saveAccount(const Account& account)
{
    vector<Account> buffer;
    fstream save("Accounts.dat", ios::in | ios::binary);
    save.seekg(0, ios::end);
    int numLine = save.tellg() / sizeof(buffer);
    save.seekg(0, ios::beg);
    buffer.resize(numLine);
    for (int i = 0; i < numLine; i++)
        save.read(reinterpret_cast<char*>(&buffer[i]), sizeof(buffer[i]));
    for (int i = 0; i < buffer.size(); i++) {
        if (strcmp(account.email, buffer[i].email) == 0) {
            if (strcmp(account.password, buffer[i].password) == 0) {
                buffer[i] = account;
                break;
            }
        }
    }
    save.close();
    fstream save2("Accounts.dat", ios::out | ios::binary);
    for (int i = 0; i < buffer.size(); i++) {
        save2.write(reinterpret_cast<const char*>(&buffer[i]), sizeof(buffer[i]));
    }
}

// update the shopping cart in account
void updateCart(Account& account)
{
    int choice, num;
    do cout << "Enter the product code: ";
    while ((choice = inputAnInteger(1, 13)) == -1);
    cout << endl;
    if (account.cart[choice] == 0) {
        updateCart(account);
        return;
    }
    do cout << "Enter the quantity: ";
    while ((num = inputAnInteger(0, 99)) == -1);
    account.cart[choice] = num;
    cout << endl;
    displayCart(account);
}

// generate a Bill and reset account.cart
void check(Account& account)
{
    Date arrival, current;
    Order order;
    cout << "Enter arrival dateDate\n";
    cout << "year: ";
    cin >> arrival.year;

    cout << "month: ";
    cin >> arrival.month;

    cout << "day: ";
    cin >> arrival.day;

    compCurrentDate(current);
    order.deliveryDate = current;
    for (int i = 0; i < 40; i++)
        order.email[i] = account.email[i];
    for (int i = 0; i < 14; i++)
    {
        order.quantity[i] = account.cart[i];
        account.cart[i] = 0;
    }
    srand(static_cast<unsigned int>(time(0)));
    order.orderNumber[0] = 'A' + rand() % 26;
    for (int i = 1; i < 10; i++)
        order.orderNumber[i] = '0' + rand() % 10;
    order.orderNumber[10] = '\0';
    order.arrivalDate = arrival;
    saveAccount(account);
    createOrder(account, order);
}

// compute the current date
void compCurrentDate(Date& currentDate)
{
    tm structuredTime;
    time_t rawTime = time(0);
    localtime_s(&structuredTime, &rawTime);

    currentDate.year = structuredTime.tm_year + 1900;
    currentDate.month = structuredTime.tm_mon + 1;
    currentDate.day = structuredTime.tm_mday;
}

// open the file Orders.txt and call displayOrderDetails twice
void createOrder(const Account& account, const Order& order)
{
    int total = 0;
    ofstream file("Orders.txt", ios::out);
    file << "Order number: " << order.orderNumber << endl;
    file << "Delivery Date: " << order.deliveryDate.year << "/ " << order.deliveryDate.month << "/ " << order.deliveryDate.day << endl;
    file << "Arrival Date: " << order.arrivalDate.year << "/ " << order.arrivalDate.month << "/ " << order.arrivalDate.day << endl;
    file << "Recipient: " << account.name << endl;
    file << "Contact Phone Number: " << account.phone << endl;
    file << "Shipping address: " << account.address << endl << endl;

    file << "Shopping details:" << endl << endl;
    file << setw(4) << right << "Code" << setw(48) << right << "Item" << setw(10) << right << "Price" << setw(10) << "Quantity" << setw(10) << right << "Subtotal" << endl;
    for (int i = 1; i < 14; i++)
    {
        if (order.quantity[i] > 0)
        {
            file << setw(4) << right << i << setw(48) << right << foods[i] << setw(10) << right 
                << price[i] << setw(10) << order.quantity[i] << setw(10) << right << order.quantity[i] * price[i] << endl;
            total += order.quantity[i] * price[i];
        }
    }
    file << endl;
    file << "Total Cost: " << total << endl << endl;
    displayOrderDetails(file, account, order);
}

// write an order to Orders.txt or display it on the output window depending on os
void displayOrderDetails(ostream& os, const Account& account, const Order& order)
{
    int total = 0;

    cout << "Order number: " << order.orderNumber << endl;
    cout << "Delivery Date: " << order.deliveryDate.year << "/ " << order.deliveryDate.month << "/ " << order.deliveryDate.day << endl;
    cout << "Arrival Date: " << order.arrivalDate.year << "/ " << order.arrivalDate.month << "/ " << order.arrivalDate.day << endl;
    cout << "Recipient: " << account.name << endl;
    cout << "Contact Phone Number: " << account.phone << endl;
    cout << "Shipping address: " << account.address << endl << endl;

    cout << "Shopping details:" << endl << endl;
    cout << setw(4) << right << "Code" << setw(48) << right << "Item" << setw(10) << right << "Price" << setw(10) << "Quantity" << setw(10) << right << "Subtotal" << endl;
    for (int i = 1; i < 14; i++)
    {
        if (order.quantity[i] > 0)
        {
            cout << setw(4) << right << i << setw(48) << right << foods[i] << setw(10) << right
                << price[i] << setw(10) << order.quantity[i] << setw(10) << right << order.quantity[i] * price[i] << endl;
            total += order.quantity[i] * price[i];
        }
    }
    cout << endl;
    cout << "Total Cost: " << total << endl << endl;
    cout << "An order has been created." << endl << endl;
}