#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <memory> // required for unique_ptr

#include "user.h"
#include "admin.h"
#include "teller.h"
#include "client.h"
using namespace std;

void viewUser(vector<unique_ptr<user>>*); //shows the attributes of a user
int startMenu();
bool loginMenu(vector<unique_ptr<user>>*, int);
unsigned int findUser(vector<unique_ptr<user>>*, int, string); //finds the index of the username and returns it
bool checkPassword(vector<unique_ptr<user>>*, string, int);
void addTeller(vector<teller>*, vector<unique_ptr<user>>*); //teller pointer, teller max size, teller current size, user pointer, user max size, user current size
void addAdmin(vector<admin>*, vector<unique_ptr<user>>*); //same as the teller
void addClient(vector<client>*, vector<unique_ptr<user>>*); //same as the other two
void tellerTransaction(vector<unique_ptr<user>>*, int, vector<client>*, int); //clients / client size /
void printToFile(vector<unique_ptr<user>>*, int); //admin just to test, maybe use user** with a polymorphic approach
void readFromFile(vector<unique_ptr<user>>*, vector<admin>*, vector<teller>*, vector<client>*);
char encrypt(char); //simple Xor encryption, can change later
void editBanker(vector<unique_ptr<user>>*, int);
void editClient(vector<unique_ptr<user>>*, int);
bool checkForUserDataFile(); //see if UserData.txt already exists

