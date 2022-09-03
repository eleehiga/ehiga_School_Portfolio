
//---------------------------------------------------------------------------
// NAME: Ethan Higa
// FILE: linkedlist.h
// DATE: Fall 2021
// DESC: Implemented a linked list class
//----------------------------------------------------------------------


#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdexcept>
#include <ostream>
#include <iostream>
using namespace std; // remove this stuff later
#include "sequence.h"


template<typename T>
class LinkedSeq : public Sequence<T>
{
public:

  // Default constructor
  LinkedSeq();

  // Copy constructor
  LinkedSeq(const LinkedSeq& rhs);

  // Move constructor
  LinkedSeq(LinkedSeq&& rhs);

  // Copy assignment operator
  LinkedSeq& operator=(const LinkedSeq& rhs);

  // Move assignment operator
  LinkedSeq& operator=(LinkedSeq&& rhs);
  
  // Destructor
  ~LinkedSeq();
  
  // Returns the number of elements in the sequence
  int size() const override;

  // Tests if the sequence is empty
  bool empty() const override;

  // Returns a reference to the element at the index in the
  // sequence. Used for lvalues (assignments into the
  // sequence). Throws out_of_range if index is invalid (less than 0
  // or greater than or equal to size()).
  T& operator[](int index) override;

  // Returns a constant address to the element at the index in the
  // sequence. Used for rvalues (evaluating to the value at the
  // index). Throws out_of_range if index is invalid (less than 0 or
  // greater than or equal to size()).
  const T& operator[](int index) const override;

  // Extends (grows) the sequence by inserting the element at the
  // given index (shifting existing elements to the "right" in the
  // sequence).  Throws out_of_range if the index is invalid (less
  // than 0 or greater than size()).
  void insert(const T& elem, int index) override;

  // Shrinks the sequence by removing the element at the index in the
  // sequence (shifing elements to the "left" in the sequence). Throws
  // out_of_range if index is invalid.
  void erase(int index) override;

  // Returns true if the element is in the sequence, and false
  // otherwise.
  bool contains(const T& elem) const override;

  // Sorts the elements in the sequence using less than equal (<=)
  // operator. (Not implemented in HW-2)
  void sort() override; 

  // implements merge sort over current sequence
  void merge_sort();

  // implements quick sort over current sequence
  void quick_sort();
  
private:

  // linked list node
  struct Node {
    T value;
    Node* next = nullptr;
  };

  // head pointer
  Node* head = nullptr;

  // tail pointer
  Node* tail = nullptr;

  // size of list
  int node_count = 0;

  // helper to delete all the nodes in the list (called by destructor
  // and copy assignment operator)
  void make_empty();

  // helper functions for merge and quick sort
  Node* merge_sort(Node* left, int len);
  Node* quick_sort(Node* start, int len);

};

template<typename T>
int LinkedSeq<T>::size() const
{
  return node_count;
}

template<typename T>
bool LinkedSeq<T>::empty() const
{
  if(head == nullptr)
    return true;
  return false;
}

template<typename T>
T& LinkedSeq<T>::operator[](int index)
{
  Node* temp = head;
  int count = 0;
  if(index >= size() or index < 0)
    throw std::out_of_range("out of range\n");
  if(index == size() - 1)
    return tail->value;
  while(temp != nullptr)
  {
    if(count >= index)
    {
      return temp->value;
    }
    ++count;
    temp = temp->next;
  }
}

template<typename T>
const T& LinkedSeq<T>::operator[](int index) const
{ 
  Node* temp = head;
  int count = 0;
  if(index >= size() or index < 0)
    throw std::out_of_range("out of range\n");
  if(index == size() - 1)
    return tail->value;
  while(temp != nullptr)
  {
    if(count >= index)
    {
      return temp->value;
    }
    ++count;
    temp = temp->next;
  }
}

