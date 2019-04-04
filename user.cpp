// User.cpp
#include <sstream>
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
	std::stringstream sstm;
	sstm << let << num;
	userID = sstm.str();
}

//accessors
string user::getName(){ return first + last; }
string user::getPassword(){ return password; }
string user::getUserID(){ return userID; }
int user::getNumID(int num){ return numID; }
