//---------------------------------------------------------------------------
// NAME: Ethan Higa
// DATE: Fall 2021
// DESC: implementing a binary search tree
//---------------------------------------------------------------------------

#ifndef BSTMAP_H
#define BSTMAP_H

#include "map.h"
#include "arrayseq.h"
#include <iostream>
using namespace std;


template<typename K, typename V>
class BSTMap : public Map<K,V>
{
public:

  // default constructor
  BSTMap();

  // copy constructor
  BSTMap(const BSTMap& rhs);

  // move constructor
  BSTMap(BSTMap&& rhs);

  // copy assignment
  BSTMap& operator=(const BSTMap& rhs);

  // move assignment
  BSTMap& operator=(BSTMap&& rhs);  

  // destructor
  ~BSTMap();
  
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

  // Returns the height of the binary search tree
  int height() const;
  
private:

  // node for linked-list separate chaining
  struct Node {
    K key;
    V value;
    Node* left;
    Node* right;
  };

  // number of key-value pairs in map
  int count = 0;

  // array of linked lists
  Node* root = nullptr;

  // clean up the tree and reset count to zero given subtree root
  void make_empty(Node* st_root);

  // copy assignment helper
  Node* copy(const Node* rhs_st_root) const;
  
  // erase helper
  Node* erase(const K& key, Node* st_root);

  // find_keys helper
  void find_keys(const K& k1, const K& k2, const Node* st_root,
                 ArraySeq<K>& keys) const;

  // sorted_keys helper
  void sorted_keys(const Node* st_root, ArraySeq<K>& keys) const;

  // height helper
  int height(const Node* st_root) const;
  
};

template<typename K, typename V>
BSTMap<K, V>::BSTMap()
{ // leave empty
}

template<typename K, typename V>
BSTMap<K, V>::BSTMap(const BSTMap& rhs)
{
	*this = rhs;
}

template<typename K, typename V>
BSTMap<K, V>::BSTMap(BSTMap&& rhs)
{
	*this = std::move(rhs);
}

template<typename K, typename V>
BSTMap<K, V>& BSTMap<K, V>::operator=(const BSTMap& rhs)
{
	if(this != &rhs)
	{
		make_empty(root); // make lhs empty
		root = copy(rhs.root);
		count = rhs.count;
	}
	return *this;
}

template<typename K, typename V>
BSTMap<K, V>& BSTMap<K, V>::operator=(BSTMap&& rhs)
{
	if(this != &rhs)
	{
		make_empty(root); // make the lhs empty
		root = rhs.root; 
		count = rhs.count;
		rhs.root = nullptr; // set rhs to null
		rhs.count = 0;
	}
	return *this;
}

template<typename K, typename V>
BSTMap<K, V>::~BSTMap()
{
	make_empty(root);
}

template<typename K, typename V>
int BSTMap<K, V>::size() const
{
	return count;
}

template<typename K, typename V>
bool BSTMap<K, V>::empty() const
{
	return count <= 0;
}

template<typename K, typename V>
V& BSTMap<K, V>::operator[](const K& key)
{	
	Node* iterate = root; // iterate till key found
	while(iterate != nullptr)
	{
		if(iterate->key == key)
			return iterate->value;
		else if(key < iterate->key)
			iterate = iterate->left;
		else if(key > iterate->key)
			iterate = iterate->right;
	}
	throw std::out_of_range("out of range\n");
}

template<typename K, typename V>
const V& BSTMap<K, V>::operator[](const K& key) const
{
	Node* iterate = root;
	while(iterate != nullptr)
	{
		if(iterate->key == key)
			return iterate->value;
		else if(key < iterate->key)
			iterate = iterate->left;
		else if(key > iterate->key)
			iterate = iterate->right;
	}
	throw std::out_of_range("out of range\n");
}

template<typename K, typename V>
void BSTMap<K, V>::insert(const K& key, const V& value)
{
	Node* temp = new Node; //make new node
	temp->key = key;
	temp->value = value;
	temp->left = nullptr;
	temp->right = nullptr;
	if(root == nullptr) // if the first insert at the root
	{
		root = temp;
		++count;
		return;
	}
	Node* iterate = root;
	while(iterate != temp)
	{
		if(temp->key < iterate->key) // go to left if less than
		{
			if(iterate->left == nullptr) // insert the new node if left null
			{
				iterate->left = temp;
				++count;
				return;
			}
			else
			{
				iterate = iterate->left;
			}
		}
		if(temp->key > iterate->key) // go to right if greater than
		{
			if(iterate->right == nullptr)
			{
				iterate->right = temp;
				++count;
				return;
			}
			else
			{
				iterate = iterate->right;
			}
		}
	}
}

template<typename K, typename V>
void BSTMap<K, V>::erase(const K& key)
{
	root = erase(key, root);
	--count;
}

