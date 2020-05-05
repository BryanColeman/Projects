#include<iostream>
using namespace std;

class Distance
{
	friend bool operator==(const Distance &valueOne, const Distance &valueTwo); 
	friend bool operator<=(const Distance &valueOne, const Distance &valueTwo); 
	friend bool operator>=(const Distance &valueOne, const Distance &valueTwo); 
	friend bool operator<(const Distance &valueOne, const Distance &valueTwo); 
	friend bool operator>(const Distance &valueOne, const Distance &valueTwo); 
	friend bool operator!=(const Distance &valueOne, const Distance &valueTwo); 

	friend ostream& operator<<(ostream& out, const Distance &distanceObj);	
	friend istream& operator>>(istream& in,Distance &distanceObj);	

	private:
	int smallMag, mediumMag, largeMag;
	char format;
	void setProperFormat();

	public:
	Distance(int small, int medium = 0, int large = 0, char createFormat = 'I');
	explicit Distance(double explicitDistance);
	
	void setFormat(char newFormat);
	
	Distance add(const Distance valueAdded) const;
	Distance subtract(const Distance valueSubed) const;
	int compare(const Distance valueCompared) const;

	Distance operator+(const Distance &valueAdded) const;
	Distance operator-(const Distance &valueSubed) const;

		
};
