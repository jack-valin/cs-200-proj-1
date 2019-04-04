//admin.h
#include "user.h"
#ifndef ADMIN_H
#define ADMIN_H
class admin : public user{
	public:
	Admin();
	void setAdminR(string);
	void print();
	private:
		string rank;
	
};

#endif

