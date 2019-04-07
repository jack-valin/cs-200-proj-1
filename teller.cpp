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
	int choice = 1;
	bool exit = false;
	do
	{
		system("CLS");
		cout << "\t\tAdmin Menu\n"
			 << "\t1. Create Client\n"
			 << "\t2. EditClient\n"//should be something like interact with client
			 << "\t3. View Client\n"//shows a list of all the accounts
			 << "\t4. Save and Exit (logout)\n"
			 << "\tEnter Choice: ";
		cin >> choice;
		switch(choice)
		{
			case 1:
				return 4;//for the main app switch case option
			case 2:
				return 5;//for the main app swtich case option
			case 3:
				return 3;
			case 4:
				cout << "Saving data and logging out" << endl;
				return 0;
			default:
				cout << "Error: Invalid choice\n";
		}
		system("PAUSE");
	}while(exit != true);
}
