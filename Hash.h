// Specification file for the Hash class
// Written By: Zachary Minshall
// IDE: MSVS

#pragma once
#include <string>
#include "DList.hpp"
#include "ListNode.hpp"

template <class T>
class DList;

template <class T>
class ListNode;

using std::string;

template<class T>
class Hash
{
private:
	int BucketCount;
	DList<T>* table;

public:
	Hash(int b);

	//insert, delete, and search
	void insertItem(string key, T item);
	void deleteItem(string key, T item);
	bool search(string key, T &returnedItem);

	//hash functions
	int goodHashFunc(string key);
	int badHashFunc(string key);

	//print functions
	void printLoadFactor();
	void printCollisions();
	void writeToFile();
	void printHash();
};
/*
Constructor for the Hash class that creates an array of pointers
to DList objects. The size of the table is equal to the input parameter 
*/
template<class T>
Hash<T>::Hash(int b)
{
	BucketCount = b;
	table = new DList<T>[BucketCount];
}


/*
Inserts an item into the hash table by finding the items index
and then calling the DList insertNode function on the correct list
*/
template<class T>
void Hash<T>::insertItem(string key, T item)
{
	int index = goodHashFunc(key);
	table[index].insertNode(item);
}

/*
Removes an item from the hash table by finding the items index
and then calling the DList deleteNode function on the correct list
*/
template<class T>
void Hash<T>::deleteItem(string key, T item)
{
	int index = goodHashFunc(key);
	table[index].deleteNode(item);
}

/*
The search function takes a key and a reference item, finds the 
hash index of the key, and then uses the Dlist search function to 
find if the item exists in the list. If it exists then the data in the 
list item is copied to the reference item that was provided.
*/
template<class T>
bool Hash<T>::search(string key, T &returnedItem) {
	int index = goodHashFunc(key);
	T searchItem;
	searchItem.setTitle(key);

	return table[index].searchList(searchItem, returnedItem);
}

/*
This is an example of a good hash function
 */
template<class T>
int Hash<T>::goodHashFunc(string key)
{
	int seed = 23;
	unsigned long sum = 0;
	for (int i = 0; i < key.length(); i++)
	{
		sum = (sum * seed) + key[i]*key[i]*key[i];
	}
	return sum % BucketCount;
	/*
	unsigned int b = 23;
	unsigned long a = 11;
	unsigned long sum = 0;

	for (int i = 0; i < key.length(); i++)
	{
		sum += key[i] * a;
		a = a * b;
	}

	return sum % BucketCount;
	*/
}

/*
This is an example of a bad hash function because it does not discriminate 
between the order of characters within a given key. Also it only looks at most
the first 3 characters of each string. So a larger string may have the same hash as a smaller one
if they start with the same first 3 characters.
*/
template<class T>
int Hash<T>::badHashFunc(string key)
{
		unsigned int sum = 0;
		for (int i = 0; i < key.length() && i < 3; i++)
			sum = sum + key[i];
		return  sum % BucketCount;
}

/*
The printLoadFactor function traverses each DList in the Hash Table,
adds up the lists that contain at least 1 node, and prints the resulting integer.
*/
template<class T>
void Hash<T>::printLoadFactor()
{
	int load = 0;

	for (int i = 0; i < BucketCount; i++) {
		if (table[i].getCount() != 0)
			load += 1;
	}
	
	cout << "The Load Factor of the Hash Table is: " << load << " / " << BucketCount << endl;
}

/*
The printCollisions function traverses each DList in the Hash Table,
adds up the number of collisions in each, and prints the resulting integer
*/
template<class T>
void Hash<T>::printCollisions()
{
	int collisions = 0;

	for (int i = 0; i < BucketCount; i++) {
		for (int k = 0; k < table[i].getCount() - 1; k++) {
			collisions += 1;
		}
	}

	cout << "The number of collisions within the Hash Table is: " << collisions << endl;
}

template<class T>
void Hash<T>::writeToFile() {
	ofstream outFile;
	outFile.open("Output.txt");
	for (int i = 0; i < BucketCount; i++) {

		ListNode<T>* head = table[i].getHead();
		ListNode<T>* pCur = head->getNext();

		while (pCur != head)
		{
			outFile << pCur->getitem().getTitle() << ",";
			outFile << pCur->getitem().getMedium() << ",";
			outFile << pCur->getitem().getCountry() << ",";
			outFile << pCur->getitem().getArtist() << ",";
			outFile << pCur->getitem().getYearPainted() << endl;

			pCur = pCur->getNext();
		}
	}
	cout << "Database written to file \"Output.txt\"" << endl;
}

template <class T>
void Hash<T>::printHash() {
	for (int i = 0; i < BucketCount; i++) {

		ListNode<T>* head = table[i].getHead();
		ListNode<T>* pCur = head->getNext();

		while (pCur != head)
		{
			cout << pCur->getitem().getTitle() << endl;

			pCur = pCur->getNext();
		}
	}
}
