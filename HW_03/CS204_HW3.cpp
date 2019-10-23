#include "linkedlist.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

void display()
{
	cout << "1. Annexation! War for the iron throne continues..." << endl;
	cout << "2. Tyrion must travel, do a path check for the famous imp." << endl;
	cout << "3. Exit" << endl;
}

int main()
{
	linkedlist list;
	ifstream input;
	string filename;
	cout << "Please enter a file name." << endl;
	cin >> filename;
	input.open(filename.c_str());
	while (input.fail())
	{
		cout << "Wrong filename! Please try again: " << endl;
		cin >> filename;
		input.open(filename.c_str());
	}
	cout << "Successfully opened file " << filename << ".txt" << endl;

	string line, hname, nname;
	cout << endl;
	cout << "######## TOPOLOGY ########" << endl << endl;
	while (getline(input, line))
	{
		istringstream ss(line);
		ss >> hname >> nname;
		cout << "Processing " << hname << ", " << nname << endl;
		if (list.nnExists(hname, nname) == false && list.nnExists(nname, hname) == false)
		{
			list.addHouseNode(hname);
			list.addHouseNode(nname);
			list.addNeighborNode(hname, nname);
			list.addNeighborNode(nname, hname);
			cout << "Topology information successfully added." << endl << endl;
		}
		else
		{
			cout << "Redundant information! An entry with " << hname << " and " << nname << " is already processed." << endl << endl;
		}
	}
	cout << endl;
	list.printAll();

	line = "";
	int num;
	cout << "Please select an option [1-2-3]" << endl;
	display();
	while (cin >> num)
	{
		if (num == 3)
		{
			list.deleteAll();
			cout << "List deleted and program ended." << endl;
			break;
		}
		else if (num != 1 && num != 2)
		{
			cout << "Invalid option please select from menu." << endl;
			cout << endl;
		}
		else if (num == 1)
		{
			cout << "Please enter two houses first the annexer and the annexed. (ex: Tyrell Stark)." << endl;
			cin >> hname >> nname;
			if (hname == nname)
			{
				cout << "A House cannot conquer itself!" << endl;
				cout << "Update failed." << endl;
				cout << endl;
			}
			else if (!list.hnExists(hname))
			{
				cout << hname << " does not exist!" << endl;
				cout << "Update failed." << endl;
				cout << endl;
			}
			else if (!list.hnExists(nname))
			{
				cout << nname << " does not exist!" << endl;
				cout << "Update failed." << endl;
				cout << endl;
			}
			else if (!list.nnExists(hname, nname))
			{
				cout << "A house can only conquer a neighboring house! " << nname << " is not a neighbor of " << hname << "." << endl;
				cout << "Update failed." << endl;
				cout << endl;
			}
			else
			{
				list.Annexation(hname, nname);
				cout << hname << " conquered " << nname << "!" << endl;
				cout << endl;
				list.printAll();
			}
		}
		else if (num == 2)
		{
			cout << "Please enter a path. (ex: Tyrell Martell Tully)" << endl;
			vector<string> hold;
			cin >> line;
			hold.push_back(line);
			getline(cin, line);
			istringstream ss(line);
			string name;
			int code1, code2, code3, code4;
			while (ss >> name)
			{
				hold.push_back(name);
			}
			for (int i=0; i < (hold.size() - 1); i++)
			{
				code1 = 0, code2 = 0, code3 = 0, code4 =0;
				if ((!list.nnExists(hold[i], hold[i + 1])) && (!list.hnExists(hold[i + 1])))
				{
					cout << hold[i + 1] << " is not a neighbor of " << hold[i] << endl;
					cout << "Path search failed." << endl;
					break;
				}
				if (hold[i] != hold[i + 1])
				{
					if (list.hnExists(hold[i]))
					{
						if (list.nnExists(hold[i], hold[i + 1]))
						{
							cout << "Path found between " << hold[i] << " and " << hold[i + 1] << endl;
							code1 = -1;
						}
						else
						{
							cout << hold[i + 1] << " is not a neighbor of " << hold[i] << endl;
							code2 = -1;
						}
					}
					else
					{
						cout << hold[i] << " does not exist in the map." << endl;
						code4 = -1;
					}
				}
				else
				{
					cout << "You are already in " << hold[i] << endl;
					code3 = -1;
				}
			}
			if (code1==-1 && code2==0 && code3==0)
			{
				cout << "Path search succeeded." << endl;
			}
			else if (code1 == 0 && (code2 == -1 || code3 == -1 || code4 == -1))
			{
				cout << "Path search failed!" << endl;
			}
			cout << endl;
		}
		cout << "Please select an option [1-2-3]" << endl;
		display();
	}

	return 0;
}