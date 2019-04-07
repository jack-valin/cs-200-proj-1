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
		<<"\t\tID: " << userID << "\n"
		<<"\t\tRank: "<<rank<<endl;
}
int admin::menu()
{
	int choice = 1;
	bool exit = false;
	do
	{
		system("CLS");
		cout << "\t\tAdmin Menu\n"
			 << "\t\t==========\n"
			 << "\t1. Create Banker\n"
			 << "\t2. Edit Banker\n"
			 << "\t3. View Account\n"//shows a list of all the accounts
			 << "\t4. Save and Exit (logout)\n"
			 << "\tEnter Choice: ";
		cin >> choice;
		switch(choice)
		{
			case 1:
				return 1;//for the main app switch case option
			case 2:
				return 2;//for the main app swtich case option
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
