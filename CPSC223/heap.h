
// -------------------------------------
// NAME: Ethan Higa
// FILE: heap.h
// DATE: Fall 2021
// DESC: dynamic binary MinHeap
// -------------------------------------

#ifndef HEAP_H
#define HEAP_H

#include <stdexcept>
#include "arrayseq.h"
#include <iostream>
#include <math.h>

using namespace std;

template<typename K>
class Heap
{
public:

	// Default constructor
	Heap();

	// Copy constructor
	Heap(const Heap& rhs);

	// Move constructor
	Heap(Heap&& rhs);

	// Copy assignment operator
	Heap& operator=(const Heap& rhs);

	// Move assignment operator
	Heap& operator=(Heap&& rhs);

	// Destructor
	~Heap();

	// inserts a key into the heap (insertion based on key value)
	void insert(const K& key);

	// checking if the heap is empty
	bool empty() const;

	// obtaining the min key from the heap
	K find_min() const;

	// erasing the min key from the heap
	void remove_min();

	// providing the keys of the heap in sorted order 
	ArraySeq<K> heap_sort() const;

	// the size of the min heap
	int size() const;

	// helper to print the tree for debugging
	void print() const;
private:

	// node for heap
	struct Node {
		K key;
		Node* left;
		Node* right;
	};

	// number of nodes
	int count = 0;

	// root node
	Node* root = nullptr;

	// clean up the tree and reset count to zero given subtree root
	void make_empty();

	// copies the last node to the root and deletes the last node
	K copy_delete(int n, Node* st_root);

	// tickles down the value of root to the bottom of the heap
	void trickle_down(Node* st_root);

	// inserts at the last node of the tree
	Node* insert(const K& key, int n , Node* subtree_root );

	// print helper
	void print(std::string indent, const Node* st_root) const;

	// copy assignment helper
	Node* copy(const Node* rhs_st_root) const;
};

// print functions from Dr. Bowers
template<typename K>
void Heap<K>::print() const
{
	print(std::string(""), root);
}

template<typename K>
void Heap<K>::print(std::string indent, const Node* st_root) const
{
	if (!st_root)
		return;
	std::cout << st_root->key <<  std::endl;
	if (st_root->left) {
		std::cout << indent << " lft: ";
		print(indent + " ", st_root->left);
	}
	if (st_root->right) {
		std::cout << indent << " rgt: ";
		print(indent + " ", st_root->right);
	}
}

// default constructor
template<typename K>
Heap<K>::Heap() 
{

}

template<typename K>
Heap<K>::Heap(const Heap& rhs)
{
	*this = rhs;
}

template<typename K>
Heap<K>::Heap(Heap&& rhs)
{
	*this = std::move(rhs);
}

