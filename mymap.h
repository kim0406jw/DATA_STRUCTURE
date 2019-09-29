
/*  **********UNBALANCED BINARY SEARCH TREE***********


 +++++++++++++2019-09-30+++++++++++++
   SungKyunKwan Universirty

   Written by, 2013312823 JANGWON KIM.

*/



/* *****************Member functions*****************

   Declaration: MyMap<KEY, VALUE>(key, value)

                node<KEY, VALUE>(key, value)

   1) insert(node<KEY, VALUE>): Insert a node with the key value. If fail to insert, return -1. (Argument is 'node' object.)
   2) find(key): Return the pointer of node with the key. If fail to search, return NULL.
   3) delete(key): Delete the node with this key. If fail to delete, return -1.
   4) clear(): Clear the tree.
   5) height(): Return the height of binary tree.
   6) size(): Return the number of stored elements
   7) show(): Print the tree with value of node. (Inorder Traversal)
   8) show_key(): Print the tree with value of key. (Inorder Traversal)

   */

#ifndef _MAP_H_
#define _MAP_H_
#include <iostream>

int max(int a, int b) {
	if (a >= b)
		return a;
	else
		return b;
}

template <typename T1, typename T2>
class node {
private:
public:
	T1 key;
	T2 value;
	node* right;
	node* left;
	node* parent;
	int bias;
	node(T1 _key, T2 _value) {
		key = _key;
		value = _value;
		right = NULL;
		left = NULL;
	}
};

template <typename T1, typename T2>
class MyMap {
private:
	int _size;
	node<T1, T2>* root_ptr;

	/**********************private functions**********************/
	void delete_node(node<T1, T2>* node) {
		if (node == NULL)
			return;
		delete_node(node->left);
		delete_node(node->right);
		delete node;
		return;
	}

	int get_height(node<T1, T2>* _node) {
		if (_node == NULL)
			return 0;
		else {
			return max(get_height(_node->left), get_height(_node->right)) + 1;
		}

	}

	node<T1, T2>* find_leftmost(node<T1, T2>* _node) {
		node<T1, T2>* present_node = _node;
		while (present_node->left != NULL) {
			present_node = present_node->left;
		}
		return present_node;
	}


	void inorder_key(node<T1, T2>* node) {
		if (node == NULL)
			return;
		inorder_key(node->left);
		std::cout << node->key << " ";
		inorder_key(node->right);
	}
	void inorder_value(node<T1, T2>* node) {
		if (node == NULL)
			return;
		inorder_value(node->left);
		std::cout << node->value << " ";
		inorder_value(node->right);
	}
/************************public functions*****************************/
public:
	MyMap() {
		_size = 0;
		root_ptr = NULL;
	}; // Constructor

