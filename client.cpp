//client.cpp

#include "client.h"

//constructor
client::client(){
	// this is gonna need work
	// initialize the accounts somehow?
	setName("","");
	setPassword("");
	setUserID(0,"");
	accountCount = 0;
}

//manipulators
void client::activateAccount(){
	string t;
	int i;
	double b;
	char commit;
	bool exit = false;
	if (accountCount == 4)
	{
		cout << "Error: Max accounts already made" << endl;
		return;
	}
	else
	{
		cout << "\nEnter the account type (Checking or Savings): ";
		cin >> t;
		cout << "Enter the account ID: ";
		cin >> i;
		cout << "Enter the starting balance: $";
		cin >> b;
		cout << "Data entered:\n"
			 << "\tAccount type: " << t << "\n"
			 << "\tAccount ID: " << i << "\n"
			 << "\tBalamce: $" << b << "\n"
			 << "Do you wish to commit this data (y/n): ";
		cin >> commit;
		
		do
		{
			if (commit == 'y' || commit == 'Y')
			{
				accounts[accountCount].setType(t);
				accounts[accountCount].setAccountID(i);
				accounts[accountCount].setBalance(b);
				cout << "Data committed\n" << endl;
				exit = true;
				accountCount++;
			}
			else if(commit == 'n' || commit == 'N')
			{
				cout << "Data not committed\n" << endl;
				exit  = true;
			}
			else
			{
				cout << "Invalid entry\nRe-enter: ";
				cin >> commit;
			}
		}while(exit == false);
	}
}

void client::setBirthDate(string b){ birthDate = b; }

//accessors
string client::getBirthDate(){ return birthDate; }
void client::viewAccounts(){
	cout << "\nAccount information:"<<endl;
	for (int i=0; i < accountCount; i++){
		// here we're gonna have to fill in the appropriate account object output methods, maybe like this:
		cout << "\tAccount Number: " << accounts[i].getAccountID() << "\n"
		     << "\tBalance: $" << accounts[i].getBalance() <<"\n"<<endl;
	}
}

//utilities
void client::print(){
	//not sure just yet what we want this to print, but this is a suggestion - Jack
	cout << "Client information:\n"
	     << "\tUser ID: "<<getUserID()<<"\n"
	     << "\tName: "<<getName()<<"\n";
	     viewAccounts(); //The getAccounts accessor should handle formatting of account output
	cout << "END OF CLIENT"<<endl;
}

//I'm assuming that these menu functions should return an integer back to the main function which the main function understands how to interpret? - Jack
int client::menu(){
	int choice = 1;
	bool exit = false;
	do
	{
		system("CLS");
		cout << "\t\tClient menu\n"
		     << "\t\t===========\n"
		     << "\t1. View active accounts\n"
		     << "\t2. Activate Account\n"
		     << "\t3. Deposit\n"
		     << "\t4. Withdrawal\n"
		     << "\t5. Save and exit (logout)\n"
			 << "\tEnter your choice: ";
		cin >> choice;
		switch(choice)
		{
			case 1:
				viewAccounts();
				break;
			case 2:
				activateAccount();
				break;
			case 3:
				clientDeposit();
				break;
			case 4:
				clientWithdrawal();
				break;
			case 5:
				return 0;
			default:
				cout << "Error: Invalid choice\n";
		}
		system("PAUSE");
	}while(exit != true);
}
void client::clientDeposit()
{
	int accID;
	int targetIndex;
	bool found = false;
	double amount;
	
	if (accountCount < 1)
		cout << "Error: No active accounts\n";
	else
	{
		viewAccounts();
		cout << "\nEnter the account ID of the account: ";
		cin >> accID;
		for (int i = 0; i < accountCount; i++)
		{
			if (accounts[i].getAccountID() == accID)
			{
				targetIndex = i;
				found = true;
			}
		}
		if (found == true)
		{
			cout << "Enter the amount to deposit: $";
			cin >> amount;
			accounts[targetIndex].deposit(amount);
		}
		else
			cout << "Error: account ID not found\n"
				 << "Quiting to main menu" << endl;
	}

}
void client::clientWithdrawal()
{
	int accID;
	int targetIndex;
	bool found = false;
	double amount;
	
	if (accountCount < 1)
		cout << "Error: No active accounts\n";
	else
	{
		viewAccounts();
		cout << "\nEnter the account ID of the account: ";
		cin >> accID;
		for (int i = 0; i < accountCount; i++)
		{
			if (accounts[i].getAccountID() == accID)
			{
				targetIndex = i;
				found = true;
			}
		}
		if (found == true)
		{
			cout << "Enter the amount to withdrawal: $";
			cin >> amount;
			accounts[targetIndex].withdrawal(amount);
		}
		else
			cout << "Error: account ID not found\n"
				 << "Quiting to main menu" << endl;
	}
}
