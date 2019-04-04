//client.h
#include "user.h"
#ifndef CLIENT_H
#define CLIENT_H
class client: public user
{
	public:
	//constructors
		client();
	//mutators
		// these may take account objects as arguments?
		void activateAccount(account);
		void accountDeposit(account, double);
		void accountWithdraw(account, double);
		void setBirthDate(string);
	// accessors
		void getAccounts(int); // print accounts associated with this customer, pass the accountCount integer
		string getBirthDate();
	// utilities
		void print();
		int menu();
	protected:
		// using some other data type besides string for birthDate will likely be painful but necessary if we want to do anything more complicated than print it
		// but in case we need them, I found some references we may want later:
		// http://www.cplusplus.com/forum/beginner/130258/
		// https://www.tutorialspoint.com/cplusplus/cpp_date_time.htm
		string birthDate;
		account accounts[4];
		int accountCount;
};

#endif