// this function is for inserting a new node into a list
template<typename T>
void LinkedSeq<T>::insert(const T& elem, int index)
{
  // can insert a new value into the list
  if(index > size() or index < 0)
    throw std::out_of_range("out of range\n");
  Node* temp = new Node;
  temp->value = elem;
  // if size 0 attach to head then head same as tail
  if(empty())
  {
    temp->next = head;
    head = temp;
    tail = head;  
  }
  else if(index == 0)
  { 
    // just attach to head
    temp->next = head;
    head = temp;
  }
  else if(index == size())
  {
    tail->next = temp;
    tail = temp;
    tail->next = nullptr;
  }
  else
  {
    // attach to the end so just the tail
    Node* travel_node = head;
    int count = 0;
    while(travel_node != nullptr)
    {
      if(count >= index - 1)
      {
        Node* after_node = travel_node->next; // save pointer to add to new temp
        travel_node->next = temp;
        temp->next = after_node;
	break;
      }    
      travel_node = travel_node->next;
      ++count;
    }
  }
  temp = nullptr;
  ++node_count;
}

template<typename T>
void LinkedSeq<T>::erase(int index)
{
  // when at that value before the node should point at the one after
  if(index >= size() or index < 0)
    throw std::out_of_range("out of range\n");
  if(index == 0)
  {
    Node* saved = head->next;
    delete head; // deallocates space to remove first element at head
    head = saved; 
    if(head == nullptr)
      tail = nullptr;
    --node_count;
    return;
  }
  Node* temp = head;
  int count = 0;
  while(temp != nullptr)
  {
    if(count >= index - 1) // one before
    {
      Node* saved = temp->next->next;
      delete temp->next;
      temp->next = saved;
      --node_count; // decrease count then can see if the index is at the end of this new size
      if(index == size())
        tail = temp;
      return;
    }
    ++count;
    temp = temp->next;
  }
}

template<typename T>
bool LinkedSeq<T>::contains(const T& elem) const
{
  Node* temp = head;
  while(temp != nullptr)
  {
    if(temp->value == elem)
    {
      temp == nullptr;
      return true;
    }
    temp = temp->next;
  }
  temp = nullptr;
  return false;
}

// implementing the following stream insertion operator. Note that
//       the function should be implemented using only public
//       functions of LinkedSeq

template<typename T>
std::ostream& operator<<(std::ostream& stream, const LinkedSeq<T>& seq)
{
  // loop through elements of linked list
  // attach it to stream
  for(int i = 0; i < seq.size(); ++i)
  {
      stream << seq[i]; // keep adding the elements of the array
      if(i < seq.size() - 1)
        stream << ", ";		
  }
  return stream;
}

template<typename T>
LinkedSeq<T>::LinkedSeq()
{ // its fine being empty
}

template<typename T>
LinkedSeq<T>::~LinkedSeq()
{
  make_empty();
}

template<typename T>
LinkedSeq<T>::LinkedSeq(const LinkedSeq& rhs)
{
  *this = rhs; 
}

template<typename T>
LinkedSeq<T>::LinkedSeq(LinkedSeq&& rhs)
{
  *this = std::move(rhs);
}

// copy, = operator
template<typename T>
LinkedSeq<T>& LinkedSeq<T>::operator=(const LinkedSeq<T>& rhs)
{
  if (this != &rhs) 
  {
    make_empty(); 
    Node* temp = rhs.head;
    int count = 0;
    while(temp != nullptr)
    { // go through rhs and insert in cleared lhs
      insert(temp->value, count);
      ++count;
      temp = temp->next;
    }
    temp = nullptr;
  }
  return *this; 
}

template<typename T>
LinkedSeq<T>& LinkedSeq<T>::operator=(LinkedSeq<T>&& rhs)
{
  if(this != &rhs)
  { // just empty lhs then change head and tail pointing and rhs head and tail pointing to null
    make_empty();
    head = rhs.head;
    tail = rhs.tail;
    node_count = rhs.node_count; // also got to send over the node_count
    rhs.head = nullptr;
    rhs.tail = nullptr;
    rhs.node_count = 0;
  }
  return *this; 
}

template<typename T>
void LinkedSeq<T>::make_empty()
{
  while(head != nullptr)
    erase(0);
}

template<typename T>
void LinkedSeq<T>::sort()
{
  merge_sort();
}

