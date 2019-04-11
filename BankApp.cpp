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
void printToFile(admin* adm, int pop, int read)//population, read offsets the count so there are not old clients rewritten to the file
{														//may not need the read variable if we are rewriting the entire file
	stringstream line;
	string finalLine;
	ofstream adminData;
	int num = 0;

	adminData.open("AdminData.txt");//was "AdminData.txt", ios::app

	for(int i = 0; i < read; i++)
		adm++;

	for (int i = read; i < pop; i++)
	{
		line.str("");
		finalLine = "";
		line << adm->getUserID() << " " << adm->getPassword() << " " << adm->getName() << " " << adm->getAdminR() << endl; //fix with the get functions from admin
		finalLine= line.str();//turns the stringstream into a string, saves it to finalLine
		for(int e = 0; e < finalLine.length(); e++)
		{
			finalLine[e] = encrypt(finalLine[e]);
		}
		adminData << finalLine;
		num++;//a count of the number saved to the file
		adm++;
	}
	adminData.close();
	cout << "\n" << num << " new admin(s) have been saved to the file AdminData.txt\n";
	cout << "The file can be found in: ";
	system("CD");
	cout << "It is the same directory that this program is stored in" << endl;
	cout << endl;
}
int readFromFile(admin* adm, int pop)//pop = population (amount of admins in the array)
{
	ifstream adminDataIn("AdminData.txt");
	char choice;
	char ch;
	bool exist = false;
	stringstream line;

	string last, first, password, userID, rank;
	exist = adminDataIn.good();//test to see if the file exists

	if(exist == true)
	{
		adminDataIn >> ch;
		ch = encrypt(ch);
		while(!adminDataIn.eof())//while it is not at the end of file
		{
			line << ch;
			if(ch == '\n')
			{
				line >> userID >> password >> first >> last >> rank;//need to change for our variables
				adm->setUserID(userID);
				adm->setPassword(password);
				adm->setName(first, last);
				adm->setAdminR(rank);
				adm++;
				pop++;
				line.str("");
			}
			adminDataIn >> ch;
			ch = encrypt(ch);
		}
		adminDataIn.close();
	}
	system("PAUSE");
	return pop;
}
char encrypt(char ch)
{
	char enc = 'q';

	return (ch ^ enc);
}
