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
#include<iomanip>
#include<cstring>
#include<cctype>
#include"myInt.h"
using namespace std;

MyInt::MyInt()								//default sets MyInt to 0
{
	size = 1;
	capacity = 5;
	arrInt = new int[capacity];
	arrInt[0] = 0;
}

MyInt::MyInt(int mi)						//sets MyInt from an integer
{
	if(mi < 0)								//if number less then 0 set to 0
	{
		size = 1;
		capacity = 5;
		arrInt = new int[capacity];
		arrInt[0] = 0;
	}
	else
	{
		int temp = mi;
		int getSize = 0;
		capacity = 5;
		arrInt = new int[capacity];
		do									//do while to get size for size and capacity
		{
			getSize++;
			temp /= 10;
		}while(temp);
		
		while(capacity <= getSize)			//set capacity and size
			grow();
		size = getSize;
		
		for(int i = size - 1; i >= 0; i--)	//loop to mod and divide in order to set the get the last digit then get rid of it
		{
			arrInt[i] = mi % 10;
			mi /= 10;
		}
	}
	killLeadingZeros();						//i always make this call to make sure any leading zeros get deleted
}

MyInt::MyInt(const char * mc)				//set a c string to the array of ints
{
	int len = strlen(mc);
	capacity = 5;
	int counter = 0;
	arrInt = new int[capacity];
	
	while(capacity <= len)
		grow();
	size = len;
	
	for(int i = 0; i < size; i++)
	{
		if(!(isdigit(mc[i])))				//of there is anythis besides a digit set the MyInt to 0
		{
			delete [] arrInt;
			capacity = 5;
			size = 1;
			arrInt = new int[capacity];
			arrInt[0] = 0;
			counter++;
			break;
		}
	}
	if(counter == 0)						//easy loop to see the array from the chars
	{
		for(int i = 0; i < size; i++)
		{
			arrInt[i] = mc[i] - '0';
		}
	}
	killLeadingZeros();
}

MyInt::MyInt(const MyInt& mi)				//takes a MyInt and sets it to another 
{
	while(capacity < mi.capacity)
		grow();
	while(capacity > mi.capacity + 5)
		shrink();
	size = mi.size;
	for(int i = 0; i < size; i++)
		arrInt[i] = mi.arrInt[i];
	killLeadingZeros();
}

MyInt& MyInt::operator=(const MyInt& mi)	//overload = to take a MyInt and set it to another.
{
	while(capacity < mi.capacity)
		grow();
	while(capacity > mi.capacity + 5)
		shrink();
	size = mi.size;
	for(int i = 0; i < size; i++)
		arrInt[i] = mi.arrInt[i];
	killLeadingZeros();
	return *this;
}

MyInt::~MyInt()								//deconstructor
{
	delete [] arrInt;
	size = 0;
	capacity = 0;
	arrInt = NULL;
}

void MyInt::grow()							//simple grow function very similar to the one we did in class
{	
	int newCap = capacity + 5;
	int * newArrInt = new int[newCap];
	for(int i = 0; i < capacity; i++)
		newArrInt[i] = arrInt[i];
	delete [] arrInt;
	arrInt = newArrInt;
	newArrInt = NULL;
	capacity = newCap;

}

void MyInt::killLeadingZeros()				//function to get rid of leading zeros i call this a lot just in case
{
	int theNumIsZero = 0;					//if the number is zero we must make sure it 
											//doesnt go down to nothing and keep one of the zeros
	for(int i = 0; i < size; i++)
	{
		if(arrInt[i] > 0)
			theNumIsZero++; 
	}
	while(arrInt[0] == 0 && theNumIsZero > 0)			//while loop that shifts to the left and gets ride of that
	{													//zero until no more leading zeros
		for(int i = 0; i < size - 1; i++)
			arrInt[i] = arrInt[i + 1];
		size--;
	}
	if(theNumIsZero == 0)
		size = 1;

	while(capacity > size + 5)
		shrink();
}

