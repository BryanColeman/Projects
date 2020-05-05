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
using namespace std;

class Account
{
	public:
	Account(char *, int, char, double);
	void shortSummary() const;
	virtual void transaction(double, char) = 0;
	virtual void calcInterest();

	const char * getName() const;
	int getAccNum() const;
	char getAccType() const;
	double getBalance() const;
	int getTrans() const;

	void setName(char *);
	void setAccNum(int);
	void setAccType(char);
	void setBalance(double);
	void setTrans(int);

	virtual double getTotDep() const;
	virtual double getTotWith() const;

	virtual void setTotDep(double);
	virtual void setTotWith(double);

        virtual double getCredLim() const;
        virtual double getInterest() const;
        virtual double getPayments() const;
        virtual double getUsage() const;

        virtual void setCredLim(double);
        virtual void setInterest(double);
        virtual void setPayments(double);
        virtual void setUsage(double);

        protected:
        char name[50];
        int accountNumber;
        char accountType;
        double balance;
        int numOfTrans;

};

class CheckingAccount : public Account
{
	private:
	int totalDeposits;
	int totalWithdrawls;

	public:
	CheckingAccount(char *, int, char, double);
	void transaction(double, char);

	double getTotDep() const;
	double getTotWith() const;

	void setTotDep(double);
	void setTotWith(double);
};

class SavingsAccount : public Account
{
        private:
	double interest;
        int totalDeposits;
        int totalWithdrawls;

        public:
        SavingsAccount(char *, int, char, double, double);
        void transaction(double, char);
	void calcInterest();

	double getInterest() const;
	double getTotDep() const;
	double getTotWith() const;

	void setInterest(double);
	void setTotDep(double);
	void setTotWith(double);
};

class CreditCardAccount : public Account
{
	private:
	double creditLimit;
	double interest;
	double payments;
	double usage;

	public:
	CreditCardAccount(char *, int, char, double, double, double);
	void transaction(double, char);
	void calcInterest();

	double getCredLim() const;
	double getInterest() const;
	double getPayments() const;
	double getUsage() const;

	void setCredLim(double);
	void setInterest(double);
	void setPayments(double);
	void setUsage(double);
};

class AccountList
{
	private:
	Account ** accountList;
	int numberOfAccounts;

	public:
	AccountList();
	~AccountList();

	bool importFile(char *);
	bool createReportFile(char *);
	void showList() const;
	void calcInterest();
	void sortByName();
	void sortByBalance();
};
