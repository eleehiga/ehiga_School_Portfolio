
//---------------------------------------------------------------------------
// NAME: Ethan Higa
// FILE: arrayseq.h
// DATE: Fall 2021
// DESC: resizable array
//----------------------------------------------------------------------


#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <stdexcept>
#include <ostream>
#include "sequence.h"

#include <iostream>
using namespace std;

template<typename T>
class ArraySeq : public Sequence<T>
{
public:

  // Default constructor
  ArraySeq();

  // Copy constructor
  ArraySeq(const ArraySeq& rhs);

  // Move constructor
  ArraySeq(ArraySeq&& rhs);

  // Copy assignment operator
  ArraySeq& operator=(const ArraySeq& rhs);

  // Move assignment operator
  ArraySeq& operator=(ArraySeq&& rhs);
  
  // Destructor
  ~ArraySeq();
  
  // Returns the number of elements in the sequence
  virtual int size() const;

  // Tests if the sequence is empty
  virtual bool empty() const;

  // Returns a reference to the element at the index in the
  // sequence. Throws out_of_range if index is invalid.
  virtual T& operator[](int index);

  // Returns a constant address to the element at the index in the
  // sequence. Throws out_of_range if index is invalid.
  virtual const T& operator[](int index) const;

  // Extends the sequence by inserting the element at the given
  // index. Throws out_of_range if the index is invalid.
  virtual void insert(const T& elem, int index);

  // Shrinks the sequence by removing the element at the index in the
  // sequence. Throws out_of_range if index is invalid.
  virtual void erase(int index);

  // Returns true if the element is in the sequence, and false
  // otherwise.
  virtual bool contains(const T& elem) const;

  // Sorts the elements in the sequence using less than equal (<=)
  // operator. (Not implemented in HW-2)
  void sort() override;
  
  // Sorts the elements based on the merge sort algorithm
  void merge_sort();
  
  // Sorts the elements based on the quick sort algorithm
  void quick_sort();

  
private:

  // resizable array
  T* array = nullptr;

  // size of list
  int count = 0;

  // max capacity of the array
  int capacity = 0;

  // helper to double the capacity of the array
  void resize();
  
  // helper to delete the array list (called by destructor and copy
  // constructor)
  void make_empty();

  // helper functions for merge and quick sort
  void merge_sort(int start, int end);
  void quick_sort(int start, int end);

};


template<typename T>
ArraySeq<T>::ArraySeq()
{ // leave empty
}

template<typename T>
ArraySeq<T>::ArraySeq(const ArraySeq& rhs)
{
  *this = rhs;
}

template<typename T>
ArraySeq<T>::ArraySeq(ArraySeq&& rhs)
{
  *this = std::move(rhs);
}


template<typename T>
ArraySeq<T>& ArraySeq<T>::operator=(const ArraySeq<T>& rhs)
{
  if(this != &rhs)
  {
    if(array != nullptr)
	make_empty(); // make the left hand side empty
    array = new T[rhs.capacity];
    capacity = rhs.capacity;
    count = rhs.count;
    for(int i = 0; i < rhs.count; ++i)
      array[i] = rhs.array[i];
  }
  return *this;
}

template<typename T>
ArraySeq<T>& ArraySeq<T>::operator=(ArraySeq<T>&& rhs)
{
 if(this != &rhs)
 {
  make_empty(); // make the left side empty
  array = rhs.array; // set the lhs pointer equal to the rhs pointer
  count = rhs.count;
  capacity = rhs.capacity;
  rhs.array = nullptr;
  rhs.count = 0;
  rhs.capacity = 0;
 }
 return *this;
}

template<typename T>
ArraySeq<T>::~ArraySeq()
{
 make_empty(); // empty it all command here
}

template<typename T>
int ArraySeq<T>::size() const
{
  return count;
}

template<typename T>
bool ArraySeq<T>::empty() const
{
  return count <= 0;
}

template<typename T>
T& ArraySeq<T>::operator[](int index)
{
  if(index >= size() or index < 0)
    throw std::out_of_range("out of range\n");
  return array[index];
}

template<typename T>
const T& ArraySeq<T>::operator[](int index) const
{
  if(index >= size() or index < 0)
    throw std::out_of_range("out of range\n");
  return array[index];
}

