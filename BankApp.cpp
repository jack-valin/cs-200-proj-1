#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "user.h"
#include "admin.h"
#include "teller.h"
#include "client.h"
using namespace std;

int startMenu();
bool loginMenu(user**, int&, int);
int findUser(user**, int, string);//finds the index of the username and returns it
bool checkPassword(user**, string, int);
int addTeller(teller*, int, int, user**, int, int&);//teller pointer, teller max size, teller current size, user pointer, user max size, user current size
int addAdmin(admin*, int, int, user**, int, int&);//same as the teller
int addClient(client*, int, int, user**, int, int&);//same as the other two
void printToFile(admin*, int, int);//admin just to test, maybe use user** with a polymorphic approach
int readFromFile(admin*, int);//same as ^^
char encrypt(char);//simple Xor encryption, can change later
void viewUser(user**, int, int);
bool checkForUserDataFile(); //see if UserData.txt already exists


int main()
{
	int startOption;
	int choice;//for the different menus
	bool access = false;//whether they have access to the system or not
	int currentUserIndex;//popsiton of the user logged in in the user array

	int userCount = 0;
	int telCount = 0;
	int admCount = 0;
	int clCount = 0;

	int admMax = 10;
	int telMax = 10;
	int clMax = 50;
	int usrMax = 70;

	admin admins[admMax];//an aray of 10 admins
	teller tellers[telMax];//an array of 10 tellers
	client clients[clMax];//an array of 50 clients
	user* users[usrMax];

	//add an if that tests if there are users in the file, if not, force the creation of an admin when it starts


	admCount = addAdmin(admins, admMax, admCount, users, usrMax, userCount);

	do
	{
		system("CLS");
        startOption = startMenu();
        switch (startOption)
        {
			case 1:
				access = loginMenu(users, currentUserIndex, userCount);//hard coded to test functionality
				if (access == true)//login credentials were correct
				{
					/*
					have a switch case for the return values that are returned from the different menus
					The options in the different menus that have reutrn values need to be done in main
					The others can be handled in the .cpp files for each class

					These corrospond the the return values from each different menu class
					*/
					do
					{
						choice = users[currentUserIndex]->menu();
						switch (choice)
						{
							case 0:
								//save data to files
								break;
							case 1:
								telCount = addTeller(tellers, telMax, telCount, users, usrMax, userCount);
								break;
							case 2:
								//edit banker (teller)
								break;
							case 3:
								viewUser(users, currentUserIndex, userCount);
								break;
							case 4:
								clCount = addClient(clients, clMax, clCount, users, usrMax, userCount);
								break;
							case 5:
								//edit client
								break;
							default:
								cout << "\nError: Invalid option\n";
						}
						system("PAUSE");
					}while(choice != 0);

				}
				else
					cout << "Login denied\n" << endl;
				break;
			case 2:
				cout << "\nGoodbye\n" << endl;
				break;
			default:
				cout << "\nError: Invalid option\n";
        }
        system("PAUSE");
	}while(startOption != 2);


	return 0;
}

void viewUser(user** userPTR, int userIndex, int pop)
{
	string name;

	cout << "Enter the UserID you wish to view: ";
	cin >> name;
	while ((*userPTR)->getUserID() != name)
		userPTR++;
	(*userPTR)->print();
}
int startMenu()
{
	int choice;
	cout << "\n\t\t\t(YOUR AD HERE)\n"
		 << "\t\t\t==============\n\n"
		 << "\t\t1. Login\n"
		 << "\t\t2. Quit\n"
		 << "\tEnter choice: ";
	cin >> choice;
	return choice;
}

