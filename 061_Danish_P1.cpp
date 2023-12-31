#include<iostream>
#include<cstdlib>
#include<ctime>
#include<sstream>
#include<vector>

using namespace std;

const int table_size = 1009;
const int data_size = 1000;
const int search_size = 100;

// IDcard structure
struct IDcard
{
	string ID;
	IDcard()
	{
		ID = "";
	}
};

// array for storing IDcard numbers
IDcard nData[table_size];

// Node structure for Link List
struct Node
{
	IDcard data;
	Node* next;

	Node(const IDcard& idata)
	{
		data = idata;
		next = nullptr;
	}
};

// linklist array
Node* Linklistdata[table_size];


// BST structure
struct BSTNode
{
	IDcard data;
	BSTNode* left;
	BSTNode* right;

	BSTNode(const IDcard& idata)
	{
		data = idata;
		left = nullptr;
		right = nullptr;
	}
};

// BST array
BSTNode* BSTdata[table_size];


// hashfunction
int Hashfunction(const string& id)
{
	int key1 = stoi(id.substr(0, 6));
	int key2 = stoi(id.substr(7, 7));
	long sum = key1 % table_size + key2 % table_size;


	int remainder1 = sum % table_size;
	return remainder1;
}


// linerprobbing function to insert data in array named as data 
void Insertion(const IDcard& idData)
{
	int index = Hashfunction(idData.ID);
	if (nData[index].ID.empty())
	{
		nData[index] = idData;
		cout << endl << "Inserted at Index: " << index << ": " << idData.ID << endl;
	}

	else
	{
		int index2 = index;
		index = (index + 1) % table_size;

		while (index != index2 && !nData[index].ID.empty())
		{
			index = (index + 1) % table_size;
		}

		if (index != index2)
		{

			nData[index] = idData;
			cout << endl << "Inserted at Index" << index << ": " << idData.ID << endl;
		}

		else
		{
			cout << "Table is full, no more data is posible to insert." << endl;
		}
	}
}

// linear search function for searching from array
bool search(const string searchid)
{
	int index1 = Hashfunction(searchid);

	while (!nData[index1].ID.empty() && nData[index1].ID != searchid)
	{
		index1 = (index1 + 1) % table_size;
	}
	return !nData[index1].ID.empty() && nData[index1].ID == searchid;
}

// linear deletion
void Delete(const string del)
{
	int index = Hashfunction(del);

	while (!nData[index].ID.empty() && nData[index].ID != del)
	{
		index = (index + 1) % table_size;
	}

	if (nData[index].ID == del)
	{
		nData[index].ID = "";
		cout << "Deleted ID: " << del << "at index: " << index << endl;
	}

	else
	{
		cout << "ID not found.";
	}
}

// display the stored data
void Display()
{
	cout << "Welcome to Nadra." << endl;
	cout << "Hash Table Contents: " << endl;
	for (int a = 0; a < table_size; a++)
	{
		if (nData[a].ID != "")
		{
			cout << endl << "[" << a << "]: " << nData[a].ID;
		}
	}

	cout << endl;
}

// Random function to genrate ID card numbers
IDcard genrateRandom()
{
	IDcard Idata;

	for (int b = 0; b < 5; b++)
	{
		Idata.ID += to_string(rand() % 10);
	}
	Idata.ID += "-";

	for (int c = 0; c < 7;c++)
	{
		Idata.ID += to_string(rand() % 10);
	}
	Idata.ID += "-";

	char randomchar = 'a' + rand() % 26;
	Idata.ID += randomchar;

	return Idata;
}


// comaprison function for linear probbing
void Comparison()
{

	string idTosearch;
	for (int d = 0; d < table_size; d++)
	{
		nData[d] = IDcard();
	}

	cout << endl;
	Display();
	int LinearProbbingCollisions = 0;

	idTosearch = genrateRandom().ID;

	for (int e = 0; e < data_size; e++)
	{
		IDcard Idata = genrateRandom();
		cout << endl << "ID: " << Idata.ID;
		int linearprobbingindex = Hashfunction(Idata.ID);

		if (!nData[linearprobbingindex].ID.empty())
		{
			LinearProbbingCollisions++;
			linearprobbingindex = (linearprobbingindex + 1) % table_size;
		}
		else
		{
			Insertion(Idata);
		}
	}

	cout << endl;
	Display();

	idTosearch = genrateRandom().ID;
	cout << "Genrate ID for searching: " << idTosearch << endl;
	int linearprobbingcomparison = 0;
	for (int f = 0; f < search_size; f++)
	{
		idTosearch = genrateRandom().ID;
		cout << "Searching for ID: " << idTosearch << endl;
		linearprobbingcomparison += search(idTosearch) ? (f + 1) : table_size;
	}

	double AvgCollsion = static_cast<double>(LinearProbbingCollisions) / data_size;
	double AvgComparison = static_cast<double>(linearprobbingcomparison) / search_size;

	cout << "Average Comparison: " << AvgComparison << endl;
	cout << "Average Collision: " << AvgCollsion << endl;

	string iddel;
	cout << "Enter ID to delete: ";
	cin >> iddel;
	Delete(iddel);
}

