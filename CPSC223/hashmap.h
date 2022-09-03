//---------------------------------------------------------------------------
// NAME:  Ethan Higa
// DATE: Fall 2021
// DESC: Hash Tab;e implemented with keys that index values
//---------------------------------------------------------------------------

#ifndef HASHMAP_H
#define HASHMAP_H

#include <functional>
#include "map.h"
#include "arrayseq.h"
#include <iostream>


template<typename K, typename V>
class HashMap : public Map<K,V>
{
public:

  // default constructor
  HashMap();

  // copy constructor
  HashMap(const HashMap& rhs);

  // move constructor
  HashMap(HashMap&& rhs);

  // copy assignment
  HashMap& operator=(const HashMap& rhs);

  // move assignment
  HashMap& operator=(HashMap&& rhs);  

  // destructor
  ~HashMap();
  
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

  // Returns true if the key is in the collection, and false otherwise.
  bool contains(const K& key) const;

  // Returns the keys k in the collection such that k1 <= k <= k2
  ArraySeq<K> find_keys(const K& k1, const K& k2) const;

  // Returns the keys in the collection in ascending sorted order
  ArraySeq<K> sorted_keys() const;  

  // statistics functions for the hash table implementation
  int min_chain_length() const;
  int max_chain_length() const;
  double avg_chain_length() const;
  
private:

  // node for linked-list separate chaining
  struct Node {
    K key;
    V value;
    Node* next;
  };

  // number of key-value pairs in map
  int count = 0;

  // max size of the (array) table
  int capacity = 16;

  // threshold for resize and rehash
  const double load_factor_threshold = 0.75; // 0.4, 0.6, 0.7, 0.75, 0.8, 0.9
  
  // array of linked lists
  Node** table = new Node*[capacity];

  // the hash function
  int hash(const K& key) const;

  // resize and rehash the table
  void resize_and_rehash();

  // initialize the table to all nullptr
  void init_table();
  
  // clean up the table and reset member variables
  void make_empty();
};

// implemented the public and private HashMap functions below.

template<typename K, typename V>
HashMap<K, V>::HashMap() 
{
	init_table();
}

// copy
template<typename K, typename V>
HashMap<K, V>::HashMap(const HashMap& rhs)
{
	init_table();
	*this = rhs;
}

// move
template<typename K, typename V>
HashMap<K, V>::HashMap(HashMap&& rhs)
{
	init_table(); // init the table such that the lhs is easier to delete when  moving
	*this = std::move(rhs);
}

// copy
template<typename K, typename V>
HashMap<K, V>& HashMap<K, V>::operator=(const HashMap& rhs)
{
	if(this != &rhs) {
		if(table != nullptr)
			make_empty();
		table = new Node*[rhs.capacity];
		capacity = rhs.capacity;
		count = 0;
		init_table(); // reinitialize left side
		Node* temp = rhs.table[0];
		for(int i = 0; i < rhs.capacity; ++i) {
			temp = rhs.table[i];
			while(temp != nullptr) {
				(*this).insert(temp->key, temp->value);
				temp = temp->next;
			}
		}
	}
	return *this;
}

// move
template<typename K, typename V>
HashMap<K, V>& HashMap<K, V>::operator=(HashMap&& rhs) 
{
	if(this != &rhs) {
		make_empty();
		table = rhs.table;
		count = rhs.count;
		capacity = rhs.capacity;
		rhs.table = new Node*[16]; // default after move for rhs is this
		rhs.capacity = 16;
		rhs.count = 0;
		rhs.init_table();
	}
	return *this;
}

template<typename K, typename V>
HashMap<K, V>::~HashMap()
{
	make_empty();
}

template<typename K, typename V>
int HashMap<K, V>::size() const
{
	return count;
}

template<typename K, typename V>
bool HashMap<K, V>::empty() const
{
	return count <= 0;
}

template<typename K, typename V>
V& HashMap<K, V>::operator[](const K& key)
{
	int index = hash(key);
	if(table[index] == nullptr) 
		throw std::out_of_range("out of range\n");
	Node* temp = table[index];
	while(temp != nullptr) { // search for key in the in chain
		if(temp->key == key)
			return temp->value;
		temp = temp->next;
	}
}

template<typename K, typename V>
const V& HashMap<K, V>::operator[](const K& key) const
{
	int index = hash(key);
	if(table[index] == nullptr) 
		throw std::out_of_range("out of range\n");
	Node* temp = table[index];
	while(temp != nullptr) {
		if(temp->key == key)
			return temp->value;
		temp = temp->next;
	}
}

template<typename K, typename V>
void HashMap<K, V>::insert(const K& key, const V& value)
{
	if(count*1.0/capacity > load_factor_threshold)
		resize_and_rehash();
	Node* temp = new Node;
	int index = hash(key);
	temp->key = key;
	temp->value = value;
	temp->next = table[index]; // set next one to first node
	table[index] = temp;
	++count;
}

