// Binary tree abstract base class
// Created by A. Student
// Modified by: Zachary Minshall
// IDE: Microsoft Visual Studio
// UPDATED: 11/10/2019
 
#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"
#include "Queue.h"

template<class T>
class BinaryTree
{
protected:
	BinaryNode<T>* rootPtr;		// ptr to root node
	int count;							// number of nodes in tree

public:
	// "admin" functions
 	BinaryTree() {rootPtr = 0; count = 0;}
	BinaryTree(const BinaryTree<T> & tree){ }
	virtual ~BinaryTree() { }
   
	// common functions for all binary trees
 	bool isEmpty() const	{return count == 0;}
	int size() const	    {return count;}
	void clear()			{destroyTree(rootPtr); rootPtr = 0; count = 0;}
	void preOrder(void visit(T &)) const {_preorder(visit, rootPtr);}
	void inOrder(void visit(T &)) const  {_inorder(visit, rootPtr);}
	void postOrder(void visit(T &)) const {_postorder(visit, rootPtr);}
	
	// additional traverse
	void breadthFirst(void visit(T&)) const {_breadthFirst(visit, rootPtr);}

	// print indented tree
	void printTree(void visit(T&)) const { _printTree(visit, rootPtr, 1); }

	// abstract functions to be implemented by derived class
	virtual bool insert(const T & newData, int compare(const T, const T)) = 0;
	virtual bool remove(const T & data, int compare(const T, const T), int compare2(const T, const T)) = 0;
	virtual bool getEntry(const T & anEntry, T & returnedItem, int compare(const T, const T)) const = 0;

private:   
	// delete all nodes from the tree
	void destroyTree(BinaryNode<T>* nodePtr);

	// internal print
	void _printTree(void visit(T&), BinaryNode<T>* nodePtr, int level) const;

	// internal traverse
	void _preorder(void visit(T &), BinaryNode<T>* nodePtr) const;
	void _inorder(void visit(T &), BinaryNode<T>* nodePtr) const;
	void _postorder(void visit(T &), BinaryNode<T>* nodePtr) const;
	void _breadthFirst(void visit(T&), BinaryNode<T>* nodePtr) const;
   
}; 

//Destroy the entire tree
template<class T>
void BinaryTree<T>::destroyTree(BinaryNode<T>* nodePtr)
{
	if (nodePtr == NULL)
		return;
	destroyTree(nodePtr->getLeftPtr());
	destroyTree(nodePtr->getRightPtr());
	cout << "Deleting node: " << nodePtr->getItem().getName() << endl;
	delete nodePtr;
}  

//Preorder Traversal
template<class T>
void BinaryTree<T>::_preorder(void visit(T &), BinaryNode<T>* nodePtr) const
{
	if (nodePtr != 0)
	{
		T item = nodePtr->getItem();
		visit(item);
		_preorder(visit, nodePtr->getLeftPtr());
		_preorder(visit, nodePtr->getRightPtr());
	}
}  

//Inorder Traversal
template<class T>
void BinaryTree<T>::_inorder(void visit(T &), BinaryNode<T>* nodePtr) const
{
	if (nodePtr != 0)
	{
		T item = nodePtr->getItem();
		_inorder(visit, nodePtr->getLeftPtr());
		visit(item);
		_inorder(visit, nodePtr->getRightPtr());
	}
}  

//Postorder Traversal
template<class T>
void BinaryTree<T>::_postorder(void visit(T &), BinaryNode<T>* nodePtr) const
{
	if (nodePtr != 0)
	{
		T item = nodePtr->getItem();
		_postorder(visit, nodePtr->getLeftPtr());
		_postorder(visit, nodePtr->getRightPtr());
		visit(item);
	}
}  

//BreadthFirst Traversal
template<class T>
void BinaryTree<T>::_breadthFirst(void visit(T &), BinaryNode<T>* nodePtr) const
{
	if (nodePtr != 0) {
		Queue<BinaryNode<T>*> q;
		BinaryNode<T>* curr;
		q.enqueue(nodePtr);
		int level = 1;
		while (!q.isEmpty()) {
			int nodeCount = q.getCount();
			cout << endl;
			cout << "Level " << level << ":" << endl;
			while (nodeCount > 0) {
				q.dequeue(curr);
				T item = curr->getItem();
				cout << '\t';
				visit(item);
				if (curr->getLeftPtr() != NULL)
					q.enqueue(curr->getLeftPtr());
				if (curr->getRightPtr() != NULL)
					q.enqueue(curr->getRightPtr());
				nodeCount--;
			}
			level++;
		}
	}
}

// Prints the tree as an indented list
template<class T>
void BinaryTree<T>::_printTree(void visit(T&), BinaryNode<T>* nodePtr, int level) const
{
	if (nodePtr == NULL)
		return;
	else
	{
		T item = nodePtr->getItem();
		for (int i = 1; i < level; i++)
			cout << '\t';
		cout << "Level " << level << ". ";
		visit(item);
		level++;
		_printTree(visit, nodePtr->getLeftPtr(), level);
		_printTree(visit, nodePtr->getRightPtr(), level);
	}
}
#endif