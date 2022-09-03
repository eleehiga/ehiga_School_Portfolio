//---------------------------------------------------------------------------
// NAME: Ethan Higa
// DATE: Fall 2021
// DESC: AVL Tree
//---------------------------------------------------------------------------

#ifndef AVLMAP_H
#define AVLMAP_H

#include "map.h"
#include "arrayseq.h"
#include <iostream>

using namespace std;


template<typename K, typename V>
class AVLMap : public Map<K,V>
{
public:

  // default constructor
  AVLMap();

  // copy constructor
  AVLMap(const AVLMap& rhs);

  // move constructor
  AVLMap(AVLMap&& rhs);

  // copy assignment
  AVLMap& operator=(const AVLMap& rhs);

  // move assignment
  AVLMap& operator=(AVLMap&& rhs);  

  // destructor
  ~AVLMap();
  
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

  // helper to print the tree for debugging
  void print() const;
  
private:

  // node for avl tree
  struct Node {
    K key;
    V value;
    Node* left;
    Node* right;
    int height;
  };

  // number of nodes
  int count = 0;

  // root node
  Node* root = nullptr;

  // clean up the tree and reset count to zero given subtree root
  void make_empty(Node* st_root);

  // copy assignment helper
  Node* copy(const Node* rhs_st_root) const;
  
  // erase helper
  Node* erase(const K& key, Node* st_root);

  // insert helper
  Node* insert(const K& key, const V& value, Node* st_root);
  
  // find_keys helper
  void find_keys(const K& k1, const K& k2, const Node* st_root,
                 ArraySeq<K>& keys) const;

  // sorted_keys helper
  void sorted_keys(const Node* st_root, ArraySeq<K>& keys) const;

  // rotations
  Node* right_rotate(Node* k2);
  Node* left_rotate(Node* k2);
  
  // rebalance
  Node* rebalance(Node* st_root);

  // print helper
  void print(std::string indent, const Node* st_root) const;
  
};


template<typename K, typename V>
void AVLMap<K,V>::print() const
{
  print(std::string(""), root);
}


template<typename K, typename V>
void AVLMap<K,V>::print(std::string indent, const Node* st_root) const
{
  if (!st_root)
    return;
  std::cout << st_root->key << " (" << st_root->height << ")" <<  std::endl;
  if (st_root->left) {
    std::cout << indent << " lft: ";
    print(indent + " ", st_root->left);
  }
  if (st_root->right) {
    std::cout << indent << " rgt: ";
    print(indent + " ", st_root->right);
  }
}


//----------------------------------------------------------------------
// TODO: Implement the above functions below
//----------------------------------------------------------------------

template<typename K, typename V>
AVLMap<K, V>::AVLMap()
{ // leave empty
}

template<typename K, typename V>
AVLMap<K, V>::AVLMap(const AVLMap& rhs)
{
	*this = rhs;
}

template<typename K, typename V>
AVLMap<K, V>::AVLMap(AVLMap&& rhs)
{
	*this = std::move(rhs);
}

template<typename K, typename V>
AVLMap<K, V>& AVLMap<K, V>::operator=(const AVLMap& rhs)
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
AVLMap<K, V>& AVLMap<K, V>::operator=(AVLMap&& rhs)
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
AVLMap<K,V>::~AVLMap()
{
	make_empty(root);
}

template<typename K, typename V>
int AVLMap<K, V>::size() const
{
	return count;
}

template<typename K, typename V>
bool AVLMap<K, V>::empty() const
{
	return count <= 0;

}

template<typename K, typename V>
V& AVLMap<K, V>::operator[](const K& key)
{
	Node* iterate = root;
	while(iterate != nullptr)
	{
		if(iterate->key == key)
			return iterate->value;
		else if(key < iterate->key)
			iterate = iterate->left;
		else
			iterate = iterate->right;
	}
	throw std::out_of_range("out of range\n");
}

template<typename K, typename V>
const V& AVLMap<K, V>::operator[](const K& key) const
{
	Node* iterate = root;
	while(iterate != nullptr)
	{
		if(iterate->key == key)
			return iterate->value;
		else if(key < iterate->key)
			iterate = iterate->left;
		else
			iterate = iterate->right;
	}
	throw std::out_of_range("out of range\n");
}

