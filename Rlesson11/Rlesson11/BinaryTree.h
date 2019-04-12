#pragma once
class BinaryTree
{
public:
	BinaryTree();
	~BinaryTree();

	//methods
	void remote_at(int index);
	void at(int index);
	void insert(int data);
	void clear();
	int* toArray();
	int get_size();
private:

	class Node
	{
	public:
		Node* p_left;
		Node* p_right;
		int data;

		Node(int date = 0, Node *p_left = nullptr, Node *p_right=nullptr)
		{
			this->p_left = p_left; this->p_right = p_right; this->data = data;
		}
	};
	int SIZE;
	Node* p_root;
};

