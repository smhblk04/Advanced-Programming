//Semih Balki - 19010 - CS204 HW1
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

bool check_cell_entry(string line);
void display_matrix(vector<vector<char>> matrix);
bool check_word(string word, string line, ifstream &input_d);
string word_found(vector<vector<char>> matrix, string path);
bool twice_check(vector<vector<char>> matrix, string path, int x, int y);
bool xandy_check(vector<vector<char>> matrix, int x, int y);
int path_check(vector<vector<char>> matrix, int x, int y, string path, vector<vector<int>> flags);

bool xandy_check(vector<vector<char>> matrix, int x, int y)
{
	if ((x > (matrix.size() - 1)) || (y > (matrix[0].size() - 1)) || x < 0 || y < 0)
	{
		return false;
	}
	return true;
}

int path_check(vector<vector<char>> matrix, int x, int y, string path, vector<vector<int>> flags)
{
	char c;
	int num = 1;
	if (path.length() <= 2)//In case of path length smaller than 2 and do not contain any RLUD input
	{
		/*for (int j = 0; j < path.length(); j++)
		{
			c = path[j];//14 8 17 0
			if ((c != 114) || (c != 108) || (c != 117) || (c != 100))
			{
				return -4;//non-RLUD input
			}
		}*/
		return -1;//Invalid path - path too short
	}
	for(int i=0; i < path.length(); i++)
	{
		if (path[i] == 'r')
		{
			y++;
		}
		else if (path[i] == 'l')
		{
			y--;
		}
		else if (path[i] == 'u')
		{
			x--;
		}
		else if (path[i] == 'd')
		{
			x++;
		}
		else if(path[i] != 'r' || path[i] != 'l' || path[i] != 'u' || path[i] != 'd')
		{
			return -4;//non-RLUD input
		}
		if (!xandy_check(matrix, x, y))
		{
			return -2;//out of range
		}
		if (flags[x][y] == 1)
		{
			return -3;//cell visited twice
		}
		flags[x][y] = num;
	}
	return -5;
}

bool twice_check(vector<vector<char>> matrix, string path, int x, int y)
{
	for (int i=0; i < path.length(); i++)
	{
		if (path[i] == 'r')
		{
			y++;
		}
		else if (path[i] == 'l')
		{
			y--;
		}
		else if (path[i] == 'u')
		{
			x--;
		}
		else if (path[i] == 'd')
		{
			x++;
		}
		if (matrix[x][y] == '_')
		{
			return false;
		}
	}
	return true;
}

string word_found(vector<vector<char>> matrix, string path, int x, int y)
{
	string sum = "";
	sum += matrix[x][y];
	for (int i = 0; i < path.length(); i++)
	{
		if (path[i] == 'r')
		{
			y++;
			sum += matrix[x][y];
		}
		else if (path[i] == 'l')
		{
			y--;
			sum += matrix[x][y];
		}
		else if (path[i] == 'u')
		{
			x--;
			sum += matrix[x][y];
		}
		else if (path[i] == 'd')
		{
			x++;
			sum += matrix[x][y];
		}
	}
	return sum;
}

bool check_word(string word, string line, ifstream &input_d)
{
	input_d.clear();
	while (getline(input_d, line))
	{
		//istringstream ss(line);
		if (word == line)
		{
			return true;
		}
	}
	return false;
}

