//teller.cpp
#include "teller.h"

teller::teller()
{
	setName("","");
	setPassword("");
	setUserID(0,"");
}
void teller::print()
{
	cout <<"Banker Info\n"
		 <<"\t"<<first<<" "<<last<<"\n"
		 <<"\tID: " << userID << endl;
}
int teller::menu()
{
	system("CLS");
	int choice = 1;
	do
	{
		if (choice < 1 || choice > 4)
		{
			cout << "Error: Invalid choice\nRe-enter: ";
			cin >> choice;
		}
		cout << "\t\tAdmin Menu\n"
			 << "\t1. Create Client\n"
			 << "\t2. EditClient\n"//should be something like interact with client
			 << "\t3. View Client\n"//shows a list of all the accounts
			 << "\t4. Save and Exit (logout)\n"
			 << "\tEnter Choice: ";
		cin >> choice;
	}while(choice < 1 || choice > 4);
	return choice;
}
