#pragma once
#include <vector>
#include <deque>
#include <string>
#include "BNode.h"
#define N 5
class BTree
{

public:
	BTree()
	{
		root = NULL;
		isEmpty = 1;
	}
	bool insert(int, int);
	bool insert_in_leaf(BNode*, link);
	BNode* find(BNode*, link);
	bool insert_in_parent(BNode*, link, BNode*);
	void printAll();
	bool Delete(int, int);
	bool delete_entry(BNode*, link);
	bool delete_key(BNode*, link, int);
	bool replace(BNode*, link, link);
	bool swap_node(BNode**, BNode**);
	int ask(int);

private:

	//Link* st;
	//BNode* st;
	//int* key;
	//int id;
	BNode* root;
	bool isEmpty;

};

