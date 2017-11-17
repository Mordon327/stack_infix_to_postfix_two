#include "Stack.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
using namespace std;

const char LEFTPARAN = '(';
const char RIGHTPARAN = ')';
const char TIMES = '*';
const char DIVIDE = '/';
const char ADD = '+';
const char SUBTRACT = '-';
const int TWO = 2;
const char SPACE = ' ';
int main()
{
		string inputFileName = "tests.txt";
		//string outputFileName = "output.txt";
		ifstream in;
		string dataInput;
		stack<char> symbols;
		//string infix;
		//string postfix;
		in.open(inputFileName);
		if (in.fail())
		{
			cerr << "Couldn't open file.";
			system("Pause");
			exit(0);
		}
		//keep track of iterations for error line
		int j = 0;
		
		//while the file isn't over
		while (in && in.peek() != EOF)
		{
			j++;
			int i = 0;
			getline(in, dataInput);
			//cout what getline got
			//cout << dataInput << endl;
			string postfix = "";

			//the big loop that does the arithmatic
			do
			{
				//get everything to compare
				char compare;
				compare = dataInput[i];
				string comp = "";
				comp += compare;

				//if it is a space, skip everything
				if (compare == SPACE)
				{
					i++;
				}
				//if it is a symbole, push it.
				else if (compare == LEFTPARAN || compare == TIMES || compare == DIVIDE || compare == ADD || compare == SUBTRACT/*the next input is a left parenthesis*/)
				{
					symbols.push(dataInput[i]);
					i++;
					//if there is a number following the symbole then print it and pop the symbole.
					if (compare == TIMES || compare == DIVIDE)
					{
						//if it is a number greater than nine.
						if (isdigit(dataInput[i + 1]) && !RIGHTPARAN)
						{
							if (isdigit(dataInput[i + 1]))
							{
								string print = "";
								print = dataInput[i + 1];
								print += dataInput[i + TWO];
								cout << stoi(print) << ' ' << compare << ' ';
								postfix += print;
								//postfix += SPACE;
								postfix += compare;
								postfix += SPACE;
								i += 3;
								symbols.pop();
							}
							else
							{
								cout << dataInput[i] << ' ' << dataInput[i + 1] << ' ' << compare << ' ';
								postfix += dataInput[i];
								postfix += SPACE;
								postfix += dataInput[i + 1];
								postfix += SPACE;
								postfix += symbols.top();
								postfix += SPACE;
								i++;
								symbols.pop();
							}
						}
					}
				}
				//if it is a number then print it.
				else if (isdigit(dataInput[i]))/*the next input is a number or other operand*/
				{
					//if the number is larger than nine.
					if (isdigit(dataInput[i + 1]))
					{
						//read the operand and write it to the output
						string print = "";
						print = dataInput[i];
						print += dataInput[i + 1];
						cout << stoi (print) << ' ';
						postfix += print;
						postfix += SPACE;
						i += TWO;
					}
					else
					{
						cout << stoi(comp) << ' ';
						postfix += comp;
						postfix += SPACE;
						i++;
					}
				}
				//if all else fails it's probably a right parenthasis.
				else
				{
					//keep up with the count or suffer the consequences of infinite loops...
					i++;
					//make sure there is something.  Don't need another stupid out of bounds errors.
						if (symbols.isEmpty() == false)
						{
							//checking the top of the stack for what is there.
							char topper = symbols.top();

							//if the top of the stack is a parenthasis.
							while (topper != LEFTPARAN)
							{
								symbols.pop();
								//Opperator precidence
								if (topper == TIMES || topper == DIVIDE)
								{
									cout << topper << ' ';
									postfix += topper;
									postfix += SPACE;
								}
								else
								{
									char temp = symbols.top();
									if (temp == TIMES || temp == DIVIDE)
									{
										cout << temp << ' ';
										postfix += temp;
										postfix += SPACE;
										symbols.pop();
										cout << topper << ' ';
										postfix += topper;
										postfix += SPACE;
									}
									else
									{
										cout << topper << ' ';
										postfix += topper;
										postfix += SPACE;
									}
								}
								//if the stack isn't empty then set the topper to see if it is a parenthasis.
								if (symbols.isEmpty() == false)
								{
									topper = symbols.top();
								}
								topper = symbols.top();
							}
							//if we find a parenthasis then kick it to the curb.
							symbols.pop();
						}

						//we got problems.
						else
						{
							cout << "Malformed expression on line " << j <<endl;
							system("Pause");
							exit(0);
						}
				}
				//we are stuck in here until we iterate over the entire line.
			} while (i < dataInput.length());
			
			/*Print and pop any remaining operations on the stack.
			(There should be no remaining left parentheses; if there are, the input expression did not have balanced parentheses.)*/
			if (symbols.isEmpty() == false)
			{
				while (symbols.isEmpty() == false)
				{
					char temp = symbols.top();
					if (temp != LEFTPARAN)
					{
						cout << temp << ' ';
						postfix += temp;
						postfix += SPACE;
					}
					symbols.pop();
				}
			}
			cout << endl << endl;
			cout << eval(postfix) << endl;
		}
		//close the file before it kills us...
	in.close();
	system("Pause");
}