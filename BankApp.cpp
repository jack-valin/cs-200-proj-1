
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "user.h"
#include "admin.h"
#include "teller.h"
using namespace std;

const int SIZE = 100;	// More than required is okay, less is BAD!
string Users[SIZE]; // From your database
string Password[SIZE];	// From your database
void printToFile(admin*, int, int);
char encrypt(char);

int GetNameIndex(string query, int size)
{
	for (int i=0; i<size; i++) 
	{
		if (query == Users[i]) return i; //Returns the index
	}
	return -1; //Error code
}

bool PasswordMatch(int index, string pass)
{
	return (pass == Password[index]);
}

int main()
{
	//Reads the database;
	ifstream fin("database.txt");
	int i=0;

	while (!fin.eof())
	{
		fin >> Users[i] >> Password[i];
		i++; 
	}

	
	string usrname, pass;
	cout << "Enter your Login ID:";
	cin >> usrname;

	int index = GetNameIndex(usrname, i);

	cout << "Enter your pass:";
	cin >> pass;

	if (!PasswordMatch(index, pass))
	{
		cout << "Access DENIED";
		return 0;
	}



	return 0;
}
//may need to have different printToFile functions for each class type?? Polymorphic approach with User**?
void printToFile(admin* adm, int pop, int read)//population, read offsets the count so there are not old clietns rewritten to the file
{
	stringstream line;
	string finalLine;
	ofstream adminData;
	int num = 0;
	
	clientData.open("AdminData.txt", ios::app);
	
	for(int i = 0; i < read; i++)
	{
		cls++;
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
		num++;
		cls++;
	}
	adminData.close();
	cout << "\n" << num << " new admin(s) have been saved to the file AdminData.txt\n";
	cout << "The file can be found in: ";
	system("CD");
	cout << "It is the same directory that this program is stored in" << endl;
	cout << endl;
}
char encrypt(char ch)
{
	char enc = 'q';	
	
	return (ch ^ enc);
}
