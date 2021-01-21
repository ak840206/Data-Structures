// ListNode.hpp
// Specification file for the ListNode class
// template can only be in one file
// Written By: A. Student
// Changed By: Yu Wen Ssu
// IDE: Xcode

#ifndef ListNode_h
#define ListNode_h

using namespace std;

template <class T>
class ListNode{
private:
    T item;
    // Use a generic name
    // T item;
    ListNode<T> *next;
    ListNode<T> *prev;
public:
    // Constructor
    ListNode(){}
    ListNode(T);
    // setters
    void setNext(ListNode<T>*);
    void setPrev(ListNode<T>*);
    void setitem(T);  // Use a generic name
    // void setItem(T);
    // getters
    ListNode<T> *getNext();
    ListNode<T> *getPrev();
    T getitem(); // Use a generic name
};


template <class T>
ListNode<T>::ListNode(T itemData)
{
    item = itemData;
    next = nullptr;
    //next = getHead();
    //
    prev = nullptr;
    //prev = getHead();
}

template <class T>
void ListNode<T>::setNext(ListNode<T>* newNext)
{
    next = newNext;
}

template <class T>
void ListNode<T>::setPrev(ListNode<T>* newPrev)
{
    prev = newPrev;
}

template <class T>
void ListNode<T>::setitem(T newitem)
{
    item = newitem;
}

template <class T>
ListNode<T>* ListNode<T>::getNext()
{
    return next;
}

template <class T>
ListNode<T>* ListNode<T>::getPrev()
{
    return prev;
}

template <class T>
T ListNode<T>::getitem()
{
    return item;
}

#endif /* ListNode_h */