#include<iostream>
#include<vector>
#include "BNode.h"
#include "BTree.h"
int main()
{
	//std::vector<int>a;
	BTree P;
	int val[] = { 4,3,2,1,5 };
	int n = sizeof(val) / sizeof(int);
	for (int i = 0; i < n; i++)P.insert(val[i], i);
	P.printAll();
	return 0;
}