// link list insertion
void llInsertion(const IDcard& idData1, int index1)
{
	Node* newNode = new Node(idData1);

	if (Linklistdata[index1] == nullptr)
	{
		Linklistdata[index1] = newNode;
		cout << "Inserted at Index: " << index1 << ": " << idData1.ID << endl;
	}

	else
	{
		newNode->next = Linklistdata[index1];
		Linklistdata[index1] = newNode;
		cout << "Inserted at Index: " << index1 << ": " << idData1.ID << endl;
	}
}

// link list search
bool llSearch(string searchID, int index2)
{
	Node* crnt = Linklistdata[index2];

	while (crnt != nullptr)
	{
		if (crnt->data.ID == searchID)
		{
			return true;
		}
		crnt = crnt->next;
	}
	return false;
}

// to delete Id from link list
void llDeletion(string del, int index3)
{
	Node* crnt1 = Linklistdata[index3];
	Node* prev = nullptr;

	while (crnt1 != nullptr && crnt1->data.ID != del)
	{
		prev = crnt1;
		crnt1 = crnt1->next;
	}

	if (crnt1 == nullptr)
	{
		cout << "ID not found." << endl;
	}

	if(prev == nullptr)
	{
		Linklistdata[index3] = crnt1->next;
	}

	else
	{
		prev->next = crnt1->next;
	}

	delete crnt1;
	cout << "DeletedID: " << del << " at index: " << index3 << endl;
}

// comparing link list
void llComparison()
{

	string idTosearch;
	for (int d = 0; d < table_size; d++)
	{
		Linklistdata[d] = nullptr;
	}

	cout << endl;
	Display();

	int LinklistCollisions = 0;

	idTosearch = genrateRandom().ID;

	for (int e = 0; e < data_size; e++)
	{
		IDcard Idata = genrateRandom();
		cout << endl << "ID: " << Idata.ID;
		int llindex = Hashfunction(Idata.ID);

		if (llSearch(Idata.ID, llindex))
		{
			LinklistCollisions++;
		}
		else
		{
			llInsertion(Idata, llindex);
		}
	}
	cout << endl;
	Display();

	
	idTosearch = genrateRandom().ID;

	cout << "Genrate ID for searching: " << idTosearch << endl;
	int linklistcomparison = 0;

	for (int f = 0; f < search_size; f++)
	{
		idTosearch = genrateRandom().ID;
		cout << "Searching for ID: " << idTosearch << endl;
		linklistcomparison += llSearch(idTosearch, Hashfunction(idTosearch)) ? (f + 1) : table_size;
	}

	double AvgCollsion = static_cast<double>(LinklistCollisions) / data_size;
	double AvgComparison = static_cast<double>(linklistcomparison) / search_size;

	cout << "Link-List Average Comparison: " << AvgComparison << endl;
	cout << "Link-List Average Collision: " << AvgCollsion << endl;

	string iddel;
	cout << "Enter ID to delete: ";
	cin >> iddel;
	llDeletion(iddel, Hashfunction(iddel));
}


// BST insertion
void BSTInsertion(const IDcard& idData2)
{
	int index = Hashfunction(idData2.ID);

	if (BSTdata[index] == nullptr)
	{
		BSTdata[index] = new BSTNode(idData2);
		cout << "Inserted at Index: " << index << ": " << idData2.ID << endl;
	}

	else
	{
		BSTNode* root = BSTdata[index];
		BSTNode* parent = nullptr;

		while (root != nullptr)
		{
			parent = root;

			if (idData2.ID < root->data.ID)
			{
				root = root->left;
			}

			else
			{
				root = root->right;
			}
		}

		if (idData2.ID < parent->data.ID)
		{
			parent->left = new BSTNode(idData2);
		}

		else
		{
			parent->right = new BSTNode(idData2);
		}
		cout << "Inserted at Index: " << index << ": " << idData2.ID << endl;

	}
	
}

