// Binary Search Tree ADT
// Created by A. Student
// Modified by: Yu Wen Ssu
 
#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"
//#include "Painting.h"

template<class T>
class BinarySearchTree : public BinaryTree<T>
{   
private:
	// internal insert node: insert newNode in nodePtr subtree
	BinaryNode<T>* _insert(BinaryNode<T>* nodePtr, BinaryNode<T>* newNodePtr, int compare(const T, const T));
   
	// internal remove node: locate and delete target node under nodePtr subtree
	BinaryNode<T>* _remove(BinaryNode<T>* nodePtr, const T target, bool & success, int compare(const T, const T), int compare2(const T,const T));
   
	// delete target node from tree, called by internal remove node
	BinaryNode<T>* deleteNode(BinaryNode<T>* targetNodePtr);
   
	// remove the leftmost node in the left subtree of nodePtr
	BinaryNode<T>* removeLeftmostNode(BinaryNode<T>* nodePtr, T & successor);
   
	// search for target node
	BinaryNode<T>* findNode(BinaryNode<T>* treePtr, const T & target, int compare(const T, const T)) const;
    
    // search for target node
    BinaryNode<T>* _findAllNode(BinaryNode<T>* treePtr, const T & target, int compare(const T, const T), void visit(T&)) const;
    
    // internal find smallest node
    BinaryNode<T>* _findSmallest(BinaryNode<T>* nodePtr, bool & success);
    
    // internal find largest node
    BinaryNode<T>* _findLargest(BinaryNode<T>* nodePtr, bool & success);
public:  
	// insert a node at the correct location
    bool insert(const T & newEntry, int compare(const T, const T));
	// remove a node if found
	bool remove(const T & target, int compare(const T, const T), int compare2(const T, const T));
	// find a target node
	bool getEntry(const T & anEntry, T & returnedItem, int compare(const T, const T)) const;
    
    bool getAllEntry(const T& anEntry, int compare(const T, const T), void visit(T&)) const;

    
    // find the smallest node
    bool findSmallest(T & returnedItem);
    // find the largest node
    bool findLargest(T & returnedItem);
    
};


///////////////////////// public function definitions ///////////////////////////
//Inserting items within a tree
template<class T>
bool BinarySearchTree<T>::insert(const T & newEntry, int compare(const T, const T))
{
    //int titleCompare(Painting p1, Painting p2)
    //when u insert, since different tree, change, don't use overload
    BinaryNode<T>* newNodePtr = new BinaryNode<T>(newEntry);
	this->rootPtr = _insert(this->rootPtr, newNodePtr, compare);
	return true;
}  

//Removing items within a tree
template<class T>
bool BinarySearchTree<T>::remove(const T & target, int compare(const T, const T), int compare2(const T, const T))
{
	bool isSuccessful = false;
	this->rootPtr = _remove(this->rootPtr, target, isSuccessful, compare, compare2);
	return isSuccessful; 
}  

//Finding entries within a tree
template<class T>
bool BinarySearchTree<T>::getEntry(const T& anEntry, T& returnedItem, int compare(const T, const T)) const
{
    BinaryNode<T>* item = findNode(this-> rootPtr, anEntry, compare);
    if(item)
    {
        returnedItem = item->getItem();
        return true;
    }
    return false;
}
 
//Finding all entries within a tree
template<class T>
bool BinarySearchTree<T>::getAllEntry(const T& anEntry, int compare(const T, const T), void visit(T&)) const
{
    _findAllNode(this->rootPtr, anEntry, compare, visit);
	return false;
}

//Finding smallest within a tree
template<class T>
bool BinarySearchTree<T>::findSmallest(T & returnedItem)
{
    BinaryNode<T>* item;
    bool isSuccessful = false;
    if((item = _findSmallest(this-> rootPtr,isSuccessful)))
    {
        returnedItem = item->getItem();
        isSuccessful = true;
    }
    return isSuccessful;
}

//Finding largest within a tree
template<class T>
bool BinarySearchTree<T>::findLargest(T & returnedItem)
{
    BinaryNode<T>* item;
    bool isSuccessful = false;
    if((item = _findLargest(this-> rootPtr,isSuccessful)))
    {
        returnedItem = item->getItem();
        isSuccessful = true;
    }
    return isSuccessful;
}


//////////////////////////// private functions ////////////////////////////////////////////

//Implementation of the insert operation
template<class T>
BinaryNode<T>* BinarySearchTree<T>::_insert(BinaryNode<T>* nodePtr,
                                                          BinaryNode<T>* newNodePtr, int compare(const T , const T))
{

	//compare returns 
	//p1 > p2 -> 1
	//p1 < p2 -> -1
	//p1 = p2 -> 0

	//we want greater or equal to go right

	if (nodePtr == NULL)
		nodePtr = newNodePtr;
	else {
		if (compare(newNodePtr->getItem(), nodePtr->getItem()) == -1)
			nodePtr->setLeftPtr(_insert(nodePtr->getLeftPtr(), newNodePtr, compare));
		else
			nodePtr->setRightPtr(_insert(nodePtr->getRightPtr(), newNodePtr, compare));
	}
	return nodePtr;
}

