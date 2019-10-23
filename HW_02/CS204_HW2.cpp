//semihbalki - 19010
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "linkedlist.h"
using namespace std;

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
		cout << "Unable to open file " << filename << ".txt" << endl;
		cout << "Please enter a different file name." << endl;
		cin >> filename;
		input.open(filename.c_str());
	}
	cout << "Successfully opened file " << filename << endl;

	cout << "###############################" << endl;
	cout << "Qualifying Laps: " << endl;
	cout << "###############################" << endl;

	string line, name;
	int lap_time;
	while (getline(input, line))
	{
		stringstream ss(line);
		ss >> name >> lap_time;
		list.sort(name, lap_time);
		cout << name << " completed the lap in " << lap_time << " milliseconds" << endl;
		list.personal_best(name);
	}
	list.print();
	return 0;
}