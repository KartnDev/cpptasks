#include <iostream>
#include "BinaryTree.h"

#define COUNT 10
#define LINE "=========================================================================================\n"

using namespace std;

BinaryTree::BinaryTree() 
{
	SIZE = 0;
	p_root = nullptr;
}

BinaryTree::~BinaryTree() 
{
	clear();
}

void BinaryTree::clear(Node* leaf) 
{
	if (leaf != nullptr) 
	{
		clear(leaf->p_left);
		clear(leaf->p_right);
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

void BinaryTree::clear() 
{
	clear(p_root);
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

int BinaryTree::maxDepth(Node* leaf)
{
	if (leaf == nullptr)
	{
		return 0;
	}
	else
	{
		/* compute the depth of each subtree */
		int lDepth = maxDepth(leaf->p_left);
		int rDepth = maxDepth(leaf->p_right);

		/* use the larger one */
		if (lDepth > rDepth)
	    {
			return(lDepth + 1);
		}
		else
		{
			return(rDepth + 1);
		}
	}
}

int BinaryTree::maxDepth()
{
	int a = maxDepth(p_root);
	cout << a;
	return a;
}

BinaryTree::Node* BinaryTree::minValueNode(BinaryTree::Node* leaf)
{
	BinaryTree::Node* current = leaf;
	
	while (current->p_left != nullptr)
	{
		current = current->p_left;
	}
	return current;
}




BinaryTree::Node* BinaryTree::deleteNode(Node* arg_root, int value)
{
	if (arg_root == nullptr)
	{
		return arg_root;
	}
	if (value < arg_root->value)
	{
		arg_root->p_left = deleteNode(arg_root->p_left, value);
	}
	else if (value > arg_root->value)
	{
		arg_root->p_right = deleteNode(arg_root->p_right, value);
	}
	else
	{
		if (arg_root->p_left == nullptr)
		{
			Node* temp = arg_root->p_right;
			free(arg_root);
			return temp;
		}
		else if (arg_root->p_right == nullptr)
		{
			Node* temp = arg_root->p_left;
			free(arg_root);
			return temp;
		}

		Node* temp = minValueNode(arg_root->p_right);

		arg_root->value = temp->value;

		arg_root->p_right = deleteNode(arg_root->p_right, temp->value);
	}
	return arg_root;
}

void BinaryTree::remove(int data)
{
	p_root = deleteNode(p_root, data);
}





void BinaryTree::print2DUtil(int space)
{
	print2DUtil(p_root, space);
}

void BinaryTree::print2DUtil(Node* leaf, int space)
{
	if (leaf == nullptr)
	{
		return;
	}
	space += COUNT;

	print2DUtil(leaf->p_right, space);

	cout << endl;

	for (int i = COUNT; i < space; i++)
	{
		cout << " ";
	}
	cout << leaf->value << "\n";

	print2DUtil(leaf->p_left, space);
}




int main() 
{


	BinaryTree tree;

	tree.insert(10);
	tree.insert(6);
	tree.insert(14);
	tree.insert(5);
	tree.insert(8);
	tree.insert(11);
	tree.insert(18);
	tree.insert(88);
	tree.insert(151);
	tree.insert(1);
	tree.insert(55);
	tree.insert(3);
	tree.insert(19);

	tree.print2DUtil(1);

	cout << LINE;

	tree.remove(151);
	tree.remove(6);
	tree.remove(10);

	tree.print2DUtil(1);

	return 0;
}