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

//Account

Account::Account(char * setName, int setAccNum, char setAccType, double setBalance) //Account constructor that all children will call
{
	strcpy(name, setName);
	accountNumber = setAccNum;
	accountType = toupper(setAccType);
	balance = setBalance;
	numOfTrans = 0;
}

void Account::shortSummary() const
{
	cout << "Name of account holder: " << name << endl;
	cout << "Account type: " << accountType << endl;
	cout << "Balance: " << balance << endl;
	cout << "Number of transactions: " << numOfTrans << endl;
}

void Account::calcInterest()				//virtual function
{}

const char * Account::getName() const		//accessors and mutators
{
	return name;
}

int Account::getAccNum() const
{
	return accountNumber;
}

char Account::getAccType() const
{
	return accountType;
}

double Account::getBalance() const
{
	return balance;
}

int Account::getTrans() const
{
	return numOfTrans;
}

void Account::setName(char * newName)
{
	strcpy(name, newName);
}

void Account::setAccNum(int newAccNum)
{
	accountNumber = newAccNum;
}

void Account::setAccType(char newAccType)
{
	accountType = newAccType;
}

void Account::setBalance(double newBalance)
{
	balance = newBalance;
}

void Account::setTrans(int newNumTrans)
{
	numOfTrans = newNumTrans;
}

double Account::getTotDep() const			//virtual accessors and mutators
{
	return 0;
}

double  Account::getTotWith() const
{
	return 0;
}

void Account::setTotDep(double i)
{}

void Account::setTotWith(double i)
{}

double Account::getCredLim() const
{
	return 0;
}

double Account::getInterest() const
{
	return 0;
}

double Account::getPayments() const
{
	return 0;
}

double Account::getUsage() const
{
	return 0;
}

void Account::setCredLim(double i)
{}

void Account::setInterest(double i)
{}

void Account::setPayments(double i)
{}

void Account::setUsage(double i)
{}

//Checking Accounts

CheckingAccount::CheckingAccount(char * setName, int setAccNum, 
char setAccType, double setBalance)
: Account(setName, setAccNum, setAccType, setBalance)
{
	totalDeposits = 0;
	totalWithdrawls = 0;
}

void CheckingAccount::transaction(double amount, char tranType)
{
	tranType = toupper(tranType);						//sets tranType to upper just in case
	if(tranType == 'D')
	{
		balance = balance + amount;
		totalDeposits = totalDeposits + amount;
	}
	if(tranType == 'W')
	{
		balance = balance - amount;
		totalWithdrawls = totalWithdrawls + amount;
	}
	numOfTrans++;
}

double CheckingAccount::getTotDep() const				//accessors and mutators
{
	return totalDeposits;
}

double CheckingAccount::getTotWith() const
{
	return totalWithdrawls;
}

void CheckingAccount::setTotDep(double newTotDep)
{
	totalDeposits = newTotDep;
}

void CheckingAccount::setTotWith(double newTotWith)
{
	totalWithdrawls = newTotWith;
}

//Savings Account

SavingsAccount::SavingsAccount(char * setName, int setAccNum, 
char setAccType, double setBalance,double setInterest) 
: Account(setName, setAccNum, setAccType, setBalance)
{
	interest = setInterest;
	totalDeposits = 0;
	totalWithdrawls = 0;
}

void SavingsAccount::transaction(double amount, char tranType)
{
	tranType = toupper(tranType);
	if(tranType == 'D')
	{
		balance = balance + amount;
		totalDeposits = totalDeposits + amount;
	}
	if(tranType == 'W')
	{
		balance = balance - amount;
		totalWithdrawls = totalWithdrawls + amount;
	}
	numOfTrans++;
}

void SavingsAccount::calcInterest()
{
	balance = balance + ((balance * interest) / 400);
	numOfTrans++;
}

double SavingsAccount::getInterest() const			//Accessors and mutators
{
	return interest;
}

double SavingsAccount::getTotDep() const
{
        return totalDeposits;
}

