//admin.h
#include "user.h"
#ifndef ADMIN_H
#define ADMIN_H
class admin: public user{
	public:
		admin();
		admin(string, string, int, string, string, string);
		void setAdminR(string);
		string getAdminR();
		string formatSave();
		void print();
		int menu();
	private:
		string rank;
};

#endif
