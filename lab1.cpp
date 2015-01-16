/*
*Aayush Pokharel
*Comp Sci
*Prof. Lawrence
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

int main()
{
	//Varaiable Declarations
	int input;
	int product = 1;
	int sum = 0;
	string iFileName;
	string oFileName = "output.txt";
	ifstream inStream;
	ofstream outStream;

	//Console Prompt for the input file name.
	cout << "Please input the intput file name. (Ex: \"Input.txt\"):\n";
	cin >> iFileName;

	//Opens the input and output text files
	inStream.open(iFileName);
	outStream.open(oFileName);
	
	//Error checks if the input and output are not found
	if (inStream.fail())
	{
		cout << "<Error Input File"
			<< iFileName
			<<"Not Found>\n";
		exit(1);
	}
	else if (outStream.fail())
	{
		cout << "<Error Output File \"output.txt\" Was Not Found>\n";
		exit(1);
	}

	
	//This loop takes the integer values from a file and stores it into the integer
	//variable "input" and the loop runs as long as there are data values within the input stream file.
	while (inStream >> input)
	{
		//Prints to the console
		product = input * input;
		sum = sum + input;
		cout << input
			<< "\t"
			<< product
			<< "\t"
			<< sum
			<< endl;

		//Prints to the output file
		outStream << input
			<< "\t"
			<< product
			<< "\t"
			<< sum
			<< endl;
	}

	
}