double SavingsAccount::getTotWith() const
{
        return totalWithdrawls;
}

void SavingsAccount::setInterest(double newInterest)
{
	interest = newInterest;
}

void SavingsAccount::setTotDep(double newTotDep)
{
	totalDeposits = newTotDep;
}

void SavingsAccount::setTotWith(double newTotWith)
{
        totalWithdrawls = newTotWith;
}

//Credit Card Account

CreditCardAccount::CreditCardAccount(char * setName, int setAccNum, 
char setAccType, double setBalance, double setInterest, double setCreditLimit) 
: Account(setName, setAccNum, setAccType, setBalance)
{
	interest = setInterest;
	creditLimit = setCreditLimit;
	payments = 0;
	usage = 0;
}

void CreditCardAccount::transaction(double amount, char tranType)
{
	tranType = toupper(tranType);
	if(tranType == 'U')
	{
		if(balance + amount > creditLimit); 		//if balanace is going to go above credit limit
		else										//do nothing
		{
			balance = balance + amount;
			usage = usage + amount;
			numOfTrans++;
		}
	}
	
	if(tranType == 'P')
	{
		if(balance - amount < 0);					//if balance is going to go negative do nothing
		else
		{
			balance = balance - amount;
			payments = payments + amount;
			numOfTrans++;
		}
	}
}

void CreditCardAccount::calcInterest()
{
	double temp = (1 + (interest / 400)) * (1 + (interest / 400)) *
	(1 + (interest / 400)) * (1 + (interest / 400));
	balance = balance + (balance * temp - balance);
	numOfTrans++;
}

double CreditCardAccount::getCredLim() const		//Accessors and mutators
{
	return creditLimit;
}

double CreditCardAccount::getInterest() const
{
	return interest;
}

double CreditCardAccount::getPayments() const
{
	return payments;
}

double CreditCardAccount::getUsage() const
{
	return usage;
}

void CreditCardAccount::setCredLim(double newCredLim)
{
	creditLimit = newCredLim;
}

void CreditCardAccount::setInterest(double newInterest)
{
	interest = newInterest;
}

void CreditCardAccount::setPayments(double newPayments)
{
	payments = newPayments;
}

void CreditCardAccount::setUsage(double newUsage)
{
	usage = newUsage;
}

//Account List

AccountList::AccountList()
{
	numberOfAccounts = 0;
	accountList = new Account * [numberOfAccounts];
}

AccountList::~AccountList()
{
	for(int i = 0; i < numberOfAccounts; i++)	//must delete every single pointer since its "new"
		delete [] accountList[i];
	delete [] accountList;
	numberOfAccounts = 0;
}

bool AccountList::importFile(char * fileToImport)
{
	ifstream in;					//set ifstream to in
	in.open(fileToImport);			//open file
	if(!in)							//if no file opened return false
		return false;
	
	int numOfAcc;
	int numOfTrans;

	in >> numOfAcc;					//in collects data from the open file just like cin would
	in >> numOfTrans;
	in.ignore();
	int tempNOA = numberOfAccounts;	//temp numberof accounts for future for loop

	Account ** temp;										//"Grow" function to grow to exact size
	temp = new Account * [numberOfAccounts + numOfAcc];

	for(int i = 0; i < numberOfAccounts; i++)
	{
		temp[i] = accountList[i];
	}
	delete [] accountList;
	numberOfAccounts = numberOfAccounts + numOfAcc;
	accountList = temp;
	temp = NULL;

	
	for(int i = tempNOA; i < numberOfAccounts; i++)			//using previous number of accounts
	{														//to new number to append them
		char tempName[50];
		int tempAccNum;
		char tempAccType;
		in.getline(tempName, 50, ',');
		in >> tempAccNum;
		in.ignore();
		in >> tempAccType;

		double tempBalance;
		double tempInterest;
		double tempCredLim;
		switch(tempAccType)				//switch statement creating the heterogenious list
		{
			case 'C':
				in.ignore();
				in >> tempBalance;
				accountList[i] = new CheckingAccount(tempName, tempAccNum,
				'C', tempBalance);
				in.ignore();
				break;
			case 'S':
				in.ignore();
				in >> tempBalance;
				in.ignore();
				in >> tempInterest;
				accountList[i] = new SavingsAccount(tempName, tempAccNum,
				'S', tempBalance, tempInterest);
				in.ignore();
				break;
			default:
				in.ignore();
				in >> tempBalance;
				in.ignore();
				in >> tempInterest;
				in.ignore();
				in >> tempCredLim;
				accountList[i] = new CreditCardAccount(tempName, tempAccNum,
				'A', tempBalance, tempInterest, tempCredLim);
				in.ignore();
		}
	}
	for(int i = 0; i < numOfTrans; i++)				//going through transactions on file and 
	{												//applying them to the specifics accounts
		int tranAccNum;
		char tranType;
		double tranAmount;
		in >> tranAccNum;
		in >> tranType;
		in.ignore();
		in >> tranAmount;
		in.ignore();
		for(int j = 0; j < numberOfAccounts; j++)
		{		
			if(accountList[j]->getAccNum() == tranAccNum)
				accountList[j]->transaction(tranAmount, tranType);
		}
	}
	return true;
}

