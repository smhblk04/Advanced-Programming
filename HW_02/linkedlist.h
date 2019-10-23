//semihbalki - 19010
#include <iostream>
#include <string>
using namespace std;
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

struct node
{
	string name;
	int lap_time;
	node *next;

	node()
	{}

	node(string nm, double num=0, node *nx=nullptr):
		name(nm), lap_time(num), next(nx)
	{}
};

class linkedlist
{
private:
	node *head;
public:
	linkedlist();
	void sort(string word, int time);
	~linkedlist();
	void print();
	void personal_best(string name);
};

void linkedlist::personal_best(string word)
{
	int position = 1;
	node *ptr = head;
	while (ptr != nullptr)
	{
		if (ptr->name == word)
		{
			cout << ptr->name << ": " << "current personal best is " << ptr->lap_time << "; " << "current position is " << position << endl;
			return;
		}
		ptr = ptr->next;
		position++;
	}
}

void linkedlist::sort(string word, int time)
{
	node* ptr = head;
	if (head != NULL)
	{
		if (head->name == word)
		{
			if (head->lap_time > time)
				head = head->next;
			else
				return;
		}
		node* prev = ptr;
		ptr = ptr->next;
		while (ptr != nullptr)
		{
			if (ptr->name == word)
			{
				if (ptr->lap_time > time)
				{
					prev->next = ptr->next;
					break;
				}
				else
				{
					return;
				}
			}
			ptr = ptr->next;
			prev = prev->next;
		}
		if (head->lap_time > time)
		{
			node* temp = new node(word, time, head);
			head = temp;
			return;
		}
		else if (head->lap_time == time)
		{
			node* temp = new node(word, time, head);
			head = temp;
			return;
		}
	}
	ptr = head;
	if (head == NULL)
	{
		head = new node(word, time, nullptr);
		return;
	}
	else
	{
		while (ptr != nullptr)
		{
			if (ptr->lap_time < time && ptr->next == nullptr)
			{
				node* temp = new node(word, time, nullptr);
				ptr->next = temp;
				return;
			}
			if (ptr->next != nullptr) {
				if (ptr->lap_time < time && ptr->next->lap_time > time)
				{
					node *temp = new node(word, time, ptr->next);
					ptr->next = temp;
					return;
				}
			}
			if (ptr->lap_time == time)
			{
				node *temp = new node(word, time, ptr->next);
				ptr->next = temp;
				return;
			}
			ptr = ptr->next;
		}
	}
}

linkedlist::linkedlist()
{
	head = NULL;
}

linkedlist::~linkedlist()
{//Linear
	node *ptr = head;
	if (head == nullptr)
	{
		cout << "Nothing to delete." << endl;
	}
	else
	{
		while (ptr != nullptr)
		{
			head = head->next;
			delete ptr;
			ptr = head;
		}
	}
}

void linkedlist::print()
{
	int count = 1;
	node *ptr = head;
	if (head == nullptr)
		cout << "Nothing to print." << endl;
	else
	{
		cout << "###############################" << endl;
		cout << "Results: " << endl;
		cout << "###############################" << endl;
		while (ptr != nullptr)
		{
			cout << count << ". " << ptr->name <<  " " << ptr->lap_time << endl;
			ptr = ptr->next;
			count++;
		}
	}
}
#endif