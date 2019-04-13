//client.h
#include "user.h"
#include "account.h"
#ifndef CLIENT_H
#define CLIENT_H
class client: public user
{
	public:
	//constructors
		client();
	//mutators
		// these may take account objects as arguments?
		void activateAccount();//does not have a parameter because the accountCount can be accessed
		//void accountDeposit(account, double);
		//void accountWithdraw(account, double);//maybe do this in the accounts themselves to make it simpler, the call would be something like:
																													// client.accounts[i].withdrawal(amount)
		void setBirthDate(string);
	// accessors
		// I just made this a function of the account class, namely formatSave(). It was easier
		// void viewAccounts(); // print accounts associated with this customer, pass the accountCount integer
		string getBirthDate();
	// utilities
		string formatAccount(int); //to format the accounts to be called in formatSave(). Pass index of desired account from the accounts[] array
		string formatString();
		string formatSave();
		void print();
		int menu();
		void clientDeposit();
		void clientWithdrawal();
		void loadAccount(int, string, double); // for use in the readFromFile() function in BankApp.cpp
	//	public://changed from protected so they can be used in the main app?
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