bool AccountList::createReportFile(char * fileToExport)
{
	ofstream out;					
	out.open(fileToExport);				//open file 
	if(!out)							//if not open return false
		return false;
	
	out <<"Checking Accounts"<< endl;														//this large chunk of text outputs	 
	out << setw(45) << "Name" << setw(15) << "accNo" << setw(15) << "Balance" << setw(15);	//the bank info onto a file
	out << "NumTrans" << setw(15) << "Deposits" << setw(15) <<"Withdrawls"<< endl;
	out <<"---------------------------------------------------------------";
	out <<"---------------------------------------------------------"<< endl;
	for(int i = 0; i < numberOfAccounts; i++)
	{
		if(accountList[i]->getAccType() == 'C')
		{
			out << fixed << showpoint << setprecision(2);
			out << setw(45) << accountList[i]->getName() << setw(15) << accountList[i]->getAccNum();
			out << setw(15) << accountList[i]->getBalance() << setw(15) << accountList[i]->getTrans();
			out << setw(15) << accountList[i]->getTotDep()<< setw(15) << accountList[i]->getTotWith() << endl;
		}
	}
	out <<"Savings Accounts"<< endl;
	out << setw(45) << "Name" << setw(15) << "accNo" << setw(15) << "Balance" << setw(15);
	out << "NumTrans" << setw(15) << "Deposits" << setw(15) <<"Withdrawls"<< endl;
	out <<"---------------------------------------------------------------";
	out <<"---------------------------------------------------------"<< endl;
	for(int i = 0; i < numberOfAccounts; i++)
	{
		if(accountList[i]->getAccType() == 'S')
		{
			out << fixed << showpoint << setprecision(2);
			out << setw(45) << accountList[i]->getName() << setw(15) << accountList[i]->getAccNum();
			out << setw(15) << accountList[i]->getBalance() << setw(15) << accountList[i]->getTrans();
			out << setw(15) << accountList[i]->getTotDep()<< setw(15) << accountList[i]->getTotWith() << endl;
		}
	}
	out <<"Credit Card Accounts"<< endl;
	out << setw(45) << "Name" << setw(15) << "accNo" << setw(15) << "Limit" << setw(15) << "Balance" << setw(15);
	out << "NumTrans" << setw(15) << "Payments" << setw(15) <<"Usage"<< endl;
	out <<"----------------------------------------------------------------";
	out <<"-----------------------------------------------------------------------"<< endl;
	for(int i = 0; i < numberOfAccounts; i++)
	{
		if(accountList[i]->getAccType() == 'A')
		{
			out << fixed << showpoint << setprecision(2);
			out << setw(45) << accountList[i]->getName() << setw(15) << accountList[i]->getAccNum();
			out << setw(15) << accountList[i]->getCredLim();
			out << setw(15) << accountList[i]->getBalance() << setw(15) << accountList[i]->getTrans();
			out << setw(15) << accountList[i]->getPayments()<< setw(15) << accountList[i]->getUsage() << endl;
		}
	}

}

