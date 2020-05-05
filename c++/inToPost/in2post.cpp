#include"stack.h"
#include<iostream>
#include<string>
#include<vector>
#include<sstream>

using namespace std;
using namespace cop4530;

bool checkOperator(string);
bool checkOperand(string);
int precedence(string);
void in2post(vector<string> &, vector<string> &);
void postArt(vector<string> &);

int main()
{

	while(true)
{
	string input;
	string token;
	vector<string> inputVec;
	vector<string> newVec;

	cout<<"enter infix expression(\"exit\" to quit)->  ";
	getline(cin,input);	
	if(input == "exit")
		break;
	istringstream ss(input);	//put the input string into the istringstream ss
	while(getline(ss,token,' '))	//parses the string using the ' ' delim
	{
		if(!checkOperator(token) && !checkOperand(token))	//error checking
		{
			cout<<"incorrect token"<<endl;
			exit(1);
		}
		inputVec.push_back(token);	//put the single string into the vector<string>
	}
	
	in2post(inputVec, newVec);
	
	for(auto i = newVec.begin(); i != newVec.end(); i++)
		cout << *i << ' ';
	cout<<endl;

	postArt(newVec);
	cout<<endl;

}
cout<<endl; 
return(0);
}
	

bool checkOperator(string x)
{
	if(x == "+" ||
	x == "-" ||
	x == "*" ||
	x == "/" ||
	x == "(" ||
	x == ")")
		return true;
	return false;
}

//performs all the error checking we need
//examples of FALSE 2a, 2*12, (1, etc
bool checkOperand(string x)
{
	bool flag = false;
	for(int i = 0; i < x.size(); i++)
	{
		if(i == 0)
		{
			if(isdigit(x[i]));
			else if(isalpha(x[i]))
				flag = true;
			else 
			{
				cout<<"operand does not start with a digit or alpha"<<endl;
				return false;
			}
		}
		else if(i > 0 && flag)
		{
			if(isdigit(x[i]) || isalpha(x[i]) || x[i] == '_');
			else
			{
				cout<<"entered incorrect operand error"<<endl;
				return false;
			}
		}
		else
		{
			if(isdigit(x[i]) || x[i] == '.');
			else
			{
				cout<<"entered incorrect operand error"<<endl;
				return false;
			}
		}
	}
	return true;
}

//return precedence
int precedence(string x)
{
	if(x == "(" || x == ")") return 3;
	if(x == "*" || x == "/") return 2;
	if(x == "+" || x == "-") return 1;
	return 0;
}

//code refereced from Prof. Myers power points
void in2post(vector<string> & x, vector<string> & y)
{
	Stack<string> s;
	for(int i = 0; i < x.size(); i++)
	{
		if(!checkOperator(x[i]))
			y.push_back(x[i]);
		else if(x[i] != ")")
		{
			while(!s.empty() && s.top() != "(" && precedence(s.top()) >= precedence(x[i]))
			{
				y.push_back(s.top());
				s.pop();
			}
			s.push(x[i]);
		}
		else
		{
			while(!s.empty() && s.top() != "(")
			{
				y.push_back(s.top());
				s.pop();
			}
			s.pop();
		}
	}
	while(!s.empty())
	{
		y.push_back(s.top());
		s.pop();
	}

}

void postArt(vector<string> & x)
{
	Stack<float> s;
	bool flag = false;
	int counter = 0;
	for(auto i = x.begin(); i != x.end(); i++)
	{	
		string temp = *i;
		for(int j = 0; j < temp.size(); j++)
		{
			if(isalpha(temp[j]) || temp[j] == '_')
				flag = true;
		}
	}
	if(flag)
	{
		for(auto i = x.begin(); i != x.end(); i++)
                {
			cout << *i << ' ';
		}
	}
	else
	{
		for(int i = 0; i < x.size(); i++)
		{
			if(!checkOperator(x[i]))
			{	
				float temp = stof(x[i]);	//runs into a slight issue if you
				s.push(temp);			//accidently put extra spaces
			}
			else if(i == x.size() - 1)
			{
				float temp, temp2;
                                temp = s.top();
                                s.pop();
                                temp2 = s.top();
                                s.pop();
                                
                                if(x[i] == "*")
                                        s.push(temp2 * temp);
                                if(x[i] == "/")
                                        s.push(temp2 / temp);
                                if(x[i] == "+")
                                        s.push(temp2 + temp);
                                if(x[i] == "-")
                                        s.push(temp2 - temp);
				
				cout << s.top() << endl;
			}
			else
			{
				float temp, temp2;
				temp = s.top();
				s.pop();
				temp2 = s.top();
				s.pop();
				
				if(x[i] == "*")
					s.push(temp2 * temp);
				if(x[i] == "/")
                                        s.push(temp2 / temp);
				if(x[i] == "+")
                                        s.push(temp2 + temp);
				if(x[i] == "-")
                                        s.push(temp2 - temp);
			}
		}
	}
}

				
















