// myIntDriver.cpp -- Sharanya Jayaraman
//
// Driver program to demonstrate the behavior of the MyInt class
// 
// You can add more tests of your own, or write other drivers to test your solution

#include <iostream>
#include "myInt.h"

using namespace std;

MyInt factorial(MyInt num);

int main()
{
	// demonstrate behavior of the two constructors and the << overload

	MyInt x(12345), y("9876543210123456789"), r1(-1000), r2 = "14H67", r3, r4, r5;
	char answer;
	cout << "Initial values: \nx = " << x << "\ny = " << y
		<< "\nr1 = " << r1 << "\nr2 = " << r2 << "\nr3 = " << r3 << "\n\n";

	// demonstrate >> overload

	cout << "Enter first number: ";
	cin >> x;
	cout << "Enter second number: ";
	cin >> y;

	cout << "You entered:\n";
	cout << "  x = " << x << '\n';
	cout << "  y = " << y << '\n';

	// demonstrate assignment =
	cout << "Assigning r1 = y ...\n";
	r1 = y;
	cout << "  r1 = " << r1 << '\n';

	// demonstrate comparison overloads
	if (x < y)	cout << "(x < y) is TRUE\n";
	if (x > y)	cout << "(x > y) is TRUE\n";
	if (x <= y)	cout << "(x <= y) is TRUE\n";
	if (x >= y)	cout << "(x >= y) is TRUE\n";
	if (x == y)	cout << "(x == y) is TRUE\n";
	if (x != y)	cout << "(x != y) is TRUE\n";
	
	// demonstrating + and * overloads

	r1 = x + y;
	cout << "The sum (x + y) = " << r1 << "\n\n";

	r2 = x * y;
	cout << "The product (x * y) = " << r2 << "\n\n";

	r3 = x - y;
	cout << "The difference (x - y) = " << r3 << "\n\n";

	r4 = x / y;
	cout << "The division (x / y) = " << r4 << "\n\n";

	r5 = x % y;
	cout << "The modulo (x % y) = " << r5 << "\n\n";

	cout << "The sum (x + 12345) = " << x + 12345 << "\n\n";
	cout << "The product (y * 98765) = " << y * 98765 << "\n\n";

	//create fatcorials, storead as MyInts using *, <= and ++
	cout << "The factorial of 45 is "<<factorial(45)<<endl;
	cout<<"The factorial of 100 is "<<factorial(100)<<endl;
	cout<<"The factorial of 281 is "<<factorial(281)<<endl;
	
	return 0;
}

MyInt factorial(MyInt num)
{
	MyInt f=1, n=1;
	while(n<=num)
	{
		f = f * n;
		n++;
	}
	cout << n << endl;
	return f;
}
