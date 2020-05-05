#include<iostream>
#include "distance.h"

using namespace std;

int main()
{
	//create some Distance objects
	Distance d1(10),d2(19,25,1),d3(8,-15),d4(2,2,2,'N'), d5(105,39,12,'K');

	//print them off to check the constructor
	cout<<"D1: "<<d1<<"D2: "<<d2<<"D3: "<<d3<<"D4: "<<d4<<"D5: "<<d5;

	//explicit conversion constructor
	Distance d6(123.4567);
	
	//test >> overload.
	//For the given output file, I entered 3,4,5 M
	cout<<"Enter values for a distance object in this format:\n large,mid,small format:\n";
	cin>>d1;
	cout<<"D1: "<<d1<<"D6: "<<d6;
	
	cout << "D2-D5: " <<d2-d5;

	//test setFormat
	d2.setFormat('M');
	cout<<"D2: "<<d2;

	//test memebr functions
	cout<<"D3+D4: "<<d3.add(d4);
	cout<<"D5-D4: "<<d5.subtract(d4);
	cout<<"Comparing d6 to d2, we get "<<d6.compare(d2)<<endl;
	
	//test math operator overloads
	cout<<"D1 + D22: "<<d1+d2;
	cout<<"D2 - D3: "<<d2-d3;

	//test relational operator overloads
	if(d2 > d4)
		cout<<"D2 is greater than d4"<<endl;

	d3 = d6;

	if(d3 == d6)
		cout<<"They are equal"<<endl;
	if(d2 < d1)
		cout<<"d2 is less"<<endl;
	if(d1 > d2)
		cout<<"d1 is more"<<endl;
	if(d1 != d2)
		cout<<"They are not equeal"<<endl;
	return 0;
}