void MyInt::shrink()									//exactly the same as grow but backwards
{
	int newCap = capacity - 5;
	int * newArrInt = new int[newCap];
	for(int i = 0; i < newCap; i++)
			newArrInt[i] = arrInt[i];
	delete [] arrInt;
	arrInt = newArrInt;
	newArrInt = NULL;
	capacity = newCap;

}

ostream& operator<<(ostream& out, const MyInt& mi)		//extremely easy ostream overload
{
	for(int i = 0; i < mi.size; i++)
		out << mi.arrInt[i];
	return out;
}

istream& operator>>(istream& in, MyInt& mi)
{
	mi.capacity = 5;
	mi.size = 0;
	int i = 0;
	in >> ws;											//ws is a c++ function that clears whitespace
	while(isdigit(in.peek()))							//while we peek and is digit loop
	{
		char c = '\0';									//set char to \0
		in.get(c);										//get the digit we peeked
		mi.arrInt[i] = c - '0';							//set digit to arrInt index
		i++;											
		if(mi.capacity <= i)							//make sure we are growing as we need
			mi.grow();
	}
	mi.size = i;										//set size to i
	return in;

}

bool operator==(const MyInt& valueOne, const MyInt& valueTwo)
{
	if(valueOne.size != valueTwo.size)							//if they have different sizes obviously not equal
		return false;											//this is where deleting leading zeros is important
	for(int i = 0; i < valueOne.size; i++)						//if any numbers are different the number is not equal
	{
		if(valueOne.arrInt[i] != valueTwo.arrInt[i])
			return false;
	}
	return true;
}

bool operator<=(const MyInt& valueOne, const MyInt& valueTwo)
{
	if(valueOne == valueTwo)									//if they are equal return true
                return true;
	if(valueOne < valueTwo)										//if they are less return true
		return true;
	return false;
}

bool operator>=(const MyInt& valueOne, const MyInt& valueTwo)
{
	if(valueOne == valueTwo)									//similar to above
		return true;
	if(valueOne > valueTwo)
		return true;
	return false;
}

bool operator<(const MyInt& valueOne, const MyInt& valueTwo)
{
	if(valueOne.size < valueTwo.size)							//if valueone size is less its less then
		return true;
	if(valueOne.size > valueTwo.size)
		return false;
	for(int i = 0; i < valueOne.size; i++) 
	{
		if(valueOne.arrInt[i] > valueTwo.arrInt[i])
			return false;
		if(valueOne.arrInt[i] < valueTwo.arrInt[i])
			return true;
	}
	if(valueOne.arrInt[valueOne.size - 1] == valueTwo.arrInt[valueTwo.size - 1])	//if we got to the point we must make sure they arent equal
		return false;
	return true;
}

bool operator>(const MyInt& valueOne, const MyInt& valueTwo)
{
	if(valueOne < valueTwo)
		return false;
	if(valueOne == valueTwo)
		return false;
	return true;
}

bool operator!=(const MyInt& valueOne, const MyInt& valueTwo)
{
	if(valueOne == valueTwo)
		return false;
	return true;
}

