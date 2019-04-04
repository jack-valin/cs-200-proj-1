
//admin.cpp

#include "admin.h"

admin::admin(){
	// setting everything null
	setAdminR("");


void admin::setAdminR(string r){
	rank = r;}
/* Wasn't sure which way we wanted to tackel these **DEW
string admin :: createAdminR (){
	cout << "Enter number coresponding to user level"
		<< " 1. Senior Admin"
		<< " 2. Junior Admin"
		<< " 3. Finacial Admin."endl;
	cin >> 
}*/

/*string admin :: createTeller (){
	cout << "Enter number coresponding to Employee level"
		<< " 1. Supervisor"
		<< " 2. Banker"endl;
	cin	<< 

}
*/
void admin:: print(){
	cout <<"Admin Info\n"
		<<"Full Name: "<<first<<" "<<last<<"\n"
		<<"Rank: "<<rank<<endl;
}
