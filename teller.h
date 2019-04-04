//teller.h
#include "user.h"
#ifndef TELLER_H
#define TELLER_H
class teller: public user{
	public:
//constructors
		teller();
//mutators

		void setUserID(int, string);//takes in the numID and letter for class type

//utilities
	int menu() = 0;
	void print() = 0;

	protected:

};



#endif

