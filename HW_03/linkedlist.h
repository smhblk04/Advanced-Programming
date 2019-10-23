#include <string>
#include <iostream>
using namespace std;
#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

struct neighborNode
{
	string neighborName;
	neighborNode * next;

	neighborNode(string n = "", neighborNode *l = nullptr) :
		neighborName(n), next(l)
	{}
};

struct houseNode
{
	string houseName;
	neighborNode * neighborListHead;
	houseNode * next;

	houseNode(string nm = "", neighborNode *pt = nullptr, houseNode *p = nullptr) :
		houseName(nm), neighborListHead(pt), next(p)
	{}
};

class linkedlist
{
public:
	linkedlist();
	void addHouseNode(string hname);
	void addNeighborNode(string hname, string nname); 
	void printAll();
	bool hnExists(string hname);
	bool nnExists(string hname, string nname);
	void deleteAll(); //to deallocate all dynamic data //other member functions...
	void Annexation(string hname, string nname);
	void remove_duplicate();
	void Connection(string hname, string nname);//Make connection with the entered inputs
	void del_hname(string hname);//from hname node
	void del_nname(string nname);//from each node and itself as a housenode
	void add_hname(string hname);//add hname, which it have new neighbours
private:
	houseNode * head;
	// any helper functions you see necessary
};

#endif