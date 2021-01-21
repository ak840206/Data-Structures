// Specification file for the LinkedList class
// template can only be in one file 
// Written By: A. Student
// Changed By: Yu Wen Ssu 
// IDE: Xcode

#ifndef D_LIST_H
#define D_LIST_H

#include "ListNode.hpp"
#include <iomanip>

using namespace std;

template <class T>
class DList
{
private:
    ListNode<T>* head;
    int count;
    
public:
    DList();   // Constructor
    ~DList();  // Destructor

	//getter
	ListNode<T>* getHead() { return head; }
    
    // Circular Doubly-Linked list operations
    void displayList(void printHeader(void)) const;
    int getCount() const {return count;}
    void insertNode(T);
    bool deleteNode(T);
    bool searchList(T, T &) const;
    bool isEmpty();
    void traverseForward(void printHeader(void), void printBreakline(void));
    void traverseBackward(void printHeader(void), void printBreakline(void));
};



template <class T>
DList<T>::DList()
{
    head = new ListNode<T>;
    head->setNext(head);
    head->setPrev(head);
    count = 0;
}

//**************************************************
// displayList shows the value
// stored in each node of the linked list
// pointed to by head.
//**************************************************
template <class T>
void DList<T>::displayList(void printHeader(void)) const
{
    ListNode<T> *pCur;
    
    //cout << "===== ==================== ====" << endl;
    //cout << "State City                 Year" << endl;
    //cout << "===== ==================== ====" << endl;
    
    printHeader();
    //pCur = head ->next;
    pCur = head->getNext();
    
    while(pCur)
    {
        cout << right << setw(4) << pCur->getitem().getArtist() << "  "
        << left << setw(21) << pCur->getitem().getTitle()
        << pCur->getitem().getYearPainted() << endl;
        
        pCur = pCur->getNext();
    }
    cout << "===== ==================== ====" << endl;
}

//**************************************************
// The searchList function looks for a target city
// in the sorted linked list: if found, returns true
// and copied the data in that node to the output parameter
//**************************************************
template <class T>
bool DList<T>::searchList(T dataIn, T &dataOut) const
{
    bool found = false;
    ListNode<T> *pCur = head->getNext();
    
    while(pCur != head && pCur->getitem() < dataIn)
        pCur = pCur->getNext();
    
    if(pCur != head && pCur->getitem() == dataIn )
    {
        //dataOut = pCur->city;
        dataOut = pCur->getitem();
        found = true;
    }
    
    return found;
}

//**************************************************
// The insertNode function inserts a new node in a
// sorted linked list
//**************************************************
template <class T>
void DList<T>::insertNode(T dataIn)
{
    ListNode<T> *newNode;
    ListNode<T> *pPre;
    ListNode<T> *pCur;
    
    newNode = new ListNode<T>;
    newNode->setitem(dataIn);
    
    pPre = head;
    pCur = head->getNext();
    
    while(pCur != head && pCur->getitem() < dataIn)
        pCur = pCur->getNext();
    
    pPre = pCur->getPrev();
    
    //setNext
    pPre->setNext(newNode);
    newNode->setNext(pCur);
    
    //setPrev
    newNode->setPrev(pPre);
    pCur->setPrev(newNode);
    
    count++;
}

//**************************************************
// The deleteNode function searches for a node
// in a sorted linked list; if found, the node is
// deleted from the list and from memory.
//**************************************************
/*~*~==============================================~*~~
Be consistent:
deleteNode() could also be improved, as you did improve insertNode()

while (pCur != head && pCur->getCity() < dataIn)
{
    pPre = pCur;
    pCur = pCur->getForw();
}

// See below

while (pCur != head && pCur->getCity() < dataIn)
{
    pCur = pCur->getForw();
}

pPre = pCur->getBack();

-1Point
 */
template <class T>
bool DList<T>::deleteNode(T dataIn)
{
    ListNode<T> *pCur;
    ListNode<T> *pPre;
    bool deleted = false;
    
    pPre = head;
    pCur = head->getNext();
    
    while(pCur != NULL && pCur->getitem() < dataIn)
    {
        pPre = pCur;
        pCur = pCur->getNext();
    }
    
    pPre = pCur->getPrev();
    
    if(pCur != NULL && pCur->getitem() == dataIn)
    {
        //setNext
        pPre->setNext(pCur->getNext());
        //setPrev
        pCur->getNext()->setPrev(pPre);
        
        delete pCur;
        deleted = true;
        count--;
    }
    return deleted;
}

//**************************************************
// The isEmpty function returns true if no
// element in the list, and returns false
// if there is at least one element in the list.
//**************************************************
/*~*~==============================================~*~~
Delia Garbacea, Oct 29 at 10:01am
bool DList::isEmpty()
{
    int c = count;
    if(c == 0)
        return false;
    return true;
}

// See below
bool DList::isEmpty()
{
    return count == 0;
}
*/

template <class T>
bool DList<T>::isEmpty()
{
    int c = count;
    if(c == 0)
        return false;
    return true;
}

//**************************************************
// The traverseFoward function traverse foward
// through a cicular doubly-linked list and display
// the menu.
//**************************************************
/*~*~==============================================~*~~
 Recommendation for the EC assignment based on Homework 2:
 
 If you want to replace City with a template in the  DList class,
 you also have to change the following line
 
 cout << right << setw(4) << pCur->getCity().getState() << "  "
 << left << setw(21) << pCur->getCity().getName()
 << pCur->getCity().getYear() << endl;
 
 to
 
 cout << pCut->getCity();
 
 This means that you would have to revisit the overloaded <<
 // because template can not be dereference (.getState())
 ~*~==============================================~*~~
 Delia Garbacea, Oct 29 at 10:01am
 */
template <class T>
void DList<T>::traverseForward(void printHeader(void), void printBreakline(void))
{
	ListNode<T> *pWalk;
    pWalk = head->getNext();
    
    printHeader();
    
    cout << pWalk->getitem();
    
    
    
    printBreakline();
}

//**************************************************
// The traverseBackwad function traverse backward
// through a cicular doubly-linked list and display
// the menu.
//**************************************************
template <class T>
void DList<T>::traverseBackward(void printHeader(void), void printBreakline(void))
{
    ListNode<T> *pWalk;
    pWalk = head->getPrev();
    
    printHeader();
    
    while(pWalk != head)
    {
        pWalk = pWalk->getPrev();
        cout << right << setw(4) << pWalk->getitem().getArtist() << "  "
        << left << setw(21) << pWalk->getitem().getTitle()
        << pWalk->getitem().getYearPainted() << endl;
    }
    
    printBreakline();
}

//**************************************************
// Destructor                                      *
// This function deletes every node in the list.   *
//**************************************************
template <class T>
DList<T>::~DList()
{
    ListNode<T> *pCur;
    ListNode<T> *pNext;
    
    pCur = head->getNext();
    while(pCur != head)
    {
        pNext = pCur->getNext();
        
        cout << "DEBUG - Destructor: Now deleting " << pCur->getitem().getTitle()
        << endl;
        delete pCur;
        pCur = pNext;
    }
    cout << "DEBUG - Destructor: Now deleting the sentinel node: "
    << head->getitem().getYearPainted() << endl;
    delete head;
}


#endif