//Implementation for the search operation for all 
template<class T>
BinaryNode<T>* BinarySearchTree<T>::_findAllNode(BinaryNode<T>* nodePtr, const T & target, 
																int compare(const T, const T), void visit(T&)) const
{

	//compare returns 
	//p1 > p2 -> 1
	//p1 < p2 -> -1
	//p1 = p2 -> 0

	bool found = false;
	while (nodePtr != NULL)
	{
		if (compare(nodePtr->getItem(), target) == 1)
			nodePtr = nodePtr->getLeftPtr();
		else if (compare(nodePtr->getItem(), target) == -1) {
			nodePtr = nodePtr->getRightPtr();
		}
		else if (compare(nodePtr->getItem(), target) == 0) {
			cout << nodePtr->getItem();
			nodePtr = nodePtr->getRightPtr();
			//if(nodePtr->getRightPtr() != nullptr)
			//_findAllNode(nodePtr->getRightPtr(), target, compare, visit);
		}
	}
	return nodePtr;
}

//Implementation for the search operation
template<class T>
BinaryNode<T>* BinarySearchTree<T>::findNode(BinaryNode<T>* nodePtr,
                                                           const T & target,
                                                                int compare(const T, const T)) const
{
    //compare returns
    //p1 > p2 -> 1
    //p1 < p2 -> -1
    //p1 = p2 -> 0

    //we want greater or equal to go right
    // > or < matters
    bool found = false;
    while(nodePtr != NULL && !found)
    {
        if(compare(nodePtr->getItem(), target) == 1)
            nodePtr = nodePtr->getLeftPtr();
        else
        {
            if(compare(nodePtr->getItem(), target) == -1)
                nodePtr = nodePtr->getRightPtr();
            else
                found = true;
        }
    }
    return nodePtr;
}


////////////////////////////////////////////////////////////////////////
// The follwoing functions will be needed for the team project
//Implementation of the remove operation
template<class T>
BinaryNode<T>* BinarySearchTree<T>::_remove(BinaryNode<T>* nodePtr,
	const T target,	bool& success, 	int compare(const T, const T),
	int compare2(const T, const T))

	//compare returns 
	//p1 > p2 -> 1
	//p1 < p2 -> -1
	//p1 = p2 -> 0

	//we want greater or equal to go right
{
	if (nodePtr == 0)
	{
		success = false;
		return 0;
	}
	if (compare(nodePtr->getItem(), target) == 1)
		nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success, compare, compare2));
	else if (compare(nodePtr->getItem(), target) == -1)
		nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success, compare, compare2));
	else if (compare(nodePtr->getItem(), target) == 0 && compare2(nodePtr->getItem(), target) != 0) {
		nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success, compare, compare2));
	}
	else
	{
		nodePtr = deleteNode(nodePtr);
		success = true;
	}
	return nodePtr;
}

//Implementation of the delete operation
template<class T>
BinaryNode<T>* BinarySearchTree<T>::deleteNode(BinaryNode<T>* nodePtr)
{
	if (nodePtr->isLeaf())				
	{
		delete nodePtr;
		nodePtr = 0;
		return nodePtr;
	}
	else if (nodePtr->getLeftPtr() == 0)  
	{
		BinaryNode<T>* nodeToConnectPtr = nodePtr->getRightPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else if (nodePtr->getRightPtr() == 0) 
	{
		BinaryNode<T>* nodeToConnectPtr = nodePtr->getLeftPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;      
	}
	else                                  
	{
		T newNodeValue;
		nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
		nodePtr->setItem(newNodeValue);
		return nodePtr;
	}  
}

//Implementation to remove the left leaf
template<class T>
BinaryNode<T>* BinarySearchTree<T>::removeLeftmostNode(BinaryNode<T>* nodePtr,
                                                                     T & successor)
{
	if (nodePtr->getLeftPtr() == 0)
	{
		successor = nodePtr->getItem();
		return deleteNode(nodePtr);
	}
	else 
	{
		nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
		return nodePtr;
	}       
}

//Implementation to find the smallest operation
template<class T>
BinaryNode<T>* BinarySearchTree<T>::_findSmallest(BinaryNode<T>* nodePtr, bool & success)
{
    if(nodePtr->getLeftPtr())
        return _findSmallest(nodePtr->getLeftPtr(), success);
    else
        return nodePtr;
}


//Implementation to find the largest operation
template<class T>
BinaryNode<T>* BinarySearchTree<T>::_findLargest(BinaryNode<T>* nodePtr, bool & success)
{
    if(nodePtr->getRightPtr())
        return _findLargest(nodePtr->getRightPtr(), success);
    else
        return nodePtr;
}

#endif _BINARY_SEARCH_TREE
