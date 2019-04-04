#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "user.h"
#include "admin.h"
#include "teller.h"
using namespace std;

int startMenu();
bool loginMenu(string*, string*, string&, string&, int);
char findUserType(string);
int findUser(string*, int, string);//finds the index of the username and returns it
bool checkPassword(string*, string, int);
void printToFile(admin*, int, int);//admin just to test, maybe use user** with a polymorphic approach
int readFromFile(admin*, int);//same as ^^
char encrypt(char);//simple Xor encryption, can change later


int main()
{
	const int SIZE = 100;	// More than required is okay, less is BAD!
	string Users[SIZE]; // From your database
	string Password[SIZE];	// From your database
	int startOption;
	bool access = false;//whether they have access to the system or not
	char userType;
	string currentUser;//the username for the current user loged in
	string currentPassword;//the password for the current user logged in
	
	Users[0] = "admin";
	Password[0] = "rosebud";
	
	admin adm;
	
	do
	{
		system("CLS");
        startOption = startMenu();
        switch (startOption)
        {
			case 1:
				access = loginMenu(Users, Password, currentUser, currentPassword, 1);//hard coded to test functionality
				if (access == true)//login credentials were correct
				{
					userType = findUserType(currentUser);
					switch (userType)
					{
						case 'a'://admin
							break;
						case 't'://teller			//call individual menu functions from classes here
							break;
						case 'c'://client
							break;
					}
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
bool loginMenu(string* users, string* pass, string &username, string &password, int pop)//pop is the number of people in the system to check against
{
	int position;
	bool access = false;
	int count = 2;
	
	system("CLS");
	cout << "\n\t\t\tLogin\n\n"
		 << "\tUsername: ";
	cin >> username;
	position = findUser(users, pop, username);
	
	if (position != -1)
	{
		cout << "\tPassword: ";
		cin >> password;
		access = checkPassword(pass, password, position);
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
			access = checkPassword(pass, password, position);
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
char findUserType(string u)
{
	return u[0];
}
int findUser(string* users, int num, string name)//num is the size of the users array
{
	for (int i = 0; i < num; i++)
	{
		if (users[i] == name)
			return i;
	}
	return-1;
}
bool checkPassword(string* passwords, string pass, int pos)//pos is the position the username was at
{
	if (passwords[pos] == pass)
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
	
	adminData.open("AdminData.txt", ios::app);
	
	for(int i = 0; i < read; i++)
		adm++;
	
	for (int i = read; i < pop; i++)
	{
		line.str("");
		finalLine = "";
		//line << cls->getID() << " " << cls->getFirstName() << " "  << cls->getLastName() << " " << cls->getBalance() << endl; //fix with the get functions from admin
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
int readFromFile(admin* cls, int pop)//pop = population (amount of admins in the array)
{
	ifstream adminDataIn("AdminData.txt");
	char choice;
	char ch;
	bool exist = false;
	stringstream line;
	
	//string last, first;
	//double amount;
	//int idGiven; //need to change for our local variables ^^^
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
				/*line >> idGiven >> first >> last >> amount;//need to change for our variables
				cls->setName(first, last);
				cls->setID(idGiven);
				cls->changeBalanceBy(amount);
				cls++;*/
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
