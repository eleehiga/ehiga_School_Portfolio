//---------------------------------------------------------------------------
// NAME:
// DATE: Fall 2021
// DESC:
//---------------------------------------------------------------------------

#ifndef BINSEARCHMAP_H
#define BINSEARCHMAP_H

#include "map.h"
#include "arrayseq.h"


template<typename K, typename V>
class BinSearchMap : public Map<K,V>
{
public:

  // Returns the number of key-value pairs in the map
  int size() const;

  // Tests if the map is empty
  bool empty() const;

  // Allows values associated with a key to be updated. Throws
  // out_of_range if the given key is not in the collection.
  V& operator[](const K& key);

  // Returns the value for a given key. Throws out_of_range if the
  // given key is not in the collection. 
  const V& operator[](const K& key) const;

  // Extends the collection by adding the given key-value
  // pair. Assumes the key being added is not present in the
  // collection. Insert does not check if the key is present.
  void insert(const K& key, const V& value);

  // Shrinks the collection by removing the key-value pair with the
  // given key. Does not modify the collection if the collection does
  // not contain the key. Throws out_of_range if the given key is not
  // in the collection.
  void erase(const K& key);

  // Returns true if the key is in the collection, and false
  // otherwise.
  bool contains(const K& key) const;

  // Returns the keys k in the collection such that k1 <= k <= k2
  ArraySeq<K> find_keys(const K& k1, const K& k2) const;

  // Returns the keys in the collection in ascending sorted order.
  ArraySeq<K> sorted_keys() const;  

private:

  // If the key is in the collection, bin_search returns true and
  // provides the key's index within the array sequence (via the index
  // output parameter). If the key is not in the collection,
  // bin_search returns false and provides the last index checked by
  // the binary search algorithm. 
  bool bin_search(const K& key, int& index) const;
  
  // implemented as a resizable array of (key-value) pairs
  ArraySeq<std::pair<K,V>> seq;

};

// TODO: Implement the BinSearchMap functions below. Note that you do
//       not need to implement a default constructor, destructor, copy
//       constructor, copy assignment operator, move constructor, and
//       move assignment operator for this version of Map. Instead,
//       the default C++ implementations are sufficient.

template<typename K, typename V>
int BinSearchMap<K, V>::size() const {
  return seq.size();
}

template<typename K, typename V>
bool BinSearchMap<K, V>::empty() const {
  return seq.empty();
}

template<typename K, typename V>
V& BinSearchMap<K, V>::operator[](const K& key) {
  int i;
  if(bin_search(key, i))
    return seq[i].second;
  throw std::out_of_range("out of range\n");
}

template<typename K, typename V>
const V& BinSearchMap<K, V>::operator[](const K& key) const {
  int i;
  if(bin_search(key, i))
    return seq[i].second;
  throw std::out_of_range("out of range\n");
}

template<typename K, typename V>
void BinSearchMap<K, V>::insert(const K& key, const V& value) {
  int i;
  bin_search(key, i);
  std::pair<K, V> p = {key, value};
  if(size() >= 1 && key >= seq[i].first) {
    seq.insert(p, i+1);
  } // insert to append dif from insert in between
  else {
    seq.insert(p, i); // insert it such that it is sorted
  }
}

template<typename K, typename V>
void BinSearchMap<K, V>::erase(const K& key) {
  int i;
  bool found = bin_search(key, i);
  if (!found)
    throw std::out_of_range("out of range\n");
  seq.erase(i); // insert it such that it is sorted
}

template<typename K, typename V>
bool BinSearchMap<K, V>::contains(const K& key) const {
  int i;
  return bin_search(key, i);
}

template<typename K, typename V>
ArraySeq<K> BinSearchMap<K, V>::find_keys(const K& k1, const K& k2) const {
  ArraySeq<K> seq1;
  int i1;
  bin_search(k1, i1);
  while(i1 < size() && seq[i1].first <= k2) {
    seq1.insert(seq[i1].first, seq1.size());
    ++i1;
  } // start search from where k1 is then go till max size of out of bounds of k2
  return seq1;
}

template<typename K, typename V>
ArraySeq<K> BinSearchMap<K, V>::sorted_keys() const {
  ArraySeq<K> seq1; // just insert it as it is already sorted
  for(int i = 0; i < size(); ++i)
    seq1.insert(seq[i].first, seq1.size());
  return seq1;
}

template<typename K, typename V>
bool BinSearchMap<K, V>::bin_search(const K& key, int& index) const {
  int i_mid = size()/2;
  int search_size = size(); // stop when search sie = 0
  int right = size() - 1; // right most index, can move these values
  int left = 0; // left most index
  while(search_size >= 1) {
    if(seq[i_mid].first == key) {
      index = i_mid;
      return true;
    }
    else if(key > seq[i_mid].first) { // true then search in right half of list
      search_size = right - i_mid;
      left = i_mid + 1; // TODO check if this and right setting is right
      i_mid = (right - i_mid + 1) / 2 + i_mid; // mid of right half + 1 as like for right calculation below in which that one uses i_mid which is not in the left section
    }
    else { // then search in left half of the list
      search_size = i_mid - left;
      right = i_mid - 1;
      i_mid = (i_mid - left) / 2 + left; // mid of left half
    }
  }
  index = i_mid;
  return false;
}

#endif