MyInt operator+(const MyInt& valueOne, const MyInt& valueTwo)
{
	MyInt tempArr;
	int len = 0;
	int carryVObigger = 0;										//counters to see whihc one is larger
	int carryVTbigger = 0;
	
	if(valueOne.size < valueTwo.size)							//always makes enough room incase carry(gets taken care of later)
	{
		carryVTbigger = 1;
		len = valueTwo.size + 1;
	}
	else if(valueTwo.size < valueOne.size)
	{
		carryVObigger = 1;
		len = valueOne.size + 1;
	}
	else
		len = valueOne.size + 1;

	while(tempArr.capacity <= len)
		tempArr.grow();
	tempArr.size = len;

	int valOneSize = valueOne.size - 1;
	int valTwoSize = valueTwo.size - 1;
	int result = 0;
	int carry = 0;

	for(int i = tempArr.size - 1; i >= 0; i--)
	{
			if(valOneSize < 0 && valTwoSize != -1)							//checks to see which case we need to use
			{																//and adds the carry then mods by ten so incase result is for example	
					if(carryVObigger == 1)									//19 we get 9
							tempArr.arrInt[i] = carry;
					else
					{
							result = valueTwo.arrInt[valTwoSize] + carry;
							tempArr.arrInt[i] = result % 10;
							carry = 0;
					}
			}
			else if(valTwoSize < 0)
			{
					if(carryVTbigger == 1)
							tempArr.arrInt[i] = carry;
					else
					{
							result = valueOne.arrInt[valOneSize] + carry;
							tempArr.arrInt[i] = result % 10;
							carry = 0;
					}
			}
			else
			{
					result = valueOne.arrInt[valOneSize] + valueTwo.arrInt[valTwoSize] + carry;
					tempArr.arrInt[i] = result % 10;
			}
			if(result > 9)													//if result was over 9 the carry is set to 1
					carry = 1;
			else
					carry = 0;
			valOneSize--;
			valTwoSize--;
	}
	tempArr.killLeadingZeros();												//killLeadingZeros sets the number to the correct size
	while(tempArr.capacity > tempArr.size + 5)								//shrink if we need to
			tempArr.shrink();
	return tempArr;
}


MyInt operator-(const MyInt& valueOne, const MyInt& valueTwo)
{
	MyInt tempArr;
	MyInt tempArrTwo;
	tempArrTwo = valueOne;
	int len = valueOne.size;
	
	while(tempArr.capacity <= len)
		tempArr.grow();
	
	tempArr.size = len;
	for(int i = 0; i < len; i++)
		tempArr.arrInt[i] = 0;
	int valOneSize = valueOne.size - 1;
    int valTwoSize = valueTwo.size - 1;
		
	if(valueOne <= valueTwo)									//if valueOne is <= to valueTwo set the number to zero 
	{															//and shrink as we need
		tempArr = 0;
		tempArr.killLeadingZeros();
		while(tempArr.capacity > tempArr.size)
			tempArr.shrink();
	}
	else
	{
		for(int i = tempArr.size - 1; i >= 0; i--)			
		{
			if(valTwoSize < 0)														//loops through and does the correct on paper equation
			{
				if(tempArrTwo.arrInt[i] < 0)
				{
					tempArr.arrInt[i] = tempArrTwo.arrInt[i] + 10;
					tempArrTwo.arrInt[i - 1]--;
				}
				else
					tempArr.arrInt[i] = tempArrTwo.arrInt[i];
			}
			else if(tempArrTwo.arrInt[valOneSize] < valueTwo.arrInt[valTwoSize])
			{
				tempArrTwo.arrInt[i - 1]--;
				tempArr.arrInt[i] = (tempArrTwo.arrInt[valOneSize] + 10) - 
				valueTwo.arrInt[valTwoSize];
			}
			else
			{
				tempArr.arrInt[i] = tempArrTwo.arrInt[valOneSize] - 
				valueTwo.arrInt[valTwoSize];
			}
			valOneSize--;
			valTwoSize--;
		}
	}
	tempArr.killLeadingZeros();
	while(tempArr.capacity > tempArr.size + 5)
		tempArr.shrink();

	return tempArr;
}

MyInt operator*(const MyInt& valueOne, const MyInt& valueTwo)
{
	MyInt tempArr;
	MyInt tempArrTwo;
	int len = 0;
	len = valueOne.size + valueTwo.size;

	while(tempArr.capacity <= len)
	{
		tempArr.grow();
		tempArrTwo.grow();
	}

	for(int i = 0; i < len; i++)
		tempArrTwo.arrInt[i] = 0;
	
	int valueOneSize = valueOne.size - 1;
	int valueTwoSize = valueTwo.size - 1;
	int result = 0;
	int zeroCounter = 0;
	int counterTwo = 0;
	for(int i = valueTwoSize; i >= 0; i--)					//loops through and does the exact same thing as done on paper
	{
		int counter = 0;
		int carry = 0;
		int j = valueOneSize + counterTwo;
		for(int k = 0; k < zeroCounter; k++)				//this tacks the zeros on as we go down
		{
			tempArr.arrInt[j] = 0;
			j--;
			counter++;
		}
		for(; j >=0; j--)
		{
			result = valueTwo.arrInt[i] * valueOne.arrInt[j] + carry;
			tempArr.arrInt[j] = result % 10;
			carry = (result / 10);
			counter++;
		}
		if(carry > 0)
		{
			for(int l = counter; l > 0; l--)
				tempArr.arrInt[l] = tempArr.arrInt[l - 1];
			tempArr.arrInt[0] = carry;
			counter++;
		}
		tempArr.size = counter;
		if(counterTwo == 0)
			tempArrTwo.size = counter;
		tempArrTwo = tempArrTwo + tempArr;
		zeroCounter++;
		counterTwo++;
	}
	tempArr.killLeadingZeros();
	while(tempArr.capacity > tempArr.size + 5)
        tempArr.shrink();
	return tempArrTwo;
}

