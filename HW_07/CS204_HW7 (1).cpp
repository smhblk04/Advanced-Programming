//Semih Balki - 19010
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <fstream>
#include <sstream>
#include <random>
#include <time.h>
#include <iomanip>
using namespace std;
//#define _VARIADIC_MAX 10//Because of no thread::thread no overloaded function takes 7 arguments
#define THREADS_NUM 5

int sum=0, index=0;
int size=0;
mutex Mutex;

int random_range(const int & min, const int & max) {
	static mt19937 generator(time(0));
	uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}

void sum_numbers(int *& arr, int & min, int & max, int i, struct tm *&ptm)
{
	while (index < size)
	{
		this_thread::sleep_for(chrono::seconds(random_range(min, max)));
		Mutex.lock();
		if (index < size)//To secure that index < size. If extract, the following if statement, arr[index] tries to access the non stored part since index may excess size.
		{
			time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
			localtime_s(ptm, &tt);
			cout << "Thread " << i << " added number index " << index << " to the total sum at " << put_time(ptm, "%X") << endl;
			sum += arr[index];
			cout << "Current sum: " << sum << endl;
			index++;
		}
		Mutex.unlock();
	}
}

int main()
{
	ifstream input;
	string filename;
	cout << "Please enter the file name." << endl;
	cin >> filename;
	input.open(filename.c_str());

	int min, max;
	cout << "Please enter the wait range of threads." << endl;
	cin >> min >> max;

	int num;
	input >> num;

	int * arr = new int[num];
	int count = 0;

	time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now());  //gets the current time
	struct tm *ptm = new struct tm;  //creating the time struct to be used in thread
	localtime_s(ptm, &tt);  //converting the time structures

	cout << "Starting reading the array at " << put_time(ptm, "%X") << endl;
	while (!input.eof())//LOADING THE ARRAY
	{
		input >> num;
		arr[size] = num;
		size++;
	}

	thread threads[THREADS_NUM];
	cout << "Array stored in the memory. Starting the summation at " << put_time(ptm, "%X") << endl;
	for (unsigned int i=0; i < THREADS_NUM; i++)//SUMMATION BEGINS
	{
		threads[i] = thread(&sum_numbers, ref(arr), ref(min), ref(max), i, ref(ptm));
	}

	for (unsigned int i = 0; i < THREADS_NUM; i++)
		threads[i].join();

	tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
	localtime_s(ptm, &tt);
	cout << "Adding finished at " << put_time(ptm, "%X") << endl;
	cout << "Sum: " << sum << endl;

	delete[] arr;//return back to heap memory

	return 0;
}