/* Name: Bryan Coleman 
 * Date: 7/24/19
 * Section: 2
 * Assignment: 5
 * Due Date: 7/24/19
 * About this project: Simulates a bank account using a heterogeneous list
 * Assumptions: 
 *
 * All work below was performed by Bryan Coleman */
#include<iostream>
#include<cstring>
#include<iomanip>
#include<fstream>
#include"accountList.h"
using namespace std;

int main()
{
	AccountList list;
	bool quitOut = true;
	int menuChoice;

	do
	{
		cout <<"1. Import data into list"<< endl;
		cout <<"2. Export data from list"<< endl;
		cout <<"3. Print a list summary"<< endl;
		cout <<"4. Calculate interest for accounts"<< endl;
		cout <<"5. Sort accounts by name"<< endl;
		cout <<"6. Sort accounts by account number"<<endl;
		cout <<"7. Quit"<< endl;
		cout <<"Enter your choice: ";
		cin >> menuChoice;
		
		char fileName[30];
		switch(menuChoice)
		{
			case 1:
				cout <<"Enter the file name: ";
				cin >>fileName;
				if(list.importFile(fileName))
					cout<<"FILE IMPORT SUCCESSFUL"<<endl;
				else
					cout<<"FILE IMPORT UNSUCCESSFUL"<<endl;
				break;
			case 2:
				cout <<"Enter the file name: ";
				cin>>fileName;
				if(list.createReportFile(fileName))
					cout<<"FILE EXPORT SUCCESSFUL"<<endl;
				else
					cout<<"FILE EXPORT UNSUCCESSFUL"<<endl;
				break;
			case 3:
				list.showList();
				break;
			case 4:
				list.calcInterest();
				break;
			case 5:
				list.sortByName();
				cout<<"List sorted by name"<<endl;
				break;
			case 6:
				list.sortByBalance();
				cout<<"List sorted by balance"<<endl;
				break;
			case 7:
				cout<<"goodbye"<<endl;
				quitOut = false;
				break;
			default:
				cout <<"invalid choice"<< endl;
		}
	}while(quitOut);

		
	
	return 0;
}