void display_matrix(vector<vector<char>> matrix)
{
	for (int i=0; i < matrix.size(); i++)
	{
		for (int j=0; j < matrix[0].size(); j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

bool check_cell_entry(string line)//check cell entry
{
	for (int i=0; i < line.length(); i++)
	{
		if (97 <= line[i] && line[i] <= 122)//Lowercase chars from ascii
		{
			if (i+1 <= line.length())
			{
				if (97 <= line[i + 1] && line[i + 1] <= 122)
				{
					return false;
				}
			}
		}
	}
	return true;
}

int main() {
	ifstream input_p, input_d;
	string p_filename, d_filename;

	cout << "Please enter the name of the puzzle file: ";
	cin >> p_filename;
	cout << endl;
	input_p.open(p_filename.c_str());
	while (input_p.fail()) {
		cout << "File could not be opened." << endl << endl;
		cout << "Please enter the name of the puzzle file: ";
		cin >> p_filename;
		cout << endl;
		input_p.open(p_filename.c_str());
	}

	char c;
	string line;
	vector<vector<char>> matrix;
	vector<vector<int>> flags;
	vector<char> vec;
	istringstream ss;
	//input_p.clear();
	input_p.seekg(0);
	vector<int> sizes, checks;//number of elements in each row
	int num = 0;
	while (!input_p.eof())//!input.eof()
	{
		getline(input_p, line);
		istringstream ss(line);

		if (!vec.empty())
			vec.clear();

		if (!checks.empty())
			checks.clear();

		if (line != "") {
			//check cell entry fonksiyonunu burada kullan
			if (check_cell_entry(line))
			{
				while (ss >> c) {
					if (c != ' ' || c != '\t') {
						if (97 <= c && c <= 122)//Lowercase chars from ascii
						{
							vec.push_back(c);
							checks.push_back(num);
						}
						else //if (65 <= c && c <= 90)//Upperscase chars from ascii
						{
							cout << "Invalid matrix - char not lowercase letter" << endl << endl;
							return 0;
						}
					}
				}
			}
			else
			{
				cout << "Invalid matrix - cell entry is not a char" << endl << endl;
				return 0;
			}
		}
		ss.clear();
		sizes.push_back(vec.size());
		matrix.push_back(vec);
		flags.push_back(checks);
	}

	//Check whether the dimensions holds
	int sum = 0;
	for (int i = 0; i < sizes.size(); i++)
	{
		sum += sizes[i];
	}
	if (sum / sizes.size() != sizes[0])//Total number of cells / row number of the matrix ?= number of cells in the first row
	{
		cout << "Invalid matrix - inconsistent dimensions" << endl << endl;
		return 0;
	}

	cout << "Please enter the name of the dictionary file: ";
	cin >> d_filename;
	cout << endl;
	input_d.open(d_filename.c_str());
	while (input_d.fail()) {
		cout << "File could not be opened." << endl << endl;
		cout << "Please enter the name of the dictionary file: ";
		cin >> d_filename;
		cout << endl;
		input_d.open(d_filename.c_str());
	}

	line = "";

	display_matrix(matrix);
	cout << endl;

	int found = 0;
	int size_of_matrix = matrix.size() * matrix[0].size();
	int x, y;
	vector<char> store;//Storing the founded vectors
	string path;
	int reward_point = 0;
	int error;
	string word;
	while (found != size_of_matrix)//When all letters in the matrix are used
	{
		cout << "Enter the starting location for word (x, y): ";
		cin >> x >> y;
		cout << endl;
		if (x == -1 || y == -1) {
			if (found != size_of_matrix)
			{
				cout << "You didn't completely solve the puzzle." << endl << endl;
				cout << "Your final score is " << reward_point << endl << endl;
				return 0;
			}
		}
		while (!xandy_check(matrix, x, y))
		{
			cout << "Invalid coordinate - out of range" << endl << endl;
			display_matrix(matrix);
			cout << endl;
			cout << "Enter the starting location for word (x, y): ";
			cin >> x >> y;
			cout << endl;
		}

		cout << "Enter the path: ";
		cin >> path;
		cout << endl;

		error = path_check(matrix, x, y, path, flags);
		if (error == -1)
		{
			cout << "Invalid path - path too short" << endl << endl;
			display_matrix(matrix);
			cout << endl;
		}
		else if (error == -2)
		{
			cout << "Invalid path - out of range" << endl << endl;
			display_matrix(matrix);
			cout << endl;
		}
		else if(error == -3)
		{
			cout << "Invalid path - cell visited twice" << endl << endl;
			display_matrix(matrix);
			cout << endl;
		}
		else if (error == -4)
		{
			cout << "Invalid path - non-RLUD input" << endl << endl;
			display_matrix(matrix);
			cout << endl;
		}
		else if (error == -5)//No error
		{
			if (twice_check(matrix, path, x, y))//path ile gidilen kelime anlamliysa kismini ekle fonksiyona ondan sonra matriks'te _ ile goster
			{
				word = word_found(matrix, path, x, y);
				input_d.clear();
				input_d.seekg(0);
				if (check_word(word, line, input_d))
				{
					matrix[x][y] = '_';
					found += word.length();
					reward_point += word.length() * word.length();
					for (int i = 0; i < path.length(); i++)
					{
						if (path[i] == 'r')
						{
							y++;
						}
						else if (path[i] == 'l')
						{
							y--;
						}
						else if (path[i] == 'u')
						{
							x--;
						}
						else if (path[i] == 'd')
						{
							x++;
						}
						matrix[x][y] = '_';
					}
					cout << "Word found: " << word << endl << endl;
					cout << "Word length: " << word.length() << endl << endl;
					cout << "Points gained: " << word.length() * word.length() << endl << endl;
					cout << "Current score: " << reward_point << endl << endl;
					display_matrix(matrix);
					cout << endl;
				}
				else
				{
					cout << "Invalid word - non-existent word " << word << endl << endl;
					display_matrix(matrix);
					cout << endl;
				}
			}
			else
			{
				cout << "Invalid path - cell visited previously" << endl << endl;
				display_matrix(matrix);
				cout << endl;
			}
		}
		else
		{
			cout << "Unknown error." << endl << endl;
		}
	}

	if (found == size_of_matrix)
	{
		cout << "Congratulations, you have solved the puzzle perfectly!" << endl << endl;
		cout << "Your final score is: " << reward_point << endl << endl;
	}

	return 0;
}