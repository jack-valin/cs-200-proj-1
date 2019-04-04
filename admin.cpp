//admin.cpp
#include "admin.h"

admin::admin(){
	// setting everything null
	setName("","");
	setPassword("");
	setUserID(0,"");
	setAdminR("");
}
void admin::setAdminR(string r)
{
	rank = r;
}
void admin::print()
{
	cout <<"Admin Info\n"
		<<"\t"<<first<<" "<<last<<"\n"
		<<"\tID: " << userID << "\n"
		<<"\t\tRank: "<<rank<<endl;
}
int admin::menu()
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
			 << "\t\t==========\n"
			 << "\t1. Create Banker\n"
			 << "\t2. Edit Banker\n"
			 << "\t3. View Account\n"//shows a list of all the accounts
			 << "\t4. Save and Exit (logout)\n"
			 << "\tEnter Choice: ";
		cin >> choice;
	}while(choice < 1 || choice > 4);
	return choice;
}
