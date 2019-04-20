//teller.h
#include "user.h"
#ifndef TELLER_H
#define TELLER_H
class teller: public user
{
	public:
		teller();
		teller(string, string, int, string, string); // Needed to make this overloaded constructor for working with vectors
		string formatSave();
		void print();
		int menu();
	private:

};
#endif
