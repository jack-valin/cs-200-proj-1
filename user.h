//user.h
#include <iostream>
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
		void setuserID(int, string);//takes in the numID and letter for class type
//accessors
		string getName();
		string getPassword();
		string getUserID();
		int getNumID(int);//takes the previous ID issued and increments it
//utilities
		virtual int meun() = 0;
		virtual void print() = 0;
	protected:
		string first;
		string last;
		string password;
		string userID;
		int numID;//grouped into username, here so that they can be incremeted
};

#endif
