 /* Name: Bryan Coleman 
 * Date: 7/10/19
 * Section: 2
 * Assignment: 4
 * Due Date: 7/10/19
 * About this project: Lets you create an int of infinite length
 * Assumptions: 
 *
 * All work below was performed by Bryan Coleman */
#include<iostream>
using namespace std;

class MyInt
{
	friend istream& operator>>(istream&, MyInt&);
	friend ostream& operator<<(ostream&, const MyInt&);
	
	friend bool operator==(const MyInt&, const MyInt&);
	friend bool operator<=(const MyInt&, const MyInt&);
	friend bool operator>=(const MyInt&, const MyInt&);
	friend bool operator<(const MyInt&, const MyInt&);
	friend bool operator>(const MyInt&, const MyInt&);
	friend bool operator!=(const MyInt&, const MyInt&);
	
	friend MyInt operator+(const MyInt&, const MyInt&);
	friend MyInt operator-(const MyInt&, const MyInt&);
	friend MyInt operator*(const MyInt&, const MyInt&);
	friend MyInt operator/(const MyInt&, const MyInt&);
	friend MyInt operator%(const MyInt&, const MyInt&);

	public:
	
	MyInt();
	MyInt(int);
	MyInt(const char *);
	MyInt(const MyInt&);
	MyInt& operator=(const MyInt&);
	~MyInt();
	
	MyInt& operator++();
	MyInt operator++(int);
	
	private:
	int * arrInt;
	int size, capacity;
	
	void grow();
	void shrink();
	void killLeadingZeros();
};