bool loginMenu(user** userPTR, int &index, int pop)//pop is the number of people in the system to check against
{
	int position;
	string username, password;
	bool access = false;
	int count = 2;//for password attempts

	system("CLS");
	cout << "\n\t\t\tLogin\n\n"
		 << "\tUsername: ";
	cin >> username;
	position = findUser(userPTR, pop, username);

	if (position != -1)
	{
		cout << "\tPassword: ";
		cin >> password;
		access = checkPassword(userPTR, password, position);
		do
		{
			if (access == true)
			{
				cout << "\nAccess Granted\n";
				system("PAUSE");
				index = position;
				return true;
			}
			else
			{
				cout << "\tAccess Denied\n"
					 << "\n\tAttempt " << count << " of 4\n"
					 << "\tRe-enter Password: ";
				cin >> password;
				count ++;
			}
			access = checkPassword(userPTR, password, position);
		}while(count <= 4);
		if (access == true)
		{
			cout << "\nAccess Granted\n";
			system("PAUSE");
			index = position;
			return true;
		}
	}
	else
		cout << "\nError: Invalid Username\n";
	return false;
}
int findUser(user** userPTR, int num, string name)//num is the size of the users array
{
	for (int i = 0; i < num; i++)
	{
		if ((*userPTR)->getUserID() == name)
			return i;
		userPTR++;
	}
	return-1;
}
bool checkPassword(user** userPTR, string pass, int pos)//pos is the position the username was at
{
	if ((*userPTR[pos]).getPassword() == pass)
		return true;
	return false;
}
int addTeller(teller* tPTR, int telMax, int telSize, user** uPTR, int userMax, int &userSize)//return the new size of teller
{
	string first, last, password;
	int numID;
	char option;//for the commit y/n
	int exit = -1;

	if (telSize >= telMax)
		cout << "Error: tellers maxed out\n";
	else if(userSize >= userMax)
		cout << "Error: Users maxed out\n";
	else
	{
		for (int i = 0; i < telSize; i++){
			tPTR++;
		}
		cout <<"Enter full name: ";
		cin >>first>>last;
		cout <<"Enter the numerical id: ";
		cin >> numID;
		cout <<"Enter the password: ";
		cin >> password;
		cout << "\nData Entered:\n\t" << first << " " << last << "\n\t\tID: t" << numID << "\n\t\tPassword: "
			 << password;
		cout << "\nWould you like to commit this data (y / n): ";
		cin >> option;
		do
		{
			if (option == 'y')
			{
				tPTR->setName(first, last);
				tPTR->setUserID(numID, "t");
				tPTR->setPassword(password);
				cout << "Data committed\n" << endl;
				telSize++;
				uPTR[userSize] = tPTR;
				userSize++;
				exit = 0;
			}
			else if (option == 'n')
			{
				cout << "Data not committed\n" << endl;
				exit = 0;
			}
			else
			{
				cout << "Error: Invalid option, re-enter: ";
				cin >> option;
			}
		}while (exit != 0);
	}
	return telSize;
}
int addAdmin(admin* aPTR, int admMax, int admSize, user** uPTR, int userMax, int &userSize)//return the new size of teller
{
	string first, last, password, rank;
	int numID;
	char option;//for the commit y/n
	int exit = -1;

	if (admSize >= admMax)
		cout << "Error: admins maxed out\n";
	else if(userSize >= userMax)
		cout << "Error: Users maxed out\n";
	else
	{
		for (int i = 0; i < admSize; i++){
			aPTR++;
		}
		cout <<"Enter full name: ";
		cin >>first>>last;
		cout <<"Enter the numerical id: ";
		cin >> numID;
		cout <<"Enter the password: ";
		cin >> password;
		cout <<"Enter the admin rank: ";
		cin >> rank;
		cout << "\nData Entered:\n\t" << first << " " << last << "\n\t\tRank: " << rank << "\n\t\tID: a" << numID << "\n\t\tPassword: "
			 << password;
		cout << "\nWould you like to commit this data (y / n): ";
		cin >> option;
		do
		{
			if (option == 'y')
			{
				aPTR->setName(first, last);
				aPTR->setUserID(numID, "a");
				aPTR->setPassword(password);
				aPTR->setAdminR(rank);
				cout << "Data committed\n" << endl;
				admSize++;
				uPTR[userSize] = aPTR;
				userSize++;
				exit = 0;
			}
			else if (option == 'n')
			{
				cout << "Data not committed\n" << endl;
				exit = 0;
			}
			else
			{
				cout << "Error: Invalid option, re-enter: ";
				cin >> option;
			}
		}while (exit != 0);
	}
	return admSize;
}
int addClient(client* cPTR, int clMax, int clSize, user** uPTR, int userMax, int &userSize)//return the new size of teller
{
	string first, last, password, birthday;
	int numID;
	char option;//for the commit y/n
	int exit = -1;

	if (clSize >= clMax)
		cout << "Error: clients maxed out\n";
	else if(userSize >= userMax)
		cout << "Error: Users maxed out\n";
	else
	{
		for (int i = 0; i < clSize; i++){
			cPTR++;
		}
		cout <<"Enter full name: ";
		cin >>first>>last;
		cout <<"Enter the numerical id: ";
		cin >> numID;
		cout <<"Enter the password: ";
		cin >> password;
		cout <<"Enter birthday (mm/dd/yyyy): ";
		cin >> birthday;
		cout << "\nData Entered:\n\t" << first << " " << last << "\n\t\tID: c" << numID << "\n\t\tPassword: "
			 << password << "\n\t\tDOB: " << birthday;
		cout << "\nWould you like to commit this data (y / n): ";
		cin >> option;
		do
		{
			if (option == 'y')
			{
				cPTR->setName(first, last);
				cPTR->setUserID(numID, "c");
				cPTR->setPassword(password);
				cPTR->setBirthDate(birthday);
				cout << "Data committed\n" << endl;
				clSize++;
				uPTR[userSize] = cPTR;
				userSize++;
				exit = 0;
			}
			else if (option == 'n')
			{
				cout << "Data not committed\n" << endl;
				exit = 0;
			}
			else
			{
				cout << "Error: Invalid option, re-enter: ";
				cin >> option;
			}
		}while (exit != 0);
	}
	return clSize;
}

