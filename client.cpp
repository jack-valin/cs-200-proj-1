//client.cpp

#include "client.h"

//constructor
client::client(){
	// this is gonna need work
}

//manipulators
void client::activateAccount(account acc){

}

// account to be modified and ammount to change it by are its arguments
/*void client::accountDeposit(account acc, double am){

}*/

// account to be modified and ammount to change it by are its arguments
/*void client::accountWithdraw(account acc, double am){

}*/

void client::setBirthDate(string b){ birthDate = b; }

//accessors
string client::getBirthDate(){ return birthDate; }
void client::getAccounts(int accountCount){
	cout << "Account information:"<<endl;
	for (int i=0; i < accountCount; i++){
		// here we're gonna have to fill in the appropriate account object output methods, maybe like this:
		// cout << "Account Number: " << account[i] -> getAccountNum() << "\n"
		//      << "Balance: " << account[i] -> getBalance() <<endl;
	}
}

//utilities
void client::print(){
	//not sure just yet what we want this to print, but this is a suggestion - Jack
	cout << "Client information:\n"
	     << "User ID: "<<getUserID()<<"\n"
	     << "Name: "<<getName()<<"\n";
	     getAccounts(accountCount); //The getAccounts accessor should handle formatting of account output
	cout << "END OF CLIENT"<<endl;
}

//I'm assuming that these menu functions should return an integer back to the main function which the main function understands how to interpret? - Jack
int client::menu(){
	system("CLS");
	int choice = 1;
	do
	{
		if (choice < 1 || choice > 4)
		{
			cout << "Error: Invalid choice\nRe-enter: ";
			cin >> choice;
		}
		cout << "\t\tClient menu\n"
		     << "\t\t===========\n"
		     << "\t1. View active accounts\n"
		     << "\t2. Activate Account\n"
		     << "\t3. Deposit\n"
		     << "\t4. Withdrawal\n"
		     << "\t5. Save and exit (logout)\n"
			 << "\tEnter your choice: ";
		cin >> choice;
	}while(choice < 1 || choice > 4);

	return choice;
}
