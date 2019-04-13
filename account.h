//account.h
#include <iostream>
using namespace std;
#ifndef ACCOUNT_H
#define ACCOUNT_H

class account
{
	public:
		account();

		double getBalance();
		string getType();
		int getAccountID();

		void setBalance(double);
		void setType(string);
		void setAccountID(int);

		void print();
		void deposit(double);
		void withdrawal(double);

		string formatSave();

	private:
		double balance;
		string type;
		int accountID;

	protected:

};

#endif
