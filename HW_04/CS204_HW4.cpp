//Semih Balki - 19010
#include <iostream>
#include "DynIntStack.h"
#include <fstream>
#include <string>
using namespace std;
int keyword_search(string line);
void keyword_display(int num);

int keyword_search(string line)
{
	if (line.find("if") != std::string::npos)
	{
		return -1;
	}
	else if (line.find("while") != std::string::npos)
	{
		return -2;
	}
	else if (line.find("elif") != std::string::npos)
	{
		return -3;
	}
	else if (line.find("for") != std::string::npos)
	{
		return -4;
	}
	else if (line.find("else") != std::string::npos)
	{
		return -5;
	}
	return 0;
}

void keyword_display(int num)
{
	if (num == -1)
	{
		cout << "Keyword if found on this line." << endl;//if
	}
	if (num == -2)
	{
		cout << "Keyword while found on this line." << endl;
	}
	if (num == -3)
	{
		cout << "Keyword elif found on this line." << endl;
	}
	if (num == -4)
	{
		cout << "Keyword for found on this line." << endl;
	}
	if (num == -5)
	{
		cout << "Keyword else found on this line." << endl;
	}
}

int main()
{
	int current_level = 0;
	int error;
	DynIntStack stack;
	ifstream input;
	string filename;
	cout << "Please enter the file name that is going to be analyzed." << endl;
	cin >> filename;
	input.open(filename.c_str());
	while (input.fail())
	{
		cout << "Unable to open file please enter a different file name." << endl;
		cin >> filename;
		input.open(filename.c_str());
	}
	cout << "Starting file analysis..." << endl;
	cout << "Initial indentation level is pushed to the stack as 0." << endl;
	cout << endl;
	stack.push(0);

	string line;
	int count = 1;
	int space_count = 0;
	int keyword_observed_prev = 0;
	while (!input.eof())
	{
		space_count = 0;
		error = 0;
		getline(input, line);
		cout << "Line number: " << count << endl;
		cout << "Line: " << line << endl;
		if (line[0] == ' ')
		{
			for (int i = 0; i < line.length(); i++)
			{
				if (line[i] == ' ')
				{
					space_count++;
					if ((i+1) < line.length())
					{
						if (line[i + 1] != ' ')
						{
							break;
						}
					}
				}
			}
		}
		else
		{
			space_count = 0;
		}
		count++;

		cout << space_count << " number of spaces observed before the start of the line." << endl;
		stack.pop(current_level);
		if(keyword_observed_prev != 0)
		{
			cout << "This line proceeds a keyword containing line." << endl;
		}
		cout << "Current Level = " << current_level << " This line = " << space_count << endl;
		stack.push(current_level);

		int keyword_found = keyword_search(line);
		if (current_level < space_count && keyword_observed_prev != 0)
		{
			cout << "Line correct. Depth " << space_count << " added to the stack." << endl;
			stack.push(space_count);
		}
		else if (current_level >= space_count && keyword_observed_prev != 0)
		{
			cout << "Incorrect file structure." << endl;
			cout << "Current line must be greater than the Current indentation level." << endl;
			cout << "Stopping file analysis..." << endl;
			error = -1;
			break;
		}
		else if (current_level > space_count && keyword_observed_prev == 0)
		{
			int levels;
			int i = 0;
			cout << "Current line is smaller than Current indentation level; checking if line belongs to outer indentation." << endl;
			while (!stack.isEmpty())
			{
				stack.pop(levels);
				if (levels == space_count)
				{
					cout << "Current Level = " << levels << " This line = " << space_count << endl;
					cout << "Line belongs to outer block." << endl;
					stack.push(levels);
					break;
				}
				else
				{
					if (i != 0 && !stack.isEmpty())
					{
						cout << "Current Level = " << levels << " This line = " << space_count << endl;
						cout << "Current line is smaller than Current indentation level; checking if line belongs to outer indentation." << endl;
					}
					if (stack.isEmpty())
					{
						cout << "Incorrect file structure." << endl; 
						cout << "An indentation level same as the Current line is not found in outer blocks." << endl;
						cout << "Stopping file analysis." << endl;
						error = -3;
						break;
					}
				}
				i++;

			}
		}
		else if (current_level < space_count && keyword_observed_prev == 0)
		{
			cout << "Incorrect file structure." << endl;
			cout << "Current line cannot be greater than the Current indentation level." << endl;
			cout << "Stopping file analysis..." << endl;
			error = -2;
			break;
		}
		else if (current_level == space_count && keyword_observed_prev == 0)
		{
			cout << "Line belongs to current block" << endl;
		}
		keyword_observed_prev = keyword_found;
		keyword_display(keyword_found);
		cout << endl;
	}
	if (error == 0)
	{
		cout << "Finished file analysis. File structure is correct!";
	}
	int num;

	cout << endl;
	cout << "Stack emptied and program ending." << endl;

	while (!stack.isEmpty())//Deleting all the nodes 
	{
		stack.pop(num);
	}
	return 0;
}