// User.cpp
#include "user.h"
user::user()
{
	
}
void user::setName(string f, string l)
{
	first = f;
	last = l;
}
void user::setPassword(string p)
{
	password = p;
}
void user::setuserID(string num, string let)//let = letter
{
	userID = let + num;
}
