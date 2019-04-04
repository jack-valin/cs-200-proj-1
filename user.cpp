// User.cpp
#include "user.h"
user::user()
{
	// setting everything to blank
	setName("","");
	setPassword("");
	setUserID("");
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
void user::setUserID(string num, string let)//let = letter
{
	userID = let + num;
}

//accessors
string user::getName(){ return first + last; }
string user::getPassword(){ return password; }
string user::getUserID(){ return userID; }
int user::getNumID(){ return numID; }
