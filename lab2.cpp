/*
Aayush Pokharel
COMP 201
*/


#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <cstdlib>

using namespace std;

int main()
{
	int value;
	int count = 0;
	vector<int>stack;
	vector<string>words;
	string word;

	cout << "WELCOME TO THE REVERSE POLISH NOTATION CALCULATOR\n";
	cout << "Please enter the operation you would like to perform. \nAnd end the equation with an \"=\" sign" << endl;

	//Slurps in from standard input
	while (cin >> word)
	{
		//Will Stop taking input after the user inputs an "=" sign.

		if (word == "=")
		{
			break;
		}

		//Fills up the string vector
		else
		{
			words.push_back(word);
		}	
	}

	for (int i = 0; i < words.size(); i++)
	{

		//The if statement will commence as long as the string inside the vector is an integer
		if (value = atoi(words.at(i).c_str()))
		{
			//Fills the integer stack vector with the integers.
			cout << "Pushing\t\t";
			stack.push_back(value);
		}
		else
		{
			cout << "Operation\t\t";

			//Assigns the last number in the stack to a variable and then pops the value off the stack
			int secondNum = stack.back();
			stack.pop_back();

			int firstNum = stack.back();
			stack.pop_back();

			//These conditional statements perform the many different operations as instructed by the user.
			if (words[i] == "+")
			{
				stack.push_back(firstNum + secondNum);
			}
			else if (words[i] == "-")
			{
				stack.push_back(firstNum - secondNum);
			}
			else if (words[i] == "*")
			{
				stack.push_back(firstNum * secondNum);
			}
			else if (words[i] == "/")
			{
				stack.push_back(firstNum / secondNum);
			}
			else
			{
				cout << "<Error>\n";
				exit(1);
			}
		}

		//prints out the stack as it changes
		for (int j = 0; j < stack.size(); j++)
		{
			cout << stack[j] << "\t";
		}
		cout << endl;
	}

	//prints out the final answer of the equation
	cout <<  "\n\nAnswer:\t" << stack.back() << endl << endl << endl;

	/*
	//barfs out the words backwards
	while (words.size() > 0)
	{
	//cout << endl << words.back() << endl << endl;
	//words.pop_back();



	}
	*/
	
	
}