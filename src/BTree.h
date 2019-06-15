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
	bool insert(int _key, int _id);
	bool insert_in_leaf(BNode*, int, int);
	BNode* find(BNode*, int);
	bool insert_in_parent(BNode*, int, BNode*);
	void printAll();
	bool Delete(int, int);
	bool delete_entry(BNode*, int);
	bool delete_key(BNode*, int, int);
	bool replace(BNode*, int, int);
	bool swap_node(BNode*, BNode*);

private:

	//Link* st;
	//BNode* st;
	//int* key;
	//int id;
	BNode* root;
	bool isEmpty;

};

