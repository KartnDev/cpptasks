#pragma once
#include <iostream>

class BinaryTree
{
	class Node;


public:
	BinaryTree();
	~BinaryTree();

	//methods
	void remote_at(int key);
	void print_data();
	void at(int key);
	void insert(int key);
	void clear();
	int* toArray();
	int get_size();

private:
	int SIZE;
	Node* p_root;


	class Node
	{
	public:
		Node* p_left;
		Node* p_right;
		int key;


		Node(int key = 0, Node *p_left=nullptr, Node *p_right = 0)
		{
			this->p_left = p_left;
			this->p_right = p_right; 
			this->key = key;
		}
	};
};

