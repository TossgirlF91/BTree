#include<iostream>
#include<vector>
#include "BNode.h"
#include "BTree.h"
int main()
{
	//std::vector<int>a;
	BTree P;
	int val[] = { 4,3,2,1,5,6,7,8 };
	int n = sizeof(val) / sizeof(int);
	for (int i = 0; i < 15; i++)
	{
		P.insert(15 - i, i);
		P.printAll();
	}

	for (int i = 0; i < 15; i++)
	{
		P.Delete(15 - i, 0);
		P.printAll();
	}
	return 0;
}