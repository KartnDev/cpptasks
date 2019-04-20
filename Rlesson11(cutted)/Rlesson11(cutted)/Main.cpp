#include <iostream>

using namespace std;



class BinaryTree 
{
	class Node;

public:
	BinaryTree();
	~BinaryTree();

	Node* search(int key);

	void insert(int key);
	void destroy_tree();
	void inorder_print();
	void postorder_print();
	void preorder_print();

	int get_size() { return SIZE; };



private:

	Node* search(int key, Node* leaf);

	void destroy_tree(Node* leaf);
	void insert(int key, Node* leaf);
	void inorder_print(Node* leaf);
	void postorder_print(Node* leaf);
	void preorder_print(Node* leaf);


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


BinaryTree::BinaryTree() 
{
	SIZE = 0;
	p_root = nullptr;
}

BinaryTree::~BinaryTree() {
	destroy_tree();
}

void BinaryTree::destroy_tree(Node* leaf) 
{
	if (leaf != nullptr) 
	{
		destroy_tree(leaf->p_left);
		destroy_tree(leaf->p_right);
		delete leaf; 
	}
}

void BinaryTree::insert(int key, Node* leaf) 
{

	if (key < leaf->value) 
	{
		if (leaf->p_left != nullptr) 
		{
			insert(key, leaf->p_left);
		}
		else 
		{
			leaf->p_left = new Node(key);
		}
	}
	else if (key >= leaf->value) 
	{
		if (leaf->p_right != nullptr) 
		{
			insert(key, leaf->p_right);
		}
		else 
		{
			leaf->p_right = new Node(key);
		}
	}
}

void BinaryTree::insert(int key) 
{
	if (p_root != nullptr) 
	{
		insert(key, p_root);
	}
	else 
	{
		p_root = new Node(key);
	}
	SIZE++;
}

BinaryTree::Node* BinaryTree::search(int key, Node* leaf) 
{
	if (leaf != nullptr) 
	{
		if (key == leaf->value) 
		{
			return leaf;
		}
		if (key < leaf->value) 
		{
			return search(key, leaf->p_left);
		}
		else 
		{
			return search(key, leaf->p_right);
		}
	}
	else 
	{
		return nullptr;
	}
}

BinaryTree::Node* BinaryTree::search(int key) 
{
	return search(key, p_root);
}

void BinaryTree::destroy_tree() 
{
	destroy_tree(p_root);
}

void BinaryTree::inorder_print() 
{
	inorder_print(p_root);
	cout << "\n";
}

void BinaryTree::inorder_print(Node* leaf) 
{
	if (leaf != nullptr) 
	{
		inorder_print(leaf->p_left);
		cout << leaf->value << ",";
		inorder_print(leaf->p_right);
	}
}

void BinaryTree::postorder_print() 
{

	postorder_print(p_root);
	cout << "\n";

}

void BinaryTree::postorder_print(Node* leaf) 
{

	if (leaf != nullptr) 
	{
		inorder_print(leaf->p_left);
		inorder_print(leaf->p_right);
		cout << leaf->value << ",";
	}
}

void BinaryTree::preorder_print() 
{
	preorder_print(p_root);
	cout << "\n";
}

void BinaryTree::preorder_print(Node* leaf) 
{

	if (leaf != nullptr) 
	{
		cout << leaf->value << ",";
		inorder_print(leaf->p_left);
		inorder_print(leaf->p_right);
	}
}

int main() 
{


	BinaryTree* tree = new BinaryTree();

	tree->insert(10);
	tree->insert(6);
	tree->insert(14);
	tree->insert(5);
	tree->insert(8);
	tree->insert(11);
	tree->insert(18);
	tree->insert(88);
	tree->insert(151);
	tree->insert(1);
	tree->insert(55);
	tree->insert(3);
	tree->insert(19);

	tree->preorder_print();  // пред-заказ
	tree->inorder_print();   // по порядку
	tree->postorder_print(); // после заказа

	delete tree;

	return 0;
}