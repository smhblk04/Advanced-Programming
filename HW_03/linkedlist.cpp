#include "linkedlist.h"
#include <string>
using namespace std;

linkedlist::linkedlist()
{
	head = nullptr;
}

void linkedlist::addHouseNode(string hname)
{
	if (!hnExists(hname))
	{
		if (head == nullptr)
		{
			houseNode* node = new houseNode(hname, nullptr, nullptr);
			head = node;
		}
		else
		{
			houseNode* ptr = head;
			while (ptr->next != nullptr)
			{
				ptr = ptr->next;
			}
			houseNode* node = new houseNode(hname, nullptr, nullptr);
			ptr->next = node;
		}
	}
}
void linkedlist::addNeighborNode(string hname, string nname)
{
	if (head->houseName == hname)//hname exists at the beginning
{
		if (head->neighborListHead == nullptr)
		{
			neighborNode* node = new neighborNode(nname, nullptr);
			head->neighborListHead = node;
		}
		else
		{
			if (!nnExists(hname, nname))
			{
				neighborNode* pt = head->neighborListHead;
				while (pt->next != nullptr)
				{
					pt = pt->next;
				}
				neighborNode *node = new neighborNode(nname, nullptr);
				pt->next = node;
			}
				
		}
	}
	else//hname does not exists
	{
		houseNode* ptr = head;
		if (!nnExists(hname, nname))
		{
			while (ptr != nullptr)
			{
				if (ptr->houseName == hname)
				{
					if (ptr->neighborListHead == nullptr)
					{
						neighborNode *node = new neighborNode(nname, nullptr);
						ptr->neighborListHead = node;
					}
					else
					{
						neighborNode* pt = ptr->neighborListHead;
						while (pt->next != nullptr)
						{
							pt = pt->next;
						}
						neighborNode *node = new neighborNode(nname, nullptr);
						pt->next = node;
					}
				}
				ptr = ptr->next;
			}
		}
	}
}

void linkedlist::Connection(string hname, string nname)
{
	houseNode* ptr = head;
	houseNode* ptr1 = head;
	neighborNode* pt = head->neighborListHead, *pt1 = head->neighborListHead;
	if (head == nullptr)
		cout << "List is empty" << endl;
	else
	{
		while (ptr->next != nullptr)
		{
			if (ptr->houseName == hname)
			{
				pt = ptr->neighborListHead;
				while (pt->next != nullptr)
				{
					pt = pt->next;//pt->next'i bagla
				}
				while (ptr1->next != nullptr)
				{
					if (ptr1->houseName == nname)
					{
						pt->next = ptr1->neighborListHead;
					}
					ptr1 = ptr1->next;
				}
			}
			ptr = ptr->next;
		}
	}
}

void linkedlist::del_hname(string hname)
{//from hname node
	houseNode* ptr = head;
	if (head == nullptr)
		cout << "Nothing to delete, list is empty" << endl;
	else
	{
		if (nnExists(hname, hname))
		{
			while (ptr->next != nullptr)
			{
				if (ptr->houseName == hname)
				{
					if (ptr->neighborListHead->neighborName == hname)
					{
						ptr->neighborListHead = ptr->next->neighborListHead;
					}
					else
					{
						neighborNode* pt = ptr->neighborListHead;
						while (pt->next != nullptr)
						{
							if (pt->next->neighborName == hname)
							{
								pt->next = pt->next->next;
								break;
							}
							pt = pt->next;
						}
					}
				}
				ptr = ptr->next;
			}
		}
		else
			return;
	}
}

void linkedlist::del_nname(string nname)
{
	//1.Kisim: nname housenode'unu silme
	if (head == nullptr)
	{
		cout << "Nothing to delete, there is no list" << endl;
	}
	else
	{
		houseNode* ptr = head;
		if (head->houseName == nname)
		{
			head = head->next;
		}
		else
		{
			while (ptr->next != nullptr)
			{
				if (ptr->next->houseName == nname)
				{
					ptr->next = ptr->next->next;
					break;
				}
				ptr = ptr->next;
			}
		}
	}
	//2.Kisim: nname housenode'unu her housenodeundan sil eger varsa
	houseNode* ptr = head;
	while (ptr != nullptr)
	{
		if (nnExists(ptr->houseName, nname))
		{
			if (ptr->neighborListHead->neighborName == nname)
			{
				ptr->neighborListHead = ptr->neighborListHead->next;
			}
			else
			{
				neighborNode* pt = ptr->neighborListHead;
				while (pt->next != nullptr)
				{
					if (pt->next->neighborName == nname)
					{
						pt->next = pt->next->next;
						break;
					}
					pt = pt->next;
				}
			}
		}
		ptr = ptr->next;
	}
}

