// User.cpp
#include <sstream>
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