template<typename T>
void ArraySeq<T>::insert(const T& elem, int index)
{
 if(index > size() or index < 0)
  throw std::out_of_range("out of range\n");
 if(array == nullptr) // first item to put in the array
 {
  array = new T[1];
  capacity = 1;
 }
 else if(count >= capacity) // if the values in there are past what the array is able to hold
 {
  resize();
 } // can insert element after resize
 if(index < count) // the index value is within how many elements there are
 {
  for(int i = count; i > index; --i) // shift all the elements past the index to the right
   array[i] = array[i - 1];
 }
 array[index] = elem; // if index > count then just append it to the end
 ++count;
}

template<typename T>
void ArraySeq<T>::erase(int index)
{
 if(index >= size() or index < 0)
  throw std::out_of_range("out of range\n");
 for(int i = index; i < count - 1; i++) // shift value of the array past index to the left to cover index also
  array[i] = array[i + 1];
 --count;
}

template<typename T>
bool ArraySeq<T>::contains(const T& elem) const
{
 if(empty())
   return false;
 for(int i = 0; i < size(); ++i)
 {
  if(array[i] == elem)
    return true;
 } 
 return false;
}

template<typename T>
void ArraySeq<T>::resize()
{
 capacity = capacity * 2; // double the capacity
 ArraySeq<T> temp_seq;
 temp_seq.array = new T[capacity]; // this new sequence has the size of the doubled capacity
 for(int i = 0; i < count; ++i)
   temp_seq.array[i] = array[i];
 temp_seq.count = count;
 temp_seq.capacity = capacity;
 *this = temp_seq; // copy temp_seq to the main array
}

template<typename T>
void ArraySeq<T>::make_empty()
{
 if(array == nullptr)
  return;
 delete [] array; // deletes all the values in the array
 array = nullptr;
 count = 0;
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, const ArraySeq<T>& seq)
{
 for(int i = 0; i < seq.size(); ++i)
 {
  stream << seq[i]; // adds values to the stream
  if(i < seq.size() - 1)
   stream << ", ";
 } 
 return stream;
}

template<typename T>
void ArraySeq<T>::merge_sort()
{
  merge_sort(0, count-1);  
}

template<typename T>
void ArraySeq<T>::quick_sort()
{
  quick_sort(0,count-1);
}

template<typename T>
void ArraySeq<T>::merge_sort(int start, int end)
{
  if (start < end)
  {
    int mid = (start + end) / 2;
    merge_sort(start, mid); // recursive step
    merge_sort(mid + 1, end); // recursive step
    
    // merge sorted sublists
    ArraySeq<T> tmp; // tmp array size n set below
    int first1 = start;
    int first2 = mid + 1;
    int i = 0;
    while(first1 <= mid and first2 <= end) 
    { // merge into tmp
      if((*this)[first1] < (*this)[first2])
      {
	tmp.insert((*this)[first1++], i++); // first1++ in order to have the next first1 to compare to the same first2
      }
      else
      {
        tmp.insert((*this)[first2++], i++);;
      }
    }
    while(first1 <= mid) // copy rest
    {
      tmp.insert((*this)[first1++], i++);
    }
    while(first2 <= end) // copy rest
    {
      tmp.insert((*this)[first2++], i++);
    }
    for(int j = 0; j < end - start + 1; ++j)
    { // copy to main array
      ((*this)[start+j]) = tmp[j];
    }
  }
}

template<typename T>
void ArraySeq<T>::quick_sort(int start, int end)
{
  if(start < end)
  {
    T pivot_val = ((*this)[start]);
    int end_pl = start; // end index, start part
    T temp_val;
    for(int i = start + 1; i < end + 1; ++i) 
    { // partition
      if((*this)[i] < pivot_val)
      {
        end_pl = end_pl + 1;
	// swap ( array [ i ] , array [ end_p1 ])
	// move the lower values more near the beginning
	temp_val = ((*this)[end_pl]);
	((*this)[end_pl]) = ((*this)[i]);
        ((*this)[i]) = temp_val;
      }
    }
    // move pivot, swap ( array [ start ] , array [ end_p1 ])
    // move the pivot to be in the middle
    temp_val = ((*this)[end_pl]);
    ((*this)[end_pl]) = ((*this)[start]);
    ((*this)[start]) = temp_val;
    quick_sort(start, end_pl - 1); // recursive step
    quick_sort(end_pl + 1, end); // recursive step
  }
}

template<typename T>
void ArraySeq<T>::sort()
{
  //quick_sort();
  merge_sort(); // for hash map
}

#endif
