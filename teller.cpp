//teller.cpp
#include "teller.h"

teller::teller()
{
	setName("","");
	setPassword("");
	setUserID(0,"");
}

// Needed to make this overloaded constructor for working with vectors
teller::teller(string f, string l, int n, string type, string pw){
	setName(f, l);
	setPassword(pw);
	setUserID(n, type);
}

string teller::formatSave()
{
	stringstream line;
	string finalLine;

	line.str("");
	finalLine = "";
	line << getUserID() << "-" << getPassword() << "-" << getFirstName() << "-" << getLastName() << ":" << endl; //fix with the get functions from admin
	finalLine= line.str();//turns the stringstream into a string, saves it to finalLine

	return finalLine;
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
		cout << "\t\t Teller Menu\n"
			 << "\t\t ===========\n"
			 << "\t1. Create Client\n"
			 << "\t2. Make Transaction\n"
			 << "\t3. EditClient\n"//should be something like interact with client
			 << "\t4. View Client\n"//shows a list of all the accounts
			 << "\t5. Save and Exit (logout)\n"
			 << "\tEnter Choice: ";
		cin >> choice;
		switch(choice)
		{
			case 1:
				return 4;//for the main app switch case option
			case 2:
				return 6;
			case 3:
				return 5;//for the main app swtich case option
			case 4:
				return 3;
			case 5:
				cout << "Saving data and logging out" << endl;
				return 0;
			default:
				cout << "Error: Invalid choice\n";
		}
		system("PAUSE");
	}while(exit != true);
}