MyInt operator/(const MyInt& valueOne, const MyInt& valueTwo)
{

	MyInt tempArr;
	if(valueOne < valueTwo)
	{
		tempArr = 0;
		return tempArr;
	}
	if(valueOne == valueTwo)
	{
		tempArr = 1;
		return tempArr;
	}
	MyInt tempArrTwo;
	MyInt tempArrThree;
	int len = valueOne.size - valueTwo.size + 1;
	int lenTwo = valueOne.size + 1;

	while(tempArr.capacity <= len)
		tempArr.grow();
	while(tempArrThree.capacity <= lenTwo)
		tempArrThree.grow();

	tempArrTwo = valueOne;
	tempArr.size = len;
	for(int i = 0; i < lenTwo; i++)
		tempArrThree.arrInt[i] = 0;
	for(int i = 0; i < len; i++)
		tempArr.arrInt[i] = valueTwo.size + 1;

	tempArrThree.size = 0;
	int counter = 0;
	int counterTwo = 0;
	int i = 0;

	do													//grabs the first number we need to divide by
	{
		tempArrThree.arrInt[i] = valueOne.arrInt[i];
		i++;
		counterTwo++;
		tempArrThree.size++;
	}while(tempArrThree < valueTwo);

	if(tempArrThree.size > valueTwo.size)
	{
		len--;
		counter++;
	}

	for(int j = 0; j < len; j++)						//does pretty simple long division along with division by subtractions
	{
		int temp = 0;
		while(tempArrThree >= valueTwo)
		{
			tempArrThree = tempArrThree - valueTwo;
			tempArrThree.grow();
			temp++;
		}
		counterTwo++;
		tempArrThree.arrInt[tempArrThree.size] = valueOne.arrInt[i];
		tempArrThree.size++;
		i++;
		tempArr.arrInt[j] = temp;
		
	}
	if(counter == 1)
		tempArr.size--;
	tempArr.killLeadingZeros();
	while(tempArr.capacity > tempArr.size + 5)
		tempArr.shrink();

	return tempArr;

}

MyInt operator%(const MyInt& valueOne, const MyInt& valueTwo)
{
	MyInt tempArr;						//this does the mod = a - (a/b)b equation 
	tempArr = valueOne / valueTwo;
	if(tempArr == 0)					//if the Array is zero after division value is equal to valueOne
	{
		tempArr = valueOne;
		return tempArr;
	}
	tempArr = tempArr * valueTwo;
	tempArr = valueOne - tempArr;
	return tempArr;
}

MyInt& MyInt::operator++()
{
	for(int i = size - 1; i >= 0; i--)	//adds one to MyInt, it will also increase size by 1 if needed
	{
		
		if(arrInt[i] == 9)
			arrInt[i] = 0;
		else
		{
			arrInt[i] += 1;
			return *this;
		}
	}
	size += 1;
	if(capacity <= size)
		grow();
	arrInt[0] = 1;
	for(int i = 1; i < size; i++)
		arrInt[i] = 0;
	return *this;
}
	
MyInt MyInt::operator++(int)		//sends back orginal value but while adding 1 to MyInt
{
	MyInt tempArr;
	tempArr = *this;
	++(*this);
	return tempArr;
}

