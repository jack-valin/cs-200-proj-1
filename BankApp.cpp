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
bool loginMenu(user**, string&, string&, int);
int addTeller(teller*, int, int, user**, int, int&);//teller pointer, teller max size, teller current size, user pointer, user max size, user current size
char findUserType(string);
int findUser(user**, int, string);//finds the index of the username and returns it
bool checkPassword(user**, string, int);
void printToFile(admin*, int, int);//admin just to test, maybe use user** with a polymorphic approach
int readFromFile(admin*, int);//same as ^^
char encrypt(char);//simple Xor encryption, can change later



int main()
{
	//const int SIZE = 100;	// More than required is okay, less is BAD!
	//string Users[SIZE]; // From your database
	//string Password[SIZE];	// From your database
	int startOption;
	int choice;//for the different menus
	bool access = false;//whether they have access to the system or not
	string currentUser;//the username for the current user loged in
	string currentPassword;//the password for the current user logged in
	
	admin admins[10];//an aray of 10 admins
	teller tellers[10];//an array of 10 tellers
	client clients[50];//an array of 50 clients
	user* users[70];


	int userCount = 0;
	addTeller(tellers, 10, 0, users, 70, userCount);
	
	do
	{
		system("CLS");
        startOption = startMenu();
        switch (startOption)
        {
			case 1:
				access = loginMenu(users, currentUser, currentPassword, userCount);//hard coded to test functionality
				if (access == true)//login credentials were correct
				{
					//call menu functions with polymorphic approach
					/*
					
					have a switch case for the return values that are returned from the different menus
					The options in the different menus that have reutrn values need to be done in main
					The others can be handled in the .cpp files for each class
					swith case:
						case 0:
							save and quit
						case 1:
							create banker (teller)
						case 2:
							edit banker (teller)
						case 3:
							view all accounts (autid access)
						case 4:
							create client
						case 5:
							edit client
					These corrospond the the return values from each different menu class
					
					*/
					
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
bool loginMenu(user** userPTR, string &username, string &password, int pop)//pop is the number of people in the system to check against
{
	int position;
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
			return true;
		}
	}
	else
		cout << "\nError: Invalid Username\n";
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
char findUserType(string u)
{
	return u[0];
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
//may need to have different printToFile functions for each class type?? Polymorphic approach with User**?
void printToFile(admin* adm, int pop, int read)//population, read offsets the count so there are not old clietns rewritten to the file
{
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