template<typename T>
void LinkedSeq<T>::merge_sort()
{
  head = merge_sort(head, size());
  Node* temp_node = head;
  for(int i = 0; i < size() - 1; ++i)
    temp_node = temp_node->next; // if went till size() then will be null
  tail = temp_node; 
}

template<typename T>
void LinkedSeq<T>::quick_sort()
{
  head = quick_sort(head, size());
  Node* temp_node = head;
  for(int i = 0; i < size() - 1; ++i)
    temp_node = temp_node->next; // if went till size() then will be null
  tail = temp_node; 
  if(tail != nullptr)
    tail->next = nullptr;
}

template<typename T>
typename LinkedSeq<T>::Node* LinkedSeq<T>::merge_sort(Node* left, int len)
{
  if(len <= 1)
    return left;
  int mid = (len) / 2; // calculating the mid length
  Node* temp = left;
  for(int i = 0; i < mid - 1; ++i) // get to the mid point
    temp = temp->next;
  Node* right = temp->next; // then split at mid with left and right sequences
  temp->next = nullptr; // make the end of left to null pointer so end does not point back to the beginning
  left = merge_sort(left, mid); // recursive steps
  right = merge_sort(right, len - mid);
  Node* temp1 = left; // iterates through
  Node* temp2 = right;
  Node* new_left = nullptr; // what will be returned
  Node* temp3 = new_left; 
  if (temp1->value < temp2->value)
  {
    new_left = temp1; // first val of new_left set
    temp1 = temp1->next;
  }
  else
  {
    new_left = temp2;
    temp2 = temp2->next;
  }
  temp3 = new_left; // points to new_left to iterate through
  while (temp1 !=  nullptr and temp2 != nullptr)
  {
    if(temp1->value < temp2->value)
    {
      temp3->next = temp1; // val from left into new_left
      temp1 = temp1->next;
    }
    else
    {
      temp3->next = temp2;
      temp2 = temp2->next;
    }
    temp3 = temp3->next; // go this appended value to keep appending more
  }
  if(temp1 != nullptr) // still values left in the left sequence
    temp3->next = temp1;
  else
    temp3->next = temp2;
  return new_left;
}

template<typename T>
typename LinkedSeq<T>::Node* LinkedSeq<T>::quick_sort(Node* start, int len)
{
  if(len <= 1)
    return start;
  Node* pivot_node = start; // to either declare values as smaller or larger than it
  Node* smaller = nullptr; // sequence contains smaller than pivot values
  Node* larger = nullptr; // sequence contains larger than pivot values
  int smaller_len = 0; // len of smaller sequence
  int larger_len = 0; // len of larger sequence
  Node* i_node = start->next; // use this to iterate through main sequence
  Node* temp1 = smaller; // use this to iterate through smaller sequence
  Node* temp2 = larger; // use this to iterate through larger sequence
  while(i_node != nullptr)
  {
    if(i_node->value < pivot_node->value and smaller_len <= 0)
    {
      smaller = i_node; // set the first value of smaller
      ++smaller_len;
      temp1 = smaller;
    }
    else if(i_node->value < pivot_node->value)
    {
      temp1->next = i_node;
      temp1 = temp1->next; // get to this appended value
      ++smaller_len;
    }
    else if(larger_len <= 0)
    {
      larger = i_node;
      ++larger_len;
      temp2 = larger;
    }
    else
    {
      temp2->next = i_node;
      temp2 = temp2->next;
      ++larger_len;
    }
    i_node = i_node->next;
  }
  // nullptr at the ends to make them distinct sequences
  if(temp1 != nullptr)
    temp1->next = nullptr;
  if(temp2 != nullptr)
    temp2->next = nullptr;
  smaller = quick_sort(smaller, smaller_len); // recursive steps
  larger = quick_sort(larger, larger_len);
  if(smaller_len > 0)
  {
    Node* temp = smaller;
    while(temp->next != nullptr)
      temp = temp->next;
    temp->next = pivot_node; // set next of last node in smaller to pivot
  }
  else
    smaller = pivot_node; // smaller is nullptr so set it equal to pivot
  pivot_node->next = larger;
  return smaller; // smaller should be first
}

#endif