	int insert(node<T1, T2> _node) {
		if (_size == 0) {
			node<T1, T2>* new_node = new node<T1, T2>(_node);
			new_node->parent = NULL;
			root_ptr = new_node;
			_size++;
			return 0;
		}
		node<T1, T2>* present_node = root_ptr;
		while (1) {
			if (present_node->key < _node.key) {
				if (present_node->right != NULL) {
					present_node = present_node->right;
				}
				else {
					node<T1, T2>* new_node = new node<T1, T2>(_node);
					node<T1, T2>* temp = present_node;
					present_node->right = new_node;
					new_node->parent = temp;
					_size++;
					return 0;
				}
			}
			else if (present_node->key > _node.key) {
				if (present_node->left != NULL) {
					present_node = present_node->left;
				}
				else {
					node<T1, T2>* new_node = new node<T1, T2>(_node);
					node<T1, T2>* temp = present_node;
					present_node->left = new_node;
					new_node->parent = temp;
					_size++;
					return 0;
				}
			}
			else {
				/*std::cout << "This tree already has a node with the same key value." << std::endl;*/
				return -1;
			}
		}
	}
	node<T1, T2>* find(T1 _key) {
		node<T1, T2>* present_node = root_ptr;
		while (present_node != NULL) {
			if (_key > present_node->key) {
				present_node = present_node->right;
			}
			else if (_key < present_node->key) {
				present_node = present_node->left;
			}
			else {
				return present_node;
			}
		}
		return NULL;
	}
	int erase(T1 _key) {
		node<T1, T2>* present_node = root_ptr;
		while (this->_size != 0 && present_node != NULL) {
			if (_key > present_node->key) {
				present_node = present_node->right;
			}
			else if (_key < present_node->key) {
				present_node = present_node->left;
			}
			else
			{ // Found ! (present_node == target_node)
				if (present_node->left == NULL && present_node->right == NULL) { // ***case1: If the target node is leaf node.***
					if (present_node->parent != NULL) { // If the target node isn't root node.
						if (present_node->parent->left == present_node) { // If the target node is left-leaf node.
							present_node->parent->left = NULL;
							delete present_node;
							this->_size = this->_size - 1;
							return 0;
						}
						else { // If the target node is right-leaf node.
							present_node->parent->right = NULL;
							delete present_node;
							this->_size = this->_size - 1;
							return 0;
						}
					}
					else { //If the target node is root node.
						delete present_node; //delete root node.
						this->_size = this->_size - 1;
						return 0;
					}
				}
				else if (present_node->left != NULL && present_node->right == NULL) { // ***case2: If the target node has only left child.***
					if (present_node->parent != NULL) { // If the target node isn't root node.
						if (present_node->parent->left == present_node) { // If the target node is left child node.
							present_node->parent->left = present_node->left;
							present_node->left->parent = present_node->parent;
							delete present_node;
							this->_size = this->_size - 1;
							return 0;
						}
						else { // If the target node is right child node.
							present_node->parent->right = present_node->left;
							present_node->left->parent = present_node->parent;
							delete present_node;
							this->_size = this->_size - 1;
							return 0;
						}
					}
					else { //If the target node is root node.
						node<T1, T2>* temp = this->root_ptr;
						this->root_ptr = this->root_ptr->left;
						/*this->root_ptr->parent = NULL;*/
						delete temp;
						this->_size = this->_size - 1;
						return 0;
					}
				}
				else {
					if (present_node->right->left == NULL) {  // ***case3: If the target node has right child. But the right child dosen't have its own left child.***
						if (present_node->parent != NULL) { // If the target node isn't root node.
							if (present_node->parent->left == present_node) { //If the target node is left child.
								present_node->parent->left = present_node->right;
								present_node->right->parent = present_node->parent;
								if (present_node->left != NULL) { // If the target node has its left child.
									present_node->left->parent = present_node->right;
									present_node->right->left = present_node->left;
								}
								delete present_node;
								this->_size = this->_size - 1;
								return 0;
							}
							else { //If the target node is right child.
								present_node->parent->right = present_node->right;
								present_node->right->parent = present_node->parent;
								if (present_node->left != NULL) { // If the target node has its left child.
									present_node->left->parent = present_node->right;
									present_node->right->left = present_node->left;
								}
								delete present_node;
								this->_size = this->_size - 1;
								return 0;
							}
						}
						else {  //If the target node is root node.
							node<T1, T2>* temp = this->root_ptr;
							this->root_ptr = this->root_ptr->right;
							if (this->root_ptr->left != NULL) { // If the target node has its left child.
								this->root_ptr->left = temp->left;
								this->root_ptr->left->parent = this->root_ptr;
							}
							delete temp;
							this->_size = this->_size - 1;
							return 0;
						}
					}
					else { // ***case4: If the target node has right child. And also the right child has its own left child.***
						if (present_node->parent != NULL) { // If the target node isn't root node.
							node<T1, T2>* switched_node = this->find_leftmost(present_node->right); // target node will be replaced by switched node.
							if (present_node->parent->left == present_node) { // If the target node is left child.
								switched_node->right = present_node->right; 
								switched_node->parent->left = NULL; 
								switched_node->parent = present_node->parent; 
								present_node->parent->left = switched_node;
								present_node->right->parent = switched_node; 
								if (present_node->left != NULL) { // If the target node has its left child.
									switched_node->left = present_node->left; 
									present_node->left->parent = switched_node; 
								}
								delete present_node;
								this->_size = this->_size - 1;
								return 0;
							}
							else { // If the target node is right child.
								switched_node->right = present_node->right; 
								switched_node->parent->left = NULL; 
								switched_node->parent = present_node->parent; 
								present_node->parent->right = switched_node; 
								present_node->right->parent = switched_node; 
								if (present_node->left != NULL) { // If the target node has its left child.
									switched_node->left = present_node->left; 
									present_node->left->parent = switched_node; 
								}
								delete present_node;
								this->_size = this->_size - 1;
								return 0;
							}
						}
						else { // If the target node root node.
							node<T1, T2>* switched_node = this->find_leftmost(present_node->right); // target node will be replaced by switched node.
							node<T1, T2>* temp = this->root_ptr;
							switched_node->right = present_node->right; 
							switched_node->parent->left = NULL; 
							this->root_ptr = switched_node;
							present_node->right->parent = switched_node; 
							if (present_node->left != NULL) { // If the target node has its left child.
								switched_node->left = present_node->left; 
								present_node->left->parent = switched_node; 
							}
							delete temp;
							this->_size = this->_size - 1;
							return 0;
						}
					}
				}
			}
		}
		return -1;
	}

	void show_key() {    // Print Inorder Traversal/ (key)  
		if (_size == 0)
			return;
		node<T1, T2>* root = root_ptr;
		inorder_key(root);
	}
	void show() {       // Print Inorder Traversal. (value)  
		if (_size == 0)
			return;
		node<T1, T2>* root = root_ptr;
		inorder_value(root);
	}
	int size() {        
                 // Return number of stored elements.
		return _size;
	}

	int height() {
		return this->get_height(this->root_ptr);
	}

	void clear() {
		delete_node(this->root_ptr);
		_size = 0;
	}

	~MyMap() {
		this->clear();
	}
};
#endif
