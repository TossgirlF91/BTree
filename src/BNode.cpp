#include "BNode.h"
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

BNode::BNode()
{
	keys.clear();
	ptrs.clear();
	leaf = 0;
}
BNode::BNode(BNode* L)
{
	leaf = L->leaf;
	keys.clear();
	ptrs.clear();
	for (int i = 0; i < L->keys.size(); i++)keys.push_back(L->keys[i]);
	for (int i = 0; i < L->ptrs.size(); i++)ptrs.push_back(L->ptrs[i]);
}
BNode::~BNode()
{

}
BNode* BNode::parent()
{
	return fa;
}
void BNode::insert(int key)
{
	keys.push_back(key);
}
void BNode::setParent(BNode* node)
{
	fa = node;
}
void BNode::setLeaf()
{
	leaf = 1;
	nex = NULL;
}
bool BNode::isLeaf()
{
	return leaf;
}
void BNode::insert(BNode* ntr)
{
	ptrs.push_back(ntr);
}
bool BNode::contain(int key)
{
	int tag = 0, SIZE = getSize();
	for (int i = 0; i < SIZE; i++)
		if (keys[i] == key)tag = 1;
	return tag;
}
int BNode::getSize()
{
	//return size;
	return keys.size();
}
bool BNode::clear()
{
	keys.clear();
	ptrs.clear();
	return true;
}
BNode* BNode::nearNode()
{
	int SIZE = fa->getSize(), pos = -1;
	BNode* p;
	for (int i = 0; i <= SIZE; i++)
		if (fa->ptrs[i] == this) { pos = i; break; }
	if (pos < SIZE)p = fa->ptrs[pos + 1];
	else p = fa->ptrs[pos - 1];
	return p;
}

int BNode::midKey(BNode* G)
{
	int SIZE = fa->getSize(), pos = -1;
	for (int i = 0; i < SIZE; i++)
		if (fa->ptrs[i] == G || fa->ptrs[i] == this) { pos = i; break; }
	int value = fa->keys[pos];
	return value;
}
int BNode::lastvalue()
{
	int SIZE = keys.size();
	return keys[SIZE];
}
void BNode::print()
{
	if (this == NULL)
	{
		printf("NULL point\n");
		return;
	}
	printf("Node:\n");
	int SIZE = getSize();
	for (int i = 0; i < SIZE; i++)printf("%d ", keys[i]);
	printf("\n\n");
}