#include "BTree.h"

bool BTree::insert(int _key, int _id)
{
	link val = std::make_pair(_key, _id);
	if (isEmpty)
	{
		BNode* L = new BNode;
		L->clear();
		L->setLeaf();
		L->insert(val);
		isEmpty = 0;
		root = L;
	}
	else
	{
		BNode* L = find(root, val);
		if (L->contain(val))
		{
			return false;
		}
		if (L->getSize() < N - 1)
		{
			insert_in_leaf(L, val);
		}
		else
		{
			BNode* G = new BNode;
			BNode* Tmp = new BNode(L);
			insert_in_leaf(Tmp, val);
			L->clear();
			G->setLeaf();
			G->nex = L->nex;
			L->nex = G;
			G->setParent(L->parent());
			int SIZE = N;
			int mid = SIZE / 2;
			for (int i = 0; i < mid; i++)L->insert(Tmp->keys[i]);
			for (int i = mid; i < SIZE; i++)G->insert(Tmp->keys[i]);

			link Minkey = G->keys[0];

			delete Tmp;
			insert_in_parent(L, Minkey, G);
		}
	}

	return true;
}
BNode* BTree::find(BNode* node, link  key)
{
	if (node->isLeaf())return node;

	BNode* child = NULL;
	int SIZE = node->getSize();

	for (int i = 0; i < SIZE; i++)
		if (key < node->keys[i]) { child = node->ptrs[i]; break; }
	if (child == NULL)
	{
		child = node->ptrs[SIZE];
	}
	return find(child, key);
}
bool BTree::insert_in_leaf(BNode* L, link key)
{
	int SIZE = L->getSize();
	int pos = -1;
	for (int i = 0; i < SIZE; i++)
		if (L->keys[i] > key) { pos = i; break; }
	if (pos == -1)pos = SIZE;
	L->keys.insert(L->keys.begin() + pos, key);
	return true;
}
bool BTree::insert_in_parent(BNode* L, link key, BNode* G)
{

	if (L == root)
	{
		BNode* P = new BNode;
		P->clear();
		P->insert(key);
		P->insert(L);
		P->insert(G);
		L->setParent(P);
		G->setParent(P);
		root = P;
	}
	else
	{
		BNode* P = L->parent();

		if (P->getSize() < N)
		{
			G->setParent(P);
			int SIZE = P->getSize();
			int pos = -1;
			for (int i = 0; i <= SIZE; i++)
				if (P->ptrs[i] == L) { pos = i; break; }
			if (pos == -1)
			{
				printf("Error insert parent find P->child==L\n");
				exit(0);
			}
			P->ptrs.insert(P->ptrs.begin() + pos + 1, G);
			P->keys.insert(P->keys.begin() + pos, key);
		}
		else
		{
			G->setParent(P);
			BNode* Tmp = new BNode(P);
			int SIZE = Tmp->getSize();
			int pos = -1;
			for (int i = 0; i <= SIZE; i++)
				if (Tmp->ptrs[i] == L) { pos = i; break; }
			if (pos == -1)
			{
				printf("Error insert parent find Tmp->child==L\n");
				exit(0);
			}
			Tmp->ptrs.insert(Tmp->ptrs.begin() + pos + 1, G);
			Tmp->keys.insert(Tmp->keys.begin() + pos, key);
			SIZE++;
			BNode* H = new BNode();
			H->clear();
			P->clear();
			H->setParent(P->parent());

			int mid = SIZE / 2;
			for (int i = 0; i < mid; i++)P->insert(Tmp->keys[i]);
			for (int i = 0; i <= mid; i++)
			{
				P->insert(Tmp->ptrs[i]);
				Tmp->ptrs[i]->setParent(P);
			}

			link Minkey = Tmp->keys[mid];
			for (int i = mid + 1; i < SIZE; i++)H->insert(Tmp->keys[i]);
			for (int i = mid + 1; i <= SIZE; i++)
			{
				H->insert(Tmp->ptrs[i]);
				Tmp->ptrs[i]->setParent(H);
			}

			insert_in_parent(P, Minkey, H);
		}
	}
	return true;
}
bool BTree::Delete(int _key, int _id)
{
	link val = std::make_pair(_key, _id);
	BNode* L = find(root, val);
	if (!L->contain(val))
	{
		return false;
	}
	delete_entry(L, val);
	return true;
}
bool BTree::swap_node(BNode** p1, BNode** p2)
{
	BNode* p3 = *p1;
	*p1 = *p2;
	*p2 = p3;
	return true;
}
bool BTree::delete_key(BNode* L, link key, int off)
{
	auto it = L->keys.begin();
	int pos = -1;
	for (int i = 0; it != L->keys.end(); i++)
	{
		if (*it == key)
		{
			it = L->keys.erase(it);
			pos = i;
		}
		else ++it;
	}
	if (pos == -1)
	{
		printf("Error in delete key\n");
		exit(0);
	}
	if (!L->isLeaf())
	{
		BNode* tr = L->ptrs[pos + off];
		auto it2 = L->ptrs.begin();
		for (; it2 != L->ptrs.end();)
		{
			if (*it2 == tr)
			{
				it2 = L->ptrs.erase(it2);
			}
			else ++it2;
		}
	}
	return (pos != -1);
}
bool BTree::delete_entry(BNode* L, link key)
{
	delete_key(L, key, 1);
	if (root == L)
	{
		if (L->getSize() == 0)
		{
			if (L->ptrs.size() > 0)
			{
				BNode* G = L->ptrs[0];
				root = G;
				G->fa = NULL;
			}
			else
			{
				root = NULL;
			}
			delete(L);
		}
	}
	else if (L->getSize() < (N / 2))
	{
		BNode* G = L->nearNode();

		link Midkey = L->midKey(G);

		bool tag_pre = (G->keys[0] < L->keys[0]);
		if (G->getSize() + L->getSize() < N)
		{

			if (tag_pre)swap_node(&G, &L), tag_pre = 0;



			if (L->isLeaf())
			{
				int SIZE = G->keys.size();
				for (int i = 0; i < SIZE; i++)L->insert(G->keys[i]);
			}
			else
			{
				int SIZE = G->keys.size();
				L->insert(Midkey);
				for (int i = 0; i < SIZE; i++)L->insert(G->keys[i]);
				for (int i = 0; i <= SIZE; i++)
				{
					L->insert(G->ptrs[i]);
					G->ptrs[i]->setParent(L);
				}
			}

			delete_entry(L->parent(), Midkey);
			delete G;
		}
		else
		{
			if (tag_pre)// G L
			{
				if (L->isLeaf())
				{
					int SIZE = G->getSize();
					link stv, edv;
					stv = L->keys[0];
					edv = G->keys[SIZE - 1];
					L->keys.insert(L->keys.begin(), edv);
					delete_key(G, edv, 0);
					replace(L->parent(), stv, edv);
				}
				else
				{
					int SIZE = G->getSize();
					link edv;
					edv = G->keys[SIZE - 1];
					BNode* ntr = G->ptrs[SIZE];
					L->keys.insert(L->keys.begin(), Midkey);
					L->ptrs.insert(L->ptrs.begin(), ntr);
					ntr->setParent(L);
					delete_key(G, edv, 1);

					replace(L->parent(), Midkey, edv);
				}
			}
			else// L G
			{
				if (L->isLeaf())
				{
					int SIZE = G->getSize();
					link stv, edv;
					stv = G->keys[0];
					edv = G->keys[1];
					L->keys.push_back(stv);
					delete_key(G, stv, 0);

					replace(L->parent(), stv, edv);
				}
				else
				{
					int SIZE = G->getSize();
					link edv;
					edv = G->keys[0];
					BNode* ntr = G->ptrs[0];
					L->keys.push_back(Midkey);
					L->ptrs.push_back(ntr);
					ntr->setParent(L);

					delete_key(G, edv, 0);

					replace(L->parent(), Midkey, edv);
				}
			}
		}

	}
	return true;
}
bool BTree::replace(BNode* L, link stv, link edv)
{
	int SIZE = L->getSize();
	bool tag = 0;
	for (int i = 0; i < SIZE; i++)
		if (L->keys[i] == stv)
		{
			L->keys[i] = edv;
			tag = 1; break;
		}
	return tag;
}
int BTree::ask(int key)
{
	link val = std::make_pair(key, INF);

	BNode* L = find(root, val);
	int SIZE = L->getSize();
	int ID = -1;
	for (int i = 0; i < SIZE; i++)
		if (L->keys[i].first == key)
		{
			ID = L->keys[i].second;
		}
	return ID;
}
void BTree::printAll()
{
	printf("Print B+ tree:\n");
	std::deque<BNode*>hh;
	hh.clear();
	if (root != NULL)hh.push_back(root);
	while (!hh.empty())
	{
		BNode* L = hh.front();
		hh.pop_front();
		int SIZE = L->getSize();
		for (int i = 0; i < SIZE; i++)printf("%d ", L->keys[i].first);
		if (!L->isLeaf())
		{
			if (L->ptrs.size() != SIZE + 1)
			{
				printf("Error\n");
				exit(0);
			}
			for (int i = 0; i <= SIZE; i++)
			{
				hh.push_back(L->ptrs[i]);
				if (L->ptrs[i]->parent() != L)
				{
					printf("Error printALL %d \n", i);

					exit(0);
					L->ptrs[i]->print();
					L->ptrs[i]->parent()->print();
				}
			}

		}
		else
		{
			printf("  ids:");
			for (int i = 0; i < SIZE; i++)
			{
				printf("%d ", L->keys[i].second);
			}

		}
		printf("\n");
	}
}