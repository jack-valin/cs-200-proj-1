// User.cpp
#include <iostream>
using namespace std;
#include "user.h"
user::user()
{
	// setting everything to blank
	setName("","");
	setPassword("");
	setUserID(0,"");
}
//manipulators
void user::setName(string f, string l)
{
	first = f;
	last = l;
}
void user::setPassword(string p)
{
	password = p;
}
void user::setUserID(int num, string let)//let = letter
{
	stringstream sstm;//was std::
	sstm << let << num;
	userID = sstm.str();
}
void user::setUserID(string complete)
{
	userID = complete;
}

//accessors
string user::getName(){ return first + " " + last; }
string user::getPassword(){ return password; }
string user::getUserID(){ return userID; }
int user::getNumID(int num){ return numID; }
void user::logTransaction(int accNum, double original, double newBal, string name, bool type)
{
	stringstream line;
	string finalLine;
	ofstream transactionLog;
	int num = 0;

	transactionLog.open("TransactionLog.txt", ios::app);//userID __ made a transaction of $__ on account number __ belonging to __ new balance $__

	line.str("");
	finalLine = "";
	if (type == 1)
		line << "User " << getUserID() << " made a deposit of $" << (newBal - original) << " on account number " << accNum << " belonging to " << name 
			 << ": new balance $" << newBal << endl;
	else
		line << "User " << getUserID() << " made a withdrawal of $" << (newBal - original) << " on account number " << accNum << " belonging to " << name 
			 << ": new balance $" << newBal << endl;
	finalLine = line.str();//turns the stringstream into a string, saves it to finalLine
	transactionLog << finalLine;
	transactionLog.close();
	
	cout << "The transaction has been logged\n";
	cout << "The file can be found in: ";
	system("CD");
	cout << endl;
}