void AccountList::showList() const
{

	cout << endl <<"Checking Accounts"<< endl;												//this large chunk of text prints out a smaller
	cout << setw(45) << "Name" << setw(15) << "accNo" << setw(15) << "Balance" << setw(15);	//amount of data to the stream
	cout << "NumTrans" << endl;
	cout << "-------------------------------------------------------------------------------------------" << endl;

	for(int i = 0; i < numberOfAccounts; i++)
	{
		if(accountList[i]->getAccType() == 'C')
		{
			cout << fixed << showpoint << setprecision(2);
			cout << setw(45) << accountList[i]->getName() << setw(15) << accountList[i]->getAccNum();
			cout << setw(15) << accountList[i]->getBalance() << setw(15) << accountList[i]->getTrans();
			cout << endl;
		}
	}

	cout <<"Savings Accounts"<< endl;
	cout << setw(45) << "Name" << setw(15) << "accNo" << setw(15) << "Balance" << setw(15);
	cout << "NumTrans" << endl;
	cout << "------------------------------------------------------------------------------------------" << endl;

	for(int i = 0; i < numberOfAccounts; i++)
	{
		if(accountList[i]->getAccType() == 'S')
		{
			cout << fixed << showpoint << setprecision(2);
			cout << setw(45) << accountList[i]->getName() << setw(15) << accountList[i]->getAccNum();
			cout << setw(15) << accountList[i]->getBalance() << setw(15) << accountList[i]->getTrans();
			cout << endl;
		}
	}

	cout <<"Credit Card Accounts"<< endl;
	cout << setw(45) << "Name" << setw(15) << "accNo" << setw(15) << "Balance" << setw(15);
	cout << "NumTrans" << endl;
	cout << "-------------------------------------------------------------------------------------------" << endl;

	for(int i = 0; i < numberOfAccounts; i++)
	{
		if(accountList[i]->getAccType() == 'A')
		{
			cout << fixed << showpoint << setprecision(2);
			cout << setw(45) << accountList[i]->getName() << setw(15) << accountList[i]->getAccNum();
			cout << setw(15) << accountList[i]->getBalance() << setw(15) << accountList[i]->getTrans();
			cout << endl;
		}
	}
}

void AccountList::calcInterest()
{
	for(int i = 0; i < numberOfAccounts; i++)
	{
		if(accountList[i]->getAccType() == 'S'
		|| accountList[i]->getAccType() == 'A')	//calculate interest if its savings or credit card account
			accountList[i]->calcInterest();
	}
}

void AccountList::sortByName()
{
	char temp[50];			//bubble sort almost identical to the one i used for movieList
	char tempTwo[50];
	bool keepGoing;

	for(int i = 0; i < numberOfAccounts - 1; i++)
	{
		keepGoing = false;
		for(int j = 0; j < numberOfAccounts - i - 1; j++)
		{
			strcpy(temp, accountList[j]->getName());
			strcpy(tempTwo, accountList[j + 1]->getName());

			if(strcmp(temp, tempTwo) > 0)
			{
				Account * tempAcc = accountList[j];
				accountList[j] = accountList[j + 1];
				accountList[j + 1] = tempAcc;
				keepGoing = true;
			}
		}
		if(keepGoing == false)
			break;
	}
}

void AccountList::sortByBalance()
{
	bool keepGoing;			//again just a bubble sort
	
	for(int i = 0; i < numberOfAccounts - 1; i++)
	{
		keepGoing = false;
		for(int j = 0; j < numberOfAccounts - i - 1; j++)
		{
			if(accountList[j]->getBalance() > accountList[j + 1]->getBalance())
			{
				Account * tempAcc = accountList[j];
				accountList[j] = accountList[j + 1];
				accountList[j + 1] = tempAcc;
				keepGoing = true;
			}
		}
		if(keepGoing == false)
			break;
	}
}
