//user.h
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;
#ifndef USER_H
#define USER_H
class user
{
	public:
//constructors
		user();
//mutators
		void setName(string, string);
		void setPassword(string);
		void setUserID(int, string);//takes in the numID and letter for class type
		void setUserID(string);
		void setUserID(string, string);
//accessors
		string getName();
		string getFirstName();
		string getLastName();
		string getPassword(); // I assume this will just return a hash of the password rather than the cleartext? Once we get to that point, of course. - Jack
		string getUserID();
		int getNumID(int);//takes the previous ID issued and increments it
//utilities
		virtual string formatSave() = 0;
		virtual int menu() = 0;
		virtual void print() = 0;
		void logTransaction(int, double, double, string, bool);//account number / old balance / new balance / account holder name / type of transaction 0 = w 1 = d
	protected:
		string first;
		string last;
		string password;
		string userID;
		int numID;//grouped into username, here so that they can be incremeted
};

#endif
