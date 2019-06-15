#pragma once
#include<iostream>
#include<vector>
#include<cstring>
class BNode
{
public:
	BNode();
	BNode(BNode* L);
	~BNode();
	int getSize();
	bool clear();
	void insert(int);
	void insert(BNode*);
	void setParent(BNode*);
	void setLeaf();
	bool isLeaf();
	BNode* parent();
	BNode* nearNode();
	int midKey(BNode*);
	int lastvalue();
	void print();
	bool contain(int);
	// Node size

	// If node is leaf
	bool leaf;

	BNode* fa;
	// Node keys
	std::vector<int> keys;
	// Node pointers
	std::vector<BNode*>ptrs;
	BNode* nex;
private:
};

