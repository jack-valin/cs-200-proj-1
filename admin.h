//admin.h
#include "user.h"
#ifndef ADMIN_H
#define ADMIN_H
class admin: public user{
	public:
		admin();
		void setAdminR(string);
		void print();
		int menu();
	private:
		string rank;
	
};

#endif

