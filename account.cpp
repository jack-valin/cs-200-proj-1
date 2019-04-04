//account.cpp

#include "account.h"

class account(){
	
void print(int maxC, acctInfo* acc){
	for (int i=0;i<maxCount;i++){
		cout<<"Account holder:"<<first<<"\t"<<last<<"\t"<<NumID<<"\t"
			<<"Has a balance of:  "<<bal<<"\n";
			acc++;
	}
}
void withD(int maxCount,acctInfo* acc){
	double withDA;
	string findTheDiff;
	cout<<"Enter your account number:";
	cin>>findTheDiff;	
	for(int i=0;i<maxCount;i++){
		if(findTheDiff==NumID){
			cout<< "Retrieving your record now. . .\n";
			break;
		}
		acc++;
	}
	cout<<"Enter the amount you wish to withdraw:";
	cin>>withDA;
	bal-=withDA;
}

void depoBal(int maxCount, acctInfo* acc){
	double depo;
	string findTheDiff;
	cout<<"Enter your account number:";
	cin>>findTheDiff;	
	for(int i=0;i<maxCount;i++){
		if(findTheDiff==NumID){
			cout<< "Retrieving your record now. . .\n";
			break;
		}
		acc++;
	}
	cout<<"Enter the amount you wish to deposit:";
	cin>>depo;
	bal+=depo;
	
}
}


