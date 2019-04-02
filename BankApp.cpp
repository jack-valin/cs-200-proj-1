#include <string>
#include <fstream>
#include <iostream>
#include "user.h"
#include "admin.h"
#include "teller.h"
 


using namespace std;

const int SIZE = 100;	// More than required is okay, less is BAD!
string Users[SIZE]; // From your database
string Password[SIZE];	// From your database


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
	cout << "Username:";
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