// search function for BST
bool BSTSearch(BSTNode* ptr, const string searchid)
{
	if (ptr == nullptr || ptr->data.ID == searchid)
	{
		return ptr != nullptr;
	}

	if (searchid < ptr->data.ID)
	{
		return BSTSearch(ptr->left, searchid);
	}

	else
	{
		return BSTSearch(ptr->right, searchid);
	}
}

// pointer function to find the smallest node of BST
BSTNode* Minival(BSTNode* ptr1)
{
	BSTNode* ptr3 = ptr1;
	while (ptr3 != nullptr && ptr3->left != nullptr)
	{
		ptr3 = ptr3->left;
	}

	return ptr3;
}

// BST deletion
void BSTDeletion(const string delid)
{
	int index = Hashfunction(delid);

	if (BSTdata[index] != nullptr)
	{
		BSTNode* root = BSTdata[index];
		BSTNode* parent = nullptr;
		BSTNode* crnt = root;

		// searching for Node to del
		while (crnt != nullptr && crnt->data.ID != delid)
		{
			parent = crnt;
			if (delid < crnt->data.ID)
			{
				crnt = crnt->left;
			}
			else
			{
				crnt = crnt->right;
			}
		}

		//IF node's found
		if (crnt != nullptr)
		{
			if (crnt->left == nullptr)
			{
				BSTNode* temp = crnt->right;
				delete crnt;

				if (parent == nullptr)
				{
					BSTdata[index] = temp;
				}

				else if (parent->left == crnt)
				{
					parent->left = temp;
				}

				else
				{
					parent->right = temp;
				}
			}

			else if (crnt->right == nullptr)
			{
				BSTNode* temp = crnt->right;
				delete crnt;

				if (parent == nullptr)
				{
					BSTdata[index] = temp;
				}

				else if (parent->left == crnt)
				{
					parent->left = temp;
				}

				else
				{
					parent->right = temp;
				}
			}

			// node with two children
			else
			{
				BSTNode* ptr2 = Minival(crnt->right);
					crnt->data = ptr2->data;
					BSTDeletion(ptr2->data.ID);
			}
		}

	}
}



// comparing BST
void BSTComparison()
{

	string iddel;
	string idTosearch;
	for (int d = 0; d < table_size; d++)
	{
		BSTdata[d] = nullptr;
	}
	cout << endl;
	Display();

	int BSTCollisions = 0;

	idTosearch = genrateRandom().ID;

	for (int e = 0; e < data_size; e++)
	{
		IDcard Idata = genrateRandom();
		cout << endl << "ID: " << Idata.ID;
		int index = Hashfunction(Idata.ID);

		if (BSTSearch(BSTdata[index], Idata.ID))
		{
			BSTCollisions++;
			
		}
		else
		{
			BSTInsertion(Idata);
		}
	}
	cout << endl;
	Display();


	idTosearch = genrateRandom().ID;
	cout << "Genrate ID for searching: " << idTosearch << endl;
	int BSTcomparison = 0;
	for (int f = 0; f < search_size; f++)
	{
		idTosearch = genrateRandom().ID;
		cout << "Searching for ID: " << idTosearch << endl; 
		BSTNode* result = BSTdata[Hashfunction(idTosearch)];
		BSTcomparison += (BSTSearch(result, idTosearch)) ? (f + 1) : table_size;
	}

	double AvgCollsion = static_cast<double>(BSTCollisions) / data_size;
	double AvgComparison = static_cast<double>(BSTcomparison) / search_size;

	cout << "BST Average Comparison: " << AvgComparison << endl;
	cout << "BST Average Collision: " << AvgCollsion << endl;

	cout << "Enter ID to delete: ";
	cin >> iddel;
	BSTDeletion(iddel);
}

// main body
int main()
{
	srand(static_cast<unsigned int>(time(nullptr)));
	char c;
	
	cout << "***********************************************" << endl;
	cout << "Welcome to NADRA" << endl;
	cout << "***********************************************" << endl;
	cout << "which technique would you like to use" << endl;
	cout << "1.Linear Probbing." << endl;
	cout << "2.Link List." << endl;
	cout << "3.BST" << endl;
	cout << "***********************************************" << endl;
	cout << "Enter your choice: ";
	cin >> c;

	switch (c)
	{
	case1:
		Comparison();
		break;
	case 2:
		llComparison();
		break;

	case 3:
		BSTComparison();
		break;
	default:
		cout << "Invalid Exiting the program." << endl;

	}
	
	return 0;
}