// copy function from hw8
template<typename K>
typename Heap<K>::Node* Heap<K>::copy(const Node* rhs_st_root) const
{
	if(rhs_st_root == nullptr)
		return nullptr;

	Node* lhs_st_root = new Node;
	lhs_st_root->key = rhs_st_root->key;
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

// same from hw8
template<typename K>
Heap<K>& Heap<K>::operator=(const Heap& rhs)
{
	if(this != &rhs)
	{
		make_empty();
		root = copy(rhs.root);
		count = rhs.count;
	}
	return *this;
}

// same from hw8
template<typename K>
Heap<K>& Heap<K>::operator=(Heap&& rhs)
{
	if(this != & rhs)
	{
		make_empty();
		root = rhs.root;
		count = rhs.count;
		rhs.root = nullptr;
		rhs.count = 0;
	}
	return *this;
}

template<typename K>
Heap<K>::~Heap()
{
	make_empty();
}

// calss recursive insert
template<typename K>
void Heap<K>::insert(const K& key)
{
	root = insert(key, count, root);
	++count;
}

template<typename K>
bool Heap<K>::empty() const
{
	return count <= 0;
}

// the key at the root should be the min as this structure is a heap
template<typename K>
K Heap<K>::find_min() const
{
	if(empty())
		throw std::out_of_range("out of range\n");
	return root->key;
}

template<typename K>
void Heap<K>::remove_min()
{
	if(empty())
		throw std::out_of_range("out of range\n");
	if(count == 1)
	{
		delete root;
		root = nullptr;
		--count;
		return;
	}
	root->key  = copy_delete(count, root); // copy the last node to the root and then removes the last node
	trickle_down(root); // trickles down the value of the root so that the tree will be a min heap
}

template<typename K>
ArraySeq<K> Heap<K>::heap_sort() const
{
	ArraySeq<K> seq;
	Heap<K> copy_heap(*this); // invokes the copy constructor to this new heap copy
	while(copy_heap.count > 0)
	{
		seq.insert(copy_heap.find_min(), seq.size()); // insert the min to the sequence
		copy_heap.remove_min(); // make the next min at the root
	}
	return seq;
}

template<typename K>
int Heap<K>::size() const
{
	return count;
}

template<typename K>
void Heap<K>::make_empty()
{
	while(count > 0)
		remove_min();
}

// pre : n >= 1
// where n is the number of nodes in the tree ( size )
template<typename K>
typename Heap<K>::Node* Heap<K>::insert(const K& key, int n, Node* subtree_root)
{
	K temp; // for swapping
	// inserts a node where the last node should be to insert it there
	if(subtree_root == nullptr)
	{
		Node* temp = new Node;
		temp->key = key;
		temp->left = nullptr;
		temp->right = nullptr;
		return temp;
	}
	int h = ceil ( log2 ( n +1)); // calculates the height
	int unfilled = ( pow (2 , h ) - 1) - n ; // on the bottom most layer
	if ( unfilled == 0) // if true then goes to bottom and left most node
	{
		subtree_root->left = insert(key, n - pow (2 , h -1) , subtree_root-> left);
		if(subtree_root->left->key < subtree_root->key)
		{ // if bottom left less than root's key
			temp = subtree_root->key;
			subtree_root->key = subtree_root->left->key;
			subtree_root->left->key = temp;
		}
	}
	else {
		int leaf_max = pow (2 , h -1); // maximum number of leaves on the bottom most layer
		int leaf_filled = leaf_max - unfilled; // on the bottom layer
		if (( leaf_max / 2) > leaf_filled) // not >= becasuse if at == then insert at the right
		{
			subtree_root->left = insert(key, n - pow (2 , h -2) , subtree_root->left );
			if(subtree_root->left->key < subtree_root->key)
			{
				temp = subtree_root->key;
				subtree_root->key = subtree_root->left->key;
				subtree_root->left->key = temp;
			}
		}
		else
		{
			subtree_root->right = insert(key, n - pow (2 , h -1) , subtree_root->right);
			if(subtree_root->right->key < subtree_root->key)
			{
				temp = subtree_root->key;
				subtree_root->key = subtree_root->right->key;
				subtree_root->right->key = temp;
			}
		}
	}
	return subtree_root;
}

// recursive function
template<typename K>
K Heap<K>::copy_delete(int n, Node* st_root)
{
	K min_key;
	if(n == 1) // if at the last node in the tree
	{
		min_key = st_root->key;
		delete st_root;
		st_root = nullptr;
		--count;
		return min_key;
	}
	int h= ceil(log2(n+1));
	int unfilled = (pow(2,h) - 1) - n;
	if(unfilled == 0)
	{
		min_key = copy_delete(n - pow(2, h-1), st_root->right);
		if(n - pow(2, h-1) == 1) // if node to the right is the last node then is deleted so set its right to nullptr
			st_root->right = nullptr;
		return min_key;
	}
	int leaf_max = pow(2, h-1);
	int leaf_filled = leaf_max - unfilled;
	if((leaf_max/2) >= leaf_filled)
	{
		min_key = copy_delete(n - pow(2, h-2), st_root->left);
		if(n - pow(2, h-2) == 1)
			st_root->left = nullptr;
		return min_key;
	}
	else
	{
		min_key = copy_delete(n - pow(2, h-1), st_root->right);
		if(n - pow(2, h-1) == 1)
			st_root->right = nullptr;
		return min_key;
	}
}

// recursive function
template<typename K>
void Heap<K>::trickle_down(Node* st_root)
{
	if(st_root->left == nullptr && st_root->right == nullptr)
		return;
	K temp;
	// swap with the least of left and right
	if(st_root->left == nullptr && st_root->right->key < st_root->key) 
	{
		temp = st_root->key;
		st_root->key = st_root->right->key;
		st_root->right->key = temp;
		trickle_down(st_root->right);
	}
	else if(st_root->right == nullptr && st_root->left->key < st_root->key) {
		temp = st_root->key;
		st_root->key = st_root->left->key;
		st_root->left->key = temp;
		trickle_down(st_root->left);
	}
	else if(st_root->left != nullptr && st_root->right != nullptr)
	{
		if(st_root->left->key > st_root->right->key && st_root->right->key < st_root->key)
		{
			temp = st_root->key;
			st_root->key = st_root->right->key;
			st_root->right->key = temp;
			trickle_down(st_root->right);
		}
		if(st_root->left->key < st_root->right->key && st_root->left->key < st_root->key)
		{
			temp = st_root->key;
			st_root->key = st_root->left->key;
			st_root->left->key = temp;
			trickle_down(st_root->left);
		}
	}
}

#endif