template<typename K, typename V>
void AVLMap<K, V>::insert(const K& key, const V& value)
{
	root = insert(key, value, root); // calls recursive insert
}

template<typename K, typename V>
void AVLMap<K, V>::erase(const K& key)
{
	root = erase(key, root);
	--count;
}

template<typename K, typename V>
bool AVLMap<K, V>::contains(const K& key) const
{
	Node* iterate = root;
	while(iterate != nullptr)
	{
		if(iterate->key == key)
			return true;
		else if(key < iterate->key)
			iterate = iterate->left;
		else
			iterate = iterate->right;
	}
	return false;
}

template<typename K, typename V>
ArraySeq<K> AVLMap<K, V>::find_keys(const K& k1, const K& k2) const
{
	ArraySeq<K> keys;
	find_keys(k1, k2, root, keys);
	return keys;
}

template<typename K, typename V>
ArraySeq<K> AVLMap<K, V>::sorted_keys() const
{
	ArraySeq<K> keys;
	sorted_keys(root, keys);
	return keys;
}

template<typename K, typename V>
int AVLMap<K, V>::height() const
{
	if(root == nullptr) // acount for no tree
		return 0;
	return root->height;
}

template<typename K, typename V>
void AVLMap<K, V>::make_empty(Node* st_root)
{
	if(st_root == nullptr)
		return;
	make_empty(st_root->left);
	make_empty(st_root->right);
	delete st_root;
	--count;
}

template<typename K, typename V>
typename AVLMap<K, V>::Node* AVLMap<K, V>::copy(const Node* rhs_st_root) const
{
	if(rhs_st_root == nullptr)
		return nullptr;

	Node* lhs_st_root = new Node;
	lhs_st_root->key = rhs_st_root->key;
	lhs_st_root->value = rhs_st_root->value;
	lhs_st_root->height = rhs_st_root->height; // in hw8 should also copy height
	lhs_st_root->left = nullptr;
	lhs_st_root->right = nullptr;

	if(rhs_st_root->left == nullptr and rhs_st_root->right == nullptr)
		return lhs_st_root;
	if(rhs_st_root->left != nullptr)
		lhs_st_root->left = copy(rhs_st_root->left);
	if(rhs_st_root->right != nullptr)
		lhs_st_root->right = copy(rhs_st_root->right);
	return lhs_st_root;
}

template<typename K, typename V>
typename AVLMap<K, V>::Node* AVLMap<K, V>::erase(const K& key, Node* st_root)
{
	// if reach nullptr
	if(st_root == nullptr)
		throw std::out_of_range("out of range\n");
	if (key < st_root->key)
	{
		st_root->left = erase(key, st_root->left);
	}
	else if (key > st_root->key)
	{
		st_root->right = erase(key, st_root->right);
	}
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
			if(prev_successor->left == nullptr && prev_successor->right == nullptr)
				prev_successor->height = 1;
			else if(prev_successor->left == nullptr)
				prev_successor->height = prev_successor->right->height + 1;
			else if(prev_successor->right == nullptr)
				prev_successor->height = prev_successor->left->height + 1;
			else if(prev_successor->left->height > prev_successor->right->height)
				prev_successor->height = prev_successor->left->height + 1;
			else if(prev_successor->left->height <= prev_successor->right->height)
				prev_successor->height = prev_successor->right->height + 1;
		}
	}
	if(st_root->left == nullptr && st_root->right == nullptr)
		st_root->height = 1;
	else if(st_root->left == nullptr)
		st_root->height = st_root->right->height + 1;
	else if(st_root->right == nullptr)
		st_root->height = st_root->left->height + 1;
	else if(st_root->left->height > st_root->right->height)
		st_root->height = st_root->left->height + 1;
	else if(st_root->left->height <= st_root->right->height)
		st_root->height = st_root->right->height + 1;
	return rebalance(st_root);
}

template<typename K, typename V>
typename AVLMap<K, V>::Node* AVLMap<K, V>::insert(const K& key, const V& value, Node* st_root)
{
	int bf = 0;
	if(st_root == nullptr)
	{
		Node* temp = new Node;
		temp->key = key;
		temp->value = value;
		temp->left = nullptr;
		temp->right = nullptr;
		temp->height = 1;
		st_root = temp;
		++count;
		return st_root;
	}
	if(key < st_root->key)
	{
		st_root->left = insert(key, value, st_root->left);
		st_root->height = st_root->left->height + 1; // update height
	}
	else if(key > st_root->key)
	{
		st_root->right = insert(key, value, st_root->right);
		st_root->height = st_root->right->height + 1;
	}
	return rebalance(st_root); // will check if need to do rebalance before 
}

