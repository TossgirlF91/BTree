#include<iostream>
#include<vector>
#include "BNode.h"
#include "BTree.h"
int main()
{
	//std::vector<int>a;
	BTree<std::string> P;
	std::string val[] = { "a","aba","aab","cba","ZZZ" };
	int n = 5;
	for (int i = 0; i < n; i++)
	{
		P.insert(val[i], i);
		P.printAll();
	}

	for (int i = 0; i < n; i++)
	{
		P.Delete(val[i], i);
		P.printAll();
	}
	return 0;
}