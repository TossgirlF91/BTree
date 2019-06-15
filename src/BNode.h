#pragma once
#include<iostream>
#include<vector>
#include<cstring>
using link=std::pair<int, int>;
#define INF 0x7FFFFFFF
class BNode
{
public:
	BNode();
	BNode(BNode* L);
	~BNode();
	int getSize();
	bool clear();
	void insert(link);
	void insert(BNode*);
	void setParent(BNode*);
	void setLeaf();
	bool isLeaf();
	BNode* parent();
	BNode* nearNode();
	link midKey(BNode*);
	void print();
	bool contain(link);
	// Node size

	// If node is leaf
	bool leaf;

	BNode* fa;
	// Node keys
	std::vector<link> keys;
	// Node pointers
	std::vector<BNode*>ptrs;
	BNode* nex;
private:
};