int main() {
	int startOption;
	int choice; //for the different menus
	bool access = false; //whether they have access to the system or not
	unsigned int currentUserIndex; //positon of the user logged in in the user array

	vector<admin> admins;
	vector<teller> tellers;
	vector<client> clients;
	// https://stackoverflow.com/questions/27460377/why-is-using-vector-of-pointers-considered-bad
	// https://stackoverflow.com/questions/3283778/why-can-i-not-push-back-a-unique-ptr-into-a-vector#3283795
	vector<unique_ptr<user>> users;

	readFromFile(&users, &admins, &tellers, &clients);

	if (admins.empty()) {
		addAdmin(&admins, &users);
	}
	do {
		system("CLS");
		startOption = startMenu();
		switch (startOption) {
			case 1:
				access = loginMenu(users, currentUserIndex, userCount);//hard coded to test functionality
				if (access == true) { //login credentials were correct
					/*
					have a switch case for the return values that are returned from the different menus
					These corrospond the the return values from each different menu class
					*/
					do {
						choice = users[currentUserIndex]->menu();
						switch (choice) {
							case 0:
								printToFile(&users);
								break;
							case 1:
								telCount = addTeller(&tellers, &users);
								break;
							case 2:
								editBanker(&users, currentUserIndex);
								break;
							case 3:
								viewUser(&users);
								break;
							case 4:
								addClient(&clients, &users);
								break;
							case 5:
								editClient(&users, currentUserIndex);
								break;
							case 6:
								tellerTransaction(&users, currentUserIndex, &clients);
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

// userIndex is currently not used for anything. Do we want to implement a permissions check?
void editBanker(vector<unique_ptr<user>> *userPTR, unsigned int userIndex) {
	int choice;
	unsigned int targetIndex;
	string bankerID, f, l, edit;

	//Finds index of target UserID, checks for validity
	cout << "Enter Banker UserID: ";
	cin >> bankerID;
	targetIndex = findUser(&userPTR, bankerID);
	if (targetIndex == -1) {
		cout <<"Invalid UserID";
		return;
	}

	(*userPTR)[targetIndex] -> print();
	cout << "What would you like to edit: \n"
		 << "1. Name\n"
		 << "2. UserID\n"
		 << "3. Password\n"
		 << "Enter Number: ";
	cin >> choice;
	switch(choice) {
		case 1: //Change Name
			cout << "Enter Full Name: ";
			cin >> f>>l;
			(*userPTR)[targetIndex] -> setName(f, l);
			break;
		case 2: //Change userId
			cout << "Enter UserID: ";
			cin >> edit;
			(*userPTR)[targetIndex] -> setUserID(edit);
			break;
		case 3: //Change Password
			cout <<"Enter Password: ";
			cin >> edit;
			(*userPTR)[targetIndex] -> setPassword(edit);
			break;
		default:
			cout << "Invalid Choice.\n";
	}
	cout << "Data changed\n" << endl;
}

void editClient(vector<unique_ptr<user>> *userPTR, unsigned	int userIndex) {
	int choice, accID, numEdit;
	unsigned int targetIndex;
	string clientID, f, l, edit;

	//Finds index of target UserID, checks for validity
	cout << "Enter Client UserID: ";
	cin >> clientID;
	targetIndex = findUser(&userPTR, clientID);
	if (targetIndex == -1) {
		cout <<"Invalid UserID";
		return;
	}

	(*userPTR)[targetIndex] -> print();
	cout << "What would you like to edit: \n"
		 << "1. Name\n"
		 << "2. UserID\n"
		 << "3. Password\n"
		 << "4. Birthdate\n"
		 << "5. Active Account\n"
		 << "Enter Number: ";
	cin >> choice;
	switch(choice) {
		case 1: //Change Name
			cout << "Enter Full Name: ";
			cin >> f>>l;
			(*userPTR)[targetIndex] -> setName(f, l);
			break;
		case 2: //Change userId
			cout << "Enter UserID: ";
			cin >> edit;
			(*userPTR)[targetIndex] -> setUserID(edit);
			break;
		case 3: //Change Password
			cout <<"Enter Password: ";
			cin >> edit;
			(*userPTR)[targetIndex] -> setPassword(edit);
			break;
		case 4: //chage birthday
			cout << "Enter birthday: ";
			cin >> edit;
			(*userPTR)[targetIndex] -> setBirthDate(edit);
			break;
		case 5: //change existing account
			cout << "Enter account ID to change: ";
			cin >> accID;
			for ( int i = 0; i < (*userPTR)[targetIndex] -> accountCount; i++ ) {
				if ((*userPTR)[targetIndex] -> accounts[i].getAccountID() == accID) {
					cout << "What would you like to edit: \n"
		 				 << "1. Account ID\n"
		 				 << "2. Account Type\n"
		 				 << "Enter Number: ";
		 			cin >> choice;
		 			switch (choice) {
		 				case 1:
		 					cout << "Enter new account ID: ";
		 					cin >> numEdit;
		 					(*userPTR)[targetIndex] -> accounts[i].setAccountID(numEdit);
		 					break;
		 				case 2:
		 					cout << "Enter new account type: ";
		 					cin >> edit;
		 					(*userPTR)[targetIndex] -> accounts[i].setType(edit);
		 					break;
		 				default:
						 	cout << "Invalid Choice.\n";
					}
				}
			}
			break;
		default:
			cout << "Invalid Choice.\n";
	}
	cout << "Data changed\n" << endl;
}

void viewUser(vector<unique_ptr<user>> *userPTR) {
	string id;
	unsigned int found = 0;

	cout << "Enter the UserID you wish to view: ";
	cin >> id;
	for (unsigned int i = 0; i < (*userPTR).size(); i++)
	{
		if ((*userPTR) -> at(i) -> getUserID() == id)
		{
			found = i;
			break;
		}
	}
	if (found != 0)
		(*userPTR) -> at(found) -> print();
	else
		cout << "Error: ID not found\n" << endl;
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

bool loginMenu(vector<unique_ptr<user>> *userPTR, int &index){
	unsigned int position;
	string username, password;
	bool access = false;
	int count = 2;//for password attempts

	system("CLS");
	cout << "\n\t\t\tLogin\n\n"
		 << "\tUsername: ";
	cin >> username;
	position = findUser(&userPTR, username); // findUser will return -1 if not found

	if (position != -1)
	{
		cout << "\tPassword: ";
		cin >> password;
		access = checkPassword(&userPTR, password, position);
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
			access = checkPassword(&userPTR, password, position);
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

unsigned int findUser(vector<unique_ptr<user>> *userPTR, string name) {
	for (unsigned int i = 0; i < (*userPTR).size(); i++)
	{
		if ((*userPTR) -> at(i) -> getUserID() == name)
			return i;
	}
	return -1;
}

bool checkPassword(vector<unique_ptr<user>> *userPTR, string pass, unsigned int pos) {
	if ((*userPTR) -> at(pos) -> getPassword() == pass)
		return true;
	return false;
}

void addTeller(vector<teller> *tPTR, vector<unique_ptr<user>> *uPTR) {
	string first, last, password;
	int numID;
	char option;//for the commit y/n
	int exit = -1;

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
	do {
		if (option == 'y') {
			unique_ptr<teller> tmpTeller(new teller(first, last, numID, "t", password));
			tPTR -> push_back(*tmpTeller);
			uPTR -> push_back(move(tmpTeller));
			cout << "Data committed\n" << endl;
			exit = 0;
		}
		else if (option == 'n') {
			cout << "Data not committed\n" << endl;
			exit = 0;
		}
		else {
			cout << "Error: Invalid option, re-enter: ";
			cin >> option;
		}
	}while (exit != 0);
}

void addAdmin(vector<admin> *aPTR, vector<unique_ptr<user>> *uPTR) {
	string first, last, password, rank;
	int numID;
	char option;//for the commit y/n
	int exit = -1;

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
	do {
		if (option == 'y') {
			unique_ptr<admin> tmpAdmin(new admin(first, last, numID, "a", password, rank));
			aPTR -> push_back(*tmpAdmin);
			cPTR -> push_back(move(tmpAdmin));
			cout << "Data committed\n" << endl;
			exit = 0;
		}
		else if (option == 'n') {
			cout << "Data not committed\n" << endl;
			exit = 0;
		}
		else {
			cout << "Error: Invalid option, re-enter: ";
			cin >> option;
		}
	}while (exit != 0);
}

void addClient(vector<client>*, vector<unique_ptr<user>>*) {
	string first, last, password, birthday;
	int numID;
	char option;//for the commit y/n
	int exit = -1;

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
	do {
		if (option == 'y') {
			unique_ptr<client> tmpClient(new client(first, last, numID, "c", password, birthday));
			cPTR -> push_back(*tmpClient);
			uPTR -> push_back(move(tmpClient));
			cout << "Data committed\n" << endl;
			exit = 0;
		}
		else if (option == 'n') {
			cout << "Data not committed\n" << endl;
			exit = 0;
		}
		else {
			cout << "Error: Invalid option, re-enter: ";
			cin >> option;
		}
	}while (exit != 0);

}

void tellerTransaction(vector<unique_ptr<user>> *uPTR, unsigned int currentUserIndex, vector<client> *cPTR) {
	int targetID;
	char type;
	bool done = false;
	bool found = false;
	bool success = false;
	double amount;

	if (cPTR -> empty()) {
		cout << "Error: no clients entered\n" << endl;
	}
	else {
		cout << "Enter the account ID: ";
		cin >> targetID;
		for ( unsigned int i = 0; i < (*cPTR).size(); i++ ) {

			for ( unsigned int j = 0; j < (*cPTR)[i].accountCount; j++ ) {

				if ( (*cPTR)[i].accounts[j].getAccountID() == targetID ) {

					found = true;

					do {
						cout << "Enter transaction type (d / w): ";
						cin >> type;

						switch(type) {

							case 'd':
								cout << "Enter the amount to deposit: ";
								cin >> amount;
								success = (*cPTR)[i].accounts[j].deposit(amount);
								if (success == true)
									(*uPTR)[currentUserIndex] -> logTransaction((*cPTR)[i].accounts[j].getAccountID(), ((*cPTR)[i].accounts[j].getBalance() - amount), (*cPTR)[i].accounts[j].getBalance(), (*cPTR)[i].getName(), true);
								done = true;
								break;

							case 'w':
								cout << "Enter the amount to withdrawal: ";
								cin >> amount;
								success = (*cPTR)[i].accounts[j].withdrawal(amount);
								if (success == true)
									(*uPTR)[currentUserIndex] -> logTransaction(cPTR[i].accounts[j].getAccountID(), (cPTR[i].accounts[j].getBalance() - amount), cPTR[i].accounts[j].getBalance(), cPTR[i].getName(), false);
								done = true;
								break;

							default:
								cout << "Error: invalid choice entered\n" << endl;
						}
					}while(done == false);
				}
			}
		}

		if (found == false) {
			cout << "Error: account not found\n" << endl;
		}
	}
}

// void printToFile(user** usr, int pop)//population, read offsets the count so there are not old clients rewritten to the file
														//may not need the read variable if we are rewriting the entire file
void printToFile(vector<unique_ptr<user>> *uPTR) {
	stringstream line;
	string finalLine;
	ofstream userData;
	int num = 0;

	userData.open("UserData.txt");

	for (unsigned int i = 0; i < (*uPTR).size(); i++) {
		line.str("");
		finalLine = "";
		line << (*uPTR)[i] -> formatSave();
		finalLine= line.str();//turns the stringstream into a string, saves it to finalLine

		for(int e = 0; e < finalLine.length(); e++) {
			finalLine[e] = encrypt(finalLine[e]);
		}

		userData << finalLine;
		num++; //a count of the number saved to the file
	}
	userData.close();
	cout << "\nThe data has been saved\n";
	cout << "The file can be found in: ";
	system("CD");
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
// void readFromFile(user** uPTR, int userMax, int userSize, admin* aPTR, int admMax, int &admSize, teller* tPTR, int telMax, int &telSize, client* cPTR, int cliMax, int &cliSize)
void readFromFile(vector<unique_ptr<user>> *uPTR, vector<admin> *aPTR, vector<teller> *tPTR, vector<client> *cPTR) {
	ifstream userDataIn("UserData.txt");
	// char choice;  // do we need this?
	char ch;
	int chCount = 0;
	int position = 0;
	int previous = 0;
	// bool exist = false; // we don't need this as long as we're not using the userDataIn.good() check
	stringstream line;
	string finalLine;
	char userType;

	string dataElements[18];
	// exist = userDataIn.good();//test to see if the file exists

	if(checkForUserDataFile()) {
		userDataIn >> ch;
		chCount++;
		ch = encrypt(ch);
		while(!userDataIn.eof()) { //while it is not at the end of file
			line << ch;
			if(ch == ':') {
				for (int i = 0; i < chCount; i++) {
					finalLine = line.str();
					if (finalLine[i] == '-') {
						dataElements[position] = finalLine.substr(previous, i - previous);
						previous = i + 1;
						position++;
					}
					if (finalLine[i] == ':') {
						dataElements[position] = finalLine.substr(previous, i - previous);
						previous = i + 1;
						position++;
					}
				}
				position = 0;
				previous = 1;
				// The maximum possible number of elements in a line is 18 - a client with 4 accounts
				/*line >> dataElements[0]  // userID
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
						 >> dataElements[17];*/
				userType = 	dataElements[0][0]; // the first letter of the userID should be the type of user		dataElements[0].substr(0,1)
				switch (userType){
					case 'a': // load the administrator user

						// administrator saved text output should look like the following:
						// a12345 password Billy Bob rank
						//    0      1      2     3   4
						// And it must be passed to the overloaded constructor in this order:
						// 2 3 0sub1 "a" 1 4
						unique_ptr<admin> tmpAdmin(new admin(dataElements[2], dataElements[3], dataElements[0].substr(1), "a", dataElements[1], dataElements[4]));
						aPTR -> push_back(*tmpAdmin);
						uPTR -> push_back(move(ptr));
						break;

					case 'c': // load the client user

						// client saved text output should look like the following:
						// c12345 password Billy Bob birthDate accountCount  accountinfo...
						//    0      1      2     3      4         5             6...
						// And it must be passed to the overloaded constructor in this order:
						// 2 3 0sub1 "c" 1 4 5
						unique_ptr<client> tmpClient(new client(dataElements[2], dataElements[3], dataElements[0].substr(1), "c", dataElements[4], dataElements[5]))
						cPTR -> push_back(*tmpClient);

						// Add in each account via this loop
						// stoi should convert string to int, per: https://stackoverflow.com/questions/7663709/how-can-i-convert-a-stdstring-to-int
						for (int i = 0; i < stoi(dataElements[5]); i++) {
							// for the account IDs: ( i * 3 ) + 6
							// stoi(dataElements[(i * 3) + 6])
							// for the account types: ( i * 3 ) + 7
							// dataElements[(i * 3) + 7]
							// for the balances: ( i * 3 ) + 8
							// stod(dataElements[(i * 3) + 8])
							// and for the other conversion I'm using, reference: https://stackoverflow.com/questions/4754011/c-string-to-double-conversion
							cPTR -> back().loadAccount(stoi(dataElements[(i * 3) + 6]), dataElements[(i * 3) + 7], stod(dataElements[(i * 3) + 8]));
						}

						uPTR -> push_back(move(tmpClient));
						break;

					case 't': // load the teller user

						// teller saved text output should look like the following:
						// t12345 password Billy Bob
						//    0      1      2     3
						// And it must be passed to the overloaded constructor in this order:
						// 2 3 0sub1 "t" 1
						unique_ptr<teller> tmpTeller(new teller(dataElements[2], dataElements[3], dataElements[0].substr(1), "t", dataElements[1]));
						tPTR -> push_back(*tmpTeller);
						uPTR -> push_back(move(tmpTeller));
						break;
					default: cout << "ERROR: User type " << userType << " not recognized from UserData.txt file." << endl;
				}
				line.str("");
				chCount = 0;
			}
			userDataIn >> ch;
			chCount++;
			ch = encrypt(ch);
		}
		userDataIn.close();
	}
	else {
		cout << "ERROR: UserData.txt does not exist!" << endl;
	}
	return userSize;
}
char encrypt(char ch)
{
	char enc = 'q';

	return (ch ^ enc);
}

bool checkForUserDataFile(){
	ifstream userDataIn("UserData.txt");
	if (userDataIn.good()){
		return true;
	}
	else {
		return false;
	}
}