void linkedlist::add_hname(string hname)
{
	if (head == nullptr)
	{
		cout << "Nothing to add, list is empty" << endl;
	}
	else
	{
		houseNode* ptr = head, *ptr1 = head;
		neighborNode* pt = ptr->neighborListHead;
		if (head->houseName == hname)
		{
			pt = ptr->neighborListHead;
			while (pt != nullptr)
			{
				if (pt->neighborName != hname)
				{
					if (!nnExists(pt->neighborName, hname))
					{
						houseNode* ptr = head;
						while (ptr != nullptr)
						{
							if (ptr->houseName == pt->neighborName)
							{
								neighborNode* node = new neighborNode(hname, ptr->neighborListHead);
								ptr->neighborListHead = node;
								break;
							}
							ptr = ptr->next;
						}
					}
					pt = pt->next;
				}
			}
		}
		else
		{
			ptr = head, ptr1 = head;
			pt = ptr->neighborListHead;
			while (ptr1 != nullptr)
			{
 				if (ptr1->houseName == hname)
				{
					neighborNode* pt = ptr1->neighborListHead;
					while (pt->next != nullptr)
					{
						if (pt->neighborName != hname)
						{
							if (!nnExists(pt->neighborName, hname))
							{
								houseNode* ptr = head;
								while (ptr != nullptr)
								{
									if (ptr->houseName == pt->neighborName)
									{
										neighborNode* node = new neighborNode(hname, ptr->neighborListHead);
										ptr->neighborListHead = node;
										break;
									}
									ptr = ptr->next;
								}
							}
						}
						pt = pt->next;
					}
				}
				ptr1 = ptr1->next;
			}
		}
	}
}

void linkedlist::remove_duplicate()
{
	houseNode* ptr = head;
	while (ptr != nullptr)
	{
		neighborNode* ptr1 = ptr->neighborListHead;
		neighborNode* ptr2 = ptr->neighborListHead;
		neighborNode* dup;
		while (ptr1 != NULL && ptr1->next != NULL)
		{
			ptr2 = ptr1;

			/* Compare the picked element with rest
			   of the elements */
			while (ptr2->next != NULL)
			{
				/* If duplicate then delete it */
				if (ptr1->neighborName == ptr2->next->neighborName)
				{
					/* sequence of steps is important here */
					dup = ptr2->next;
					ptr2->next = ptr2->next->next;
					delete(dup);
				}
				else /* This is tricky */
					ptr2 = ptr2->next;
			}
			ptr1 = ptr1->next;
		}
		ptr = ptr->next;
	}
}

void linkedlist::Annexation(string hname, string nname)
{
	Connection(hname, nname);
	del_hname(hname);
	del_nname(nname);
	add_hname(hname);
	remove_duplicate();
}

void linkedlist::printAll()
{
	cout << "######## MAP ########" << endl << endl;
	houseNode* ptr = head;
	neighborNode* pt;
	if (head == nullptr)
	{
		cout << "Nothing to print" << endl;
	}
	else
	{
		while (ptr != nullptr) 
		{
			cout << ptr->houseName << ": ";
			if (ptr->neighborListHead != nullptr)
			{
				pt = ptr->neighborListHead;
				while (pt != nullptr)
				{
					cout << pt->neighborName << ", ";
					pt = pt->next;
				}
				cout << endl;
			}
			ptr = ptr->next;
		}
	}
	cout << endl;
}
bool linkedlist::hnExists(string hname)//check whether housenode exists
{
	houseNode* ptr = head;
	if (head == nullptr)
		return false;
	else
	{
		while (ptr != nullptr)
		{
			if (ptr->houseName == hname)
			{
				return true;
			}
			ptr = ptr->next;
		}
	}
	return false;
}
bool linkedlist::nnExists(string hname, string nname)//check whether neighbornode exists
{
	houseNode* ptr = head;
	neighborNode *pt;
	if (head == nullptr)
		return false;
	else
	{
		while (ptr != nullptr)
		{
			if (ptr->houseName == hname)
			{
				pt = ptr->neighborListHead;
				while (pt != nullptr)
				{
					if (pt->neighborName == nname)
					{
						return true;
					}
					pt = pt->next;
				}
			}
			ptr = ptr->next;
		}
	}
	return false;
}

void linkedlist::deleteAll()
{
	if (head == nullptr)
	{
		cout << "Nothing to delete." << endl;
	}
	else
	{
		houseNode* ptr;
		while (head != nullptr)
		{
			ptr = head;
			head = head->next;
			delete ptr;
		}
	}
}