template<typename K, typename V>
void HashMap<K, V>::erase(const K& key)
{
	int index = hash(key);
	if(table[index] == nullptr) 
		throw std::out_of_range("out of range\n");
	Node* temp = (table[index])->next;
	if(table[index]->key == key) { // if the key is in the first node in the chain
		delete table[index];
		table[index] = temp;
		--count;
		return;
	}
	Node* temp_prev = table[index];
	while(temp != nullptr) {
		if(temp->key == key) {
			temp = temp->next; // move to next one to save that
			delete temp_prev->next;
			temp_prev->next = temp;
			--count;
			return;
		}
		else {
			temp_prev = temp_prev->next;
			temp = temp->next;
		}
	}
}

template<typename K, typename V>
bool HashMap<K, V>::contains(const K& key) const
{
	int index = hash(key);
	Node* temp = table[index];
	while(temp != nullptr) { // go through till find key
		if(temp->key == key)
			return true;
		temp = temp->next;
	}
	return false;
}

template<typename K, typename V>
ArraySeq<K> HashMap<K, V>::find_keys(const K& k1, const K& k2) const
{
	ArraySeq<K> seq_temp;
	Node* temp = table[0];
	for(int i = 0; i < capacity; ++i) { // go through all to find keys in range
		temp = table[i];
		while(temp != nullptr) {
			if(temp->key >= k1 && temp->key <= k2)
				seq_temp.insert(temp->key, seq_temp.size());
			temp = temp->next;
		}
	}
	return seq_temp;
}

template<typename K, typename V>
ArraySeq<K> HashMap<K, V>::sorted_keys() const
{
	ArraySeq<K> seq_temp;
	Node* temp = table[0];
	for(int i = 0; i < capacity; ++i) {
		temp = table[i];
		while(temp != nullptr) {
			seq_temp.insert(temp->key, seq_temp.size());
			temp = temp->next;
		}
	}
	seq_temp.sort();
	return seq_temp;
}

template<typename K, typename V>
int HashMap<K, V>::min_chain_length() const
{
	int min = 0;
	int length = 0;
	Node* temp = table[0];
	for(int i = 0; i < capacity; ++i) {
		temp = table[i];
		length = 0;
		while(temp != nullptr) {
			++length;
			temp = temp->next;
		}
		if((length < min and length != 0) || (min == 0 and length > min))
			min = length; // logic above is how if the length is less than the mid but it is not zero or if the min is at zero but the length is above this 
	}
	return min;
}

template<typename K, typename V>
int HashMap<K, V>::max_chain_length() const
{
	int max = 0;
	int length = 0;
	Node* temp = table[0];
	for(int i = 0; i < capacity; ++i) {
		temp = table[i];
		length = 0;
		while(temp != nullptr) {
			++length;
			temp = temp->next;
		}
		if(length > max)
			max = length;
	}
	return max;
}

template<typename K, typename V>
double HashMap<K, V>::avg_chain_length() const
{
	double sum = 0;
	int chains = 0;
	int length = 0;
	Node* temp = table[0];
	for(int i = 0; i < capacity; ++i) {
		temp = table[i];
		length = 0;
		while(temp != nullptr) {
			++length;
			temp = temp->next;
		}
		if(length > 0) { 
			sum = length + sum;
			++chains;
		}
	}
	if(chains > 0)
		return sum / chains;
	return 0;
}

template<typename K, typename V>
int HashMap<K, V>::hash(const K& key) const
{
	std::hash<K> hash_fun;
	int value2 = hash_fun(key);
	return value2 % capacity; // returns the index
}

template<typename K, typename V>
void HashMap<K, V>::resize_and_rehash()
{
	int new_capacity = capacity * 2;
	HashMap<K,V> temp_hash_map; // making a new hash map
	temp_hash_map.make_empty();
	temp_hash_map.table = new Node*[new_capacity];
	temp_hash_map.capacity = new_capacity;
	temp_hash_map.init_table(); // got to initialize it
	Node* temp = table[0];
	for(int i = 0; i < capacity; ++i) {
		temp = table[i];
		while(temp != nullptr) {
			temp_hash_map.insert(temp->key, temp->value);
			temp = temp->next;
		}
	}
	*this = temp_hash_map;
}

template<typename K, typename V>
void HashMap<K, V>::init_table()
{
	for(int i = 0; i < capacity; ++i)
		table[i] = nullptr;
}

template<typename K, typename V>
void HashMap<K, V>::make_empty()
{
	if(table == nullptr)
		return;
	Node* temp = table[0];
	for(int i = 0; i < capacity; ++i) {
		temp = table[i];
		while(temp != nullptr) {
			temp = temp->next;
			delete table[i];
			table[i] = temp;
		}
	}
	delete [] table; // deletes all the values in the array
	table = nullptr;
   	count = 0;
	capacity = 0;
}

#endif