template<typename K, typename V>
bool BSTMap<K, V>::contains(const K& key) const
{
	Node* iterate = root;
	while(iterate != nullptr)
	{
		if(iterate->key == key)
			return true;
		else if(key < iterate->key)
			iterate = iterate->left;
		else if(key > iterate->key)
			iterate = iterate->right;
	}
	return false;
}

template<typename K, typename V>
ArraySeq<K> BSTMap<K, V>::find_keys(const K& k1, const K& k2) const
{
	ArraySeq<K> keys;
	find_keys(k1, k2, root, keys);
	return keys;
}

template<typename K, typename V>
ArraySeq<K> BSTMap<K, V>::sorted_keys() const
{
	ArraySeq<K> keys;
	sorted_keys(root, keys); // return already sorted
	return keys;
}

template<typename K, typename V>
int BSTMap<K, V>::height() const
{
	return height(root);
}

// recursive function, post order traversal
template<typename K, typename V>
void BSTMap<K, V>::make_empty(Node* st_root)
{
	if(st_root == nullptr)
		return;
	make_empty(st_root->left);
	make_empty(st_root->right);
	delete st_root; // delete one where it is in the recursion
	--count;
}

// post order traversal for copy
template<typename K, typename V>
typename BSTMap<K, V>::Node* BSTMap<K, V>::copy(const Node* rhs_st_root) const
{
	if(rhs_st_root == nullptr) // if it empty
		return nullptr; 

	Node* lhs_st_root = new Node; // make new node that is a copy of the rhs
	lhs_st_root->key = rhs_st_root->key;
	lhs_st_root->value = rhs_st_root->value;
	lhs_st_root->left = nullptr;
	lhs_st_root->right = nullptr;

	if(rhs_st_root->left == nullptr and rhs_st_root->right == nullptr)
		return lhs_st_root; // return a leaf
	if(rhs_st_root->left != nullptr) // copy left subtree
		lhs_st_root->left = copy(rhs_st_root->left);
	if(rhs_st_root->right != nullptr) // not else cause want to copy both sides
		lhs_st_root->right = copy(rhs_st_root->right);
	return lhs_st_root; // finally return main root
}

// recursive function
template<typename K, typename V>
typename BSTMap<K, V>::Node* BSTMap<K, V>::erase(const K& key, Node* st_root)
{
	// if reach nullptr
	if(st_root == nullptr)
		throw std::out_of_range("out of range\n");
	if (key < st_root->key)
		st_root->left = erase(key, st_root->left);
	else if (key > st_root->key)
		st_root->right = erase(key, st_root->right);
	else if (key == st_root->key)
	{
		// case 1: left subtree is empty
		if(st_root->left == nullptr)
		{
			Node* temp = st_root->right;
			delete st_root;
			return temp;	
		}
		// case 2: right subtree is empty
		else if(st_root->right == nullptr)
		{
			Node* temp = st_root->left;
			delete st_root;
			return temp;	
		}
		// case 3: in order successor
		// 	use iteration to find, replace, and delete inorder successor
		else
		{
			Node* prev_successor = st_root;
			Node* successor = st_root->right; //go to right child
			while(successor->left != nullptr)
			{ // go till left is null
				prev_successor = successor;
				successor = successor->left;
			}
			// replace contents of node to delete with inorder successor's contents
			st_root->key = successor->key; // replace successor to st root
			st_root->value = successor->value;
			if(prev_successor->key == successor->key)
			{ // if successor to the immediate right of st root
				prev_successor->right = successor->right;
				delete successor;
			}
			else
			{ // set the node previous to the successor to the erased successor
				prev_successor->left = erase(st_root->key, successor);
			}
		}
	}
	return st_root;
}

// inorder traversal
template<typename K, typename V>
void BSTMap<K, V>::find_keys(const K& k1, const K& k2, const Node* st_root, ArraySeq<K>& keys) const
{
	// check if done
	if(st_root == nullptr)
		return;
	// go left
	find_keys(k1, k2, st_root->left, keys);
	// ... visit the node ...
	if(st_root->key >= k1 and st_root->key <= k2)
		keys.insert(st_root->key, keys.size());
	// go right
	find_keys(k1, k2, st_root->right, keys);
}

template<typename K, typename V>
void BSTMap<K, V>::sorted_keys(const Node* st_root, ArraySeq<K>& keys) const
{
	// check if done
	if(st_root == nullptr)
		return;
	// go left
	sorted_keys(st_root->left, keys);
	// ... visit the node ...
	keys.insert(st_root->key, keys.size());
	// go right
	sorted_keys(st_root->right, keys);

}

template<typename K, typename V>
int BSTMap<K, V>::height(const Node* st_root) const
{
	if(st_root == nullptr) // reached the very end
		return 0;
	int left_height = height(st_root->left);
	int right_height = height(st_root->right);
	if(left_height >= right_height)
		return left_height + 1;
	else
		return right_height + 1;
}


#endif
