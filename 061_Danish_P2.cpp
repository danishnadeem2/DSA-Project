#include<iostream>
#include<vector>
#include<cmath>
#include<list>
#include<ctime>
#include<unordered_set>

using namespace std;

int Hashfunction(int key, int table_size)
{
	return key % table_size;
}

// liner probing
class HashTable
{
public:
	vector<int> data;
	int size;

	HashTable(int s)
	{
		size = s;
		data = vector<int>(s, -1);
	}

	void Insertion(int val)
	{
		int index = Hashfunction(val, size);

		while (data[index] != -1)
		{
			index = (index + 1) % size;
		}

		data[index] = val;

		cout << val << "Inserted at index " << index << "in linear probing." << endl;
	}

	int search(int val)
	{
		int index2 = Hashfunction(val, size);
		int search = 1;

		while (data[index2] != -1)
		{
			index2 = (index2 + 1) % size;
			search++;
		}

		return search;
	}
};

class Linklist
{
public:
	vector<list<int>>nData;
	int size;

	Linklist(int s)
	{
		size = s;
		nData = vector<list<int>>(s);
	}

	void llInsertion(int val)
	{
		int index3 = Hashfunction(val, size);
		nData[index3].push_back(val);

		cout << val << "Inserted at index: " << index3 << " in link list." << endl;
	}

	int llSearching(int val)
	{
		int index4 = Hashfunction(val, size);
		int search = 1;

		for (int key : nData[index4])
		{
			if (key == val)
			{
				break;
			}

			search++;
		}

		return search;
	}
};


class BSTNode
{
public:
	int val;
	BSTNode* left;
	BSTNode* right;
	vector<BSTNode*> mData;
	int size;

	BSTNode(int v, int s)
	{
		val = v;
		left = nullptr;
		right = nullptr;
		size = s;
		mData = vector<BSTNode*>(s, nullptr);
	}
	
	void BSTInsertion(int val)
	{
		int index5 = Hashfunction(val, size);
		if (!mData[index5])
		{
			mData[index5] = new BSTNode(val, size);

		}
		else
		{
			BSTNode* crnt = mData[index5];
			while (true)
			{
				if (val < crnt->val)
				{
					if (crnt->left == nullptr)
					{
						crnt->left = new BSTNode(val, size);
					}

					else
					{
						crnt = crnt->left;
					}
				}

				else
				{
					if (crnt->right == nullptr)
					{
						crnt->right = new BSTNode(val, size);
					}

					else
					{
						crnt = crnt->right;
					}
				}
			}
		}
		cout << val << "Inserted at index: " << index5 << " in BST." << endl;
	}

	int BSTSearch(int val)
	{
		int index6 = Hashfunction(val, size);
		int search = 1;

		BSTNode* ptr = mData[index6];

		while (ptr)
		{
			if (val == ptr->val)
			{
				break;
			}

			else if (val > ptr->val)
			{
				ptr = ptr->right;
			}

			else
			{
				ptr = ptr->left;
			}
			search++;
		}
		return search;
	}
}; 
int main()
{
	const int table_size = 1019;
	HashTable ht(table_size);
	Linklist ll(table_size);
	BSTNode bst(0, table_size);

	unordered_set<int>genratedvl;

	srand(time(0));

	for (int a = 0; a < 1000; a++)
	{
		int randompn;
		do
		{
			randompn = rand() % (table_size - 1) + 2;
		} while (!genratedvl.insert(randompn).second);

		ht.Insertion(randompn);
		ll.llInsertion(randompn);
		bst.BSTInsertion(randompn);
	}

	for (int b = 0; b < 1000; b++)
	{
		int randomen;
		do
		{
			randomen = rand() % (table_size - 1) + 2;
		} while (genratedvl.insert(randomen).second);

		ht.Insertion(randomen);
		ll.llInsertion(randomen);
		bst.BSTInsertion(randomen);

	}

	for (int c = 0; c < 1000; c++)
	{
		int randomon;
		do
		{
			randomon = rand() % (table_size - 1) + 2;
		} while (!genratedvl.insert(randomon).second);

		ht.Insertion(randomon);
		ll.llInsertion(randomon);
		bst.BSTInsertion(randomon);
	}

	
	int searchlinear = 0;
	int llsearch = 0;
	int bstsearch = 0;

	for (int d = 0; d < 100; d++)
	{
		int randomval = rand() % 1000 + 1;
		searchlinear += ht.search(randomval);
		llsearch += ll.llSearching(randomval);
		bstsearch += bst.BSTSearch(randomval);
	}

	cout << "Avg Linear Search: " << searchlinear / 100 << "and Total search: " << searchlinear << endl;
	cout << "Avg Link List Search: " << llsearch / 100 << "and Total Search: " << llsearch << endl;
	cout << "Avg BST Search: " << bstsearch / 100 << "and Total Search: " << bstsearch << endl;

	return 0;
}