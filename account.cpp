//account.cpp
#include "account.h"

account::account()
{
	setBalance(0);
	setType("");
	setAccountID(0);
}
double account::getBalance() {return balance;}
string account::getType(){return type;}
int account::getAccountID(){return accountID;}
void account::setBalance(double b) {balance = b;}
void account::setType(string t){type = t;}
void account::setAccountID(int id){accountID = id;}

void account::print()
{
	cout << accountID <<"\n"
		 <<"\tBalance: $" << getBalance() << endl;
}
void account::deposit(double amount)
{	
	if (amount < 0)
	{
		cout << "Error: Invalid deposit amount" << endl;
		return;
	}
		balance+=amount;
		cout << "Deposit successful\n";
}
void account::withdrawal(double amount){
	if (amount < 0)
		amount = amount * (-1);//if you are trying to withdrawal a negative amount, it will correct to positive
	if (balance < amount)
	{
		cout << "Error: Overdraft\n";
		return;
	}
		balance-=amount;
		cout << "Withdrawal successful\n";
}
