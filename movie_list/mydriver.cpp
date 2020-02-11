#include<iostream>
#include<string>

#include"tlist.h"

using namespace std;

template<typename T>
void PrintList(const TList<T>& L, string label)
{
	cout << label << "size is: " << L.GetSize() << "\n"
		<< label << " = ";
	L.Print(cout);
	cout << "\n\n";
}

int main()
{
	//default constructor
	TList<int> IL1;
	TList<char> CL1;
	
	PrintList(IL1, "IL1");
	PrintList(CL1, "CL1");
	
	//perameter constructor
	TList<int> IL2(100, 10);
	TList<char> CL2('B', 20);
	
	PrintList(IL2, "IL2");
	PrintList(CL2, "CL2");
	
	//copy construct and copy assignment operator
	TList<int> IL3;
	IL3 = IL2;
	TList<char> CL3(CL2);

	PrintList(IL3, "IL3");
	PrintList(CL3, "CL3");
	
	//move constuctor and move assignment
	TList<int> IL4(TList<int>(10,12));
	TList<char> CL4 = TList<char>('C',7);

	PrintList(IL4, "IL4");
	PrintList(CL4, "CL4");
	
	//test isempty and getsize
	if(IL4.IsEmpty())
		cout << "the list is empty" << "\n\n";
	else
		cout << "the list is not empty" << "\n\n";

	cout << IL4.GetSize() << endl << endl;
	
	//test clear
	IL4.Clear();

	if(IL4.IsEmpty())
                cout << "the list is empty" << "\n\n";
        else
                cout << "the list is not empty" << "\n\n";

	cout << IL4.GetSize() << endl << endl;
	
	//test insert front and remove front
	for(int i = 0; i < 10; i++)
		IL4.InsertFront(i * 2);
	PrintList(IL4, "IL4");
	
	for(int i = 0; i < 10; i++)
		IL4.RemoveFront();
	PrintList(IL4, "IL4");
	
	//test insert back and remove back
	for(int i = 0; i < 10; i++)
		CL4.InsertBack('A');
	PrintList(CL4, "CL4");
	
	for(int i = 0; i < 10; i++)
		CL4.RemoveBack();
	PrintList(CL4, "CL4");

	//test getfirst and last
	cout << CL4.GetFirst() << endl;
	cout << CL2.GetLast() << endl;

	TList<int> IL5;
	for(int i = 0; i < 4; i++)
		IL5.InsertFront(i);


	//test getiterator, getiteratorend
	//also test hasnext, hasprevious
	//also test Next, Previous, Insert, and remove
	PrintList(IL5, "IL5");
	TListIterator<int> itr = IL5.GetIterator();
	
	if(itr.HasNext())
		cout << "this element has one next" << endl << endl;
	else
		cout << "this element does not have one next" << endl << endl;
	if(itr.HasPrevious())
		cout << "this element has one previous" << endl << endl;
	else
		cout << "this element does not have one previous" << endl << endl;

	IL5.Insert(itr, 4);
	PrintList(IL5, "IL5");
	itr.Next();
	itr.Next();
	IL5.Remove(itr);
	itr.Next();
	IL5.Remove(itr);
	IL5.Remove(itr);
	IL5.Remove(itr);
	IL5.Remove(itr);
	PrintList(IL5, "IL5");	

        for(int i = 0; i < 4; i++)
                IL5.InsertFront(i);

	itr = IL5.GetIteratorEnd();

        if(itr.HasNext())
                cout << "this element has one next" << endl << endl;
        else
                cout << "this element does not have one next" << endl << endl;
        if(itr.HasPrevious())
                cout << "this element has one previous" << endl << endl;
        else
                cout << "this element does not have one previous" << endl << endl;

	IL5.Remove(itr);
	itr.Previous();
	itr.Previous();
	IL5.Insert(itr,100);
	PrintList(IL5, "IL5");
	itr.Previous();
	itr.Previous();
	IL5.Remove(itr);
	PrintList(IL5,"IL5");
	IL5.Remove(itr);
	IL5.Remove(itr);
	IL5.Remove(itr);
	PrintList(IL5,"IL5");
	IL5.Remove(itr);

	//test operator+
	TList<char> CL6 = CL2 + CL4;
	PrintList(CL6, "CL6");

	TList<char> CL7 = CL6 + TList<char>('!', 5);
	PrintList(CL7, "CL7");
	
	//GetData is used throughout the hpp
	return 0;
}