template<typename K, typename V>
void AVLMap<K, V>::find_keys(const K& k1, const K& k2, const Node* st_root,
		                 ArraySeq<K>& keys) const
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
void AVLMap<K, V>::sorted_keys(const Node* st_root, ArraySeq<K>& keys) const
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
typename AVLMap<K, V>::Node* AVLMap<K, V>::right_rotate(Node* k2)
{
	Node* k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	// important to update k2 height first then k1 height
	if(k2->left == nullptr && k2->right == nullptr)
		k2->height = 1;
	else if(k2->left == nullptr)
		k2->height = k2->right->height + 1;
	else if(k2->right == nullptr)
		k2->height = k2->left->height + 1;
	else if(k2->left->height > k2->right->height)
		k2->height = k2->left->height + 1;
	else if(k2->left->height <= k2->right->height)
		k2->height = k2->right->height + 1;
	if(k1->left == nullptr && k1->right == nullptr)
		k1->height = 1;
	else if(k1->left == nullptr)
		k1->height = k1->right->height + 1;
	else if(k1->right == nullptr)
		k1->height = k1->left->height + 1;
	else if(k1->left->height > k1->right->height)
		k1->height = k1->left->height + 1;
	else if(k1->left->height <= k1->right->height)
		k1->height = k1->right->height + 1;
	return k1;
}

template<typename K, typename V>
typename AVLMap<K, V>::Node* AVLMap<K, V>::left_rotate(Node* k2)
{
	Node* k1 = k2->right;
	k2->right = k1->left;
	k1->left = k2;
	if(k2->left == nullptr && k2->right == nullptr)
		k2->height = 1;
	else if(k2->left == nullptr)
		k2->height = k2->right->height + 1;
	else if(k2->right == nullptr)
		k2->height = k2->left->height + 1;
	else if(k2->left->height > k2->right->height)
		k2->height = k2->left->height+1;
	else if(k2->left->height <= k2->right->height)
		k2->height = k2->right->height+1;
	if(k1->left == nullptr && k1->right == nullptr)
		k1->height = 1;
	else if(k1->left == nullptr)
		k1->height = k1->right->height + 1;
	else if(k1->right == nullptr)
		k1->height = k1->left->height + 1;
	else if(k1->left->height > k1->right->height)
		k1->height = k1->left->height + 1;
	else if(k1->left->height <= k1->right->height)
		k1->height = k1->right->height + 1;
	return k1;
}

template<typename K, typename V>
typename AVLMap<K, V>::Node* AVLMap<K, V>::rebalance(Node* st_root)
{
	int bf;
	Node* heavier_node = nullptr; // which child, left or right, is the heavier of st_root

	if(st_root->left == nullptr && st_root->right == nullptr)
		return st_root;
	if(st_root->left == nullptr)
		bf = -st_root->right->height;
	else if(st_root->right == nullptr)
		bf = st_root->left->height;
	else
		bf = st_root->left->height - st_root->right->height;
	if(bf >= 2) // left child heavier
	{
		// check which subtree of the child is heavier
		heavier_node = st_root->left;
		if(heavier_node->left == nullptr) // so the right subtree is heavier
			heavier_node = left_rotate(heavier_node);
		else if(heavier_node->right == nullptr)  
			heavier_node = heavier_node; //do nothing
		else if(heavier_node->left->height < heavier_node->right->height) // right subtree heavier
			heavier_node = left_rotate(heavier_node);
		st_root->left = heavier_node;
		st_root = right_rotate(st_root);
	}
	else if(bf <= -2) // right child heavier
	{
		heavier_node = st_root->right;
		if(heavier_node->left == nullptr) // so the left subtree is heavier
			heavier_node = heavier_node;//do nothing
		else if(heavier_node->right == nullptr)  
			heavier_node = right_rotate(heavier_node);
		else if(heavier_node->left->height > heavier_node->right->height)
			heavier_node = right_rotate(heavier_node);
		st_root->right = heavier_node;
		st_root = left_rotate(st_root);
	}
	return st_root;
}


#endif
