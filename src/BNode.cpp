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
void BNode::insert(link key)
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
bool BNode::contain(link key)
{
	int tag = 0, SIZE = getSize();
	for (int i = 0; i < SIZE; i++)
		if (keys[i].first == key.first || keys[i].second == key.second)tag = 1;
	return tag;
}
int BNode::getSize()
{
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

link BNode::midKey(BNode* G)
{
	int SIZE = fa->getSize(), pos = -1;
	for (int i = 0; i < SIZE; i++)
		if (fa->ptrs[i] == G || fa->ptrs[i] == this) { pos = i; break; }
	link value = fa->keys[pos];
	return value;
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
	for (int i = 0; i < SIZE; i++)printf("%d ", keys[i].first);
	printf("\n\n");
}