//may need to have different printToFile functions for each class type?? Polymorphic approach with User**?
// Prototype adjustment for the polymorphic approach. REQUIRES TESTING
void printToFile(user** usr, int pop, int read)//population, read offsets the count so there are not old clients rewritten to the file
{														//may not need the read variable if we are rewriting the entire file
	stringstream line;
	string finalLine;
	ofstream userData;
	int num = 0;

	userData.open("UserData.txt");//was "AdminData.txt", ios::app

	for(int i = 0; i < read; i++)
		usr++;

	for (int i = read; i < pop; i++)
	{
		line.str("");
		finalLine = "";
		line << usr->formatSave() << endl; //fix with the get functions from admin
		finalLine= line.str();//turns the stringstream into a string, saves it to finalLine
		for(int e = 0; e < finalLine.length(); e++)
		{
			finalLine[e] = encrypt(finalLine[e]);
		}
		userData << finalLine;
		num++;//a count of the number saved to the file
		usr++;
	}
	userData.close();
	cout << "\n" << num << " new admin(s) have been saved to the file AdminData.txt\n";
	cout << "The file can be found in: ";
	system("CD");
	cout << "It is the same directory that this program is stored in" << endl;
	cout << endl;
}
// Arguments to this function have to basically contain everything. It's a mess without vectors
// Here's the list:
// uPTR = pointer to user array
// usrMax = maximum number of users
// usrSize = current number of users
// aPTR = pointer to admin array
// admMax = maximum number of admins
// admSize = current number of admins
// tPTR = pointer to teller array
// telMax = maximum number of tellers
// telSize = current number of tellers
// cPTR = pointer to client array
// cliMax = maximum number of clients
// cliSize = current number of clients
int readFromFile(user** uPTR, int userMax, int userSize, admin* aPTR, int admMax, int &admSize, teller* tPTR, int telMax, int &telSize, client* cPTR, int cliMax, int &cliSize)
{
	ifstream userDataIn("UserData.txt");
	// char choice;  // do we need this?
	char ch;
	bool exist = false;
	stringstream line;
	string userType;

	string dataElements[18];
	// exist = userDataIn.good();//test to see if the file exists

	if(checkForUserDataFile())
	{
		// Doesn't this data need to get decrypted char by char? Or can it handle it all at once?
		userDataIn >> ch;
		ch = encrypt(ch);
		while(!userDataIn.eof())//while it is not at the end of file
		{
			line << ch;
			if(ch == '\n')
			{
				// The maximum possible number of elements in a line is 18 - a client with 4 accounts
				line >> dataElements[0]  // userID
						 >> dataElements[1]  // password
						 >> dataElements[2]  // first name
						 >> dataElements[3]  // last name
						 >> dataElements[4]  // rank / birthDate
						 >> dataElements[5]  // accountCount
						 >> dataElements[6]  // account id
						 >> dataElements[7]  // account type
						 >> dataElements[8]  // account balance
						 >> dataElements[9]  // account id
						 >> dataElements[10]
						 >> dataElements[11]
						 >> dataElements[12] // account id
						 >> dataElements[13]
						 >> dataElements[14]
						 >> dataElements[15] // account id
						 >> dataElements[16]
						 >> dataElements[17];
				userType = dataElements[0].substr(0,1); // the first letter of the userID should be the type of user
				switch (userType){
					case "a": // load the administrator user

						// check if we have too many admins or users first
						if ( admSize >= admMax ){
							cout << "ERROR: Attempted to load too many administrators!" << endl;
							break;
						}
						else if ( userSize >= userMax ){
							cout << "ERROR: Attempted to load too many users! (in admin case)" << endl;
							break;
						}

						// administrator saved text output should look like the following:
						// a12345 password Billy Bob rank
						//    0      1      2     3   4
						aPTR->setUserID(dataElements[0].substr(1), "a"); // passing the remainder of the existing userID with the substr() function of string, starting at index 1
						aPTR->setPassword(dataElements[1]);
						aPTR->setName(dataElements[2], dataElements[3]);
						aPTR->setAdminR(dataElements[4]);
						admSize++;
						uPTR[userSize] = aPTR;
						userSize++;
						aPTR++;
						break;

					case "c": // load the client user

						// check if we have too many clients or users first
						if ( cliSize >= cliMax ){
							cout << "ERROR: Attempted to load too many clients!" << endl;
							break;
						}
						else if ( userSize >= userMax ){
							cout << "ERROR: Attempted to load too many users! (in client case)" << endl;
							break;
						}

						// client saved text output should look like the following:
						// c12345 password Billy Bob birthDate accountCount  accountinfo...
						//    0      1      2     3      4         5             6...
						cPTR->setUserID(dataElements[0].substr(1), "c");
						cPTR->setPassword(dataElements[1]);
						cPTR->setName(dataElements[2], dataElements[3]);
						cPTR->setBirthDate(dataElements[4]);
						cliSize++;

						// Add in each account via this loop
						// stoi should convert string to int, per: https://stackoverflow.com/questions/7663709/how-can-i-convert-a-stdstring-to-int
						for (int i = 0; i < stoi(dataElements[5]); i++){
							// for the account IDs: ( i * 3 ) + 6
							// stoi(dataElements[(i * 3) + 6])
							// for the account types: ( i * 3 ) + 7
							// dataElements[(i * 3) + 7]
							// for the balances: ( i * 3 ) + 8
							// stod(dataElements[(i * 3) + 8])
							// and for the other conversion I'm using, reference: https://stackoverflow.com/questions/4754011/c-string-to-double-conversion
							cPTR -> loadAccount(stoi(dataElements[(i * 3) + 6]), dataElements[(i * 3) + 7], stod(dataElements[(i * 3) + 8]));
						}

						uPTR[userSize] = cPTR;
						userSize++;
						cPTR++;
						break;

					case "t": // load the teller user

						// check if we have too many tellers or users first
						if ( telSize >= telMax ){
							cout << "ERROR: Attempted to load too many tellers!" << endl;
							break;
						}
						else if ( userSize >= userMax ){
							cout << "ERROR: Attempted to load too many users! (in teller case)" << endl;
							break;
						}

						// teller saved text output should look like the following:
						// t12345 password Billy Bob
						//    0      1      2     3
						tPTR->setUserID(dataElements[0].substr(1), "t"); // passing the remainder of the existing userID with the substr() function of string, starting at index 1
						tPTR->setPassword(dataElements[1]);
						tPTR->setName(dataElements[2], dataElements[3]);
						telSize++;
						uPTR[userSize] = tPTR;
						userSize++;
						tPTR++;
						break;
					default: cout << "ERROR: User type " << userType << " not recognized from UserData.txt file." << endl;
				}
				line.str("");
			}
			userDataIn >> ch;
			ch = encrypt(ch);
		}
		userDataIn.close();
	}
	else {
		cout << "ERROR: UserData.txt does not exist!" << endl;
	}
	system("PAUSE");
	return userSize;
}
char encrypt(char ch)
{
	char enc = 'q';

	return (ch ^ enc);
}

// Since we're gonna want to check for this file's existance in main() as well as readFromFile(), I made it a function
bool checkForUserDataFile(){
	ifstream userDataIn("UserData.txt");
	if (userDataIn.good()){
		return true;
	}
	else {
		return false;
	}
}
