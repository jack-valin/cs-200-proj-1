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
		bool deposit(double);
		bool withdrawal(double);
		
	private:
		double balance;
		string type;
		int accountID;
		
	protected:
	
};

#endif
