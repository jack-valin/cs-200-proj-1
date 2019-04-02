#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "user.h"
#include "admin.h"
#include "teller.h"
using namespace std;

bool loginMenu(string*, string*, int);
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

	Users[0] = "admin";
	Password[0] = "rosebud";
	loginMenu(Users, Password, 2);//hard coded to test functionality

	return 0;
}
bool loginMenu(string* users, string* pass, int pop)//pop is the number of people in the system to check against
{
	string username, password;
	int position;
	bool access = false;
	int count = 2;
	
	cout << "\t\t\t(YOUR AD HERE)\n\n"
		 << "\tUsername: ";
	cin >> username;
	position = findUser(users, pop, username);
	
	if (position != -1)
	{
		cout << "\tPassword: ";
		cin >> password;
		do
		{
			access = checkPassword(pass, password, position);
			if (access == true)
			{
				cout << "\nAccess Granted\n";
				count = 5;//to force the exit from the loop
				system("PAUSE");
			}
			else
			{
				cout << "Access Denied\n"
					 << "Attempt " << count << " of 4\n"
					 << "Re-enter Password: ";
				cin >> password;
				count ++;
			}
		}while(count <= 4);
	}
	else
	{
		cout << "Error: Invalid Username";
	}
}
int findUser(string* users, int num, string name)//num is the size of the users array
{
	for (int i = 0; i < num; i++)
	{
		if (users[i] == name)
		{
			return i;
		}
	}
	return-1;
}
bool checkPassword(string* passwords, string pass, int pos)//pos is the position the username was at
{
	if (passwords[pos] == pass)
	{
		return true;
	}
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
	{
		adm++;
	}
	
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
