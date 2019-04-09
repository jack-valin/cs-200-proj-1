//teller.h
#include "user.h"
#ifndef TELLER_H
#define TELLER_H
class teller: public user
{
	public:
		teller();
		string formatSave();
		void print();
		int menu();
	private:
		
};
#endif
