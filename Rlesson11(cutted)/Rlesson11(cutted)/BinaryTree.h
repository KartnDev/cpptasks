#pragma once

class BinaryTree
{
	class Node;

public:
	BinaryTree();
	~BinaryTree();

	Node* search(int key);

	void clear();

	void insert(int key);

	void inorder_print();
	void print2DUtil(int space);

	void remove(int data);

	int maxDepth();
	int get_size() { return SIZE; };

private:
	class Node;
	Node* minValueNode(Node* leaf);
	Node* deleteNode(Node* p_root, int key);
	Node* search(int key, Node* leaf);
	void clear(Node* leaf);
	void insert(int key, Node* leaf);
	void inorder_print(Node* leaf);
	void print2DUtil(Node* root, int space);
	int maxDepth(Node* node);

private:
	class Node
	{
	public:
		Node* p_left;
		Node* p_right;
		int value;

		Node(int value = 0, Node* p_left = nullptr, Node* p_right = 0)
		{
			this->p_left = p_left;
			this->p_right = p_right;
			this->value = value;
		}
	};
	Node* p_root;
	int SIZE;
};


