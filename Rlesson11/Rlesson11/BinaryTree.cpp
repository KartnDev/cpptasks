#include "BinaryTree.h"
#include <iostream>

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

void BinaryTree::remote_at(int index)
{
}

void BinaryTree::print_data()
{
	Node* current = this->p_root;
	cout << current->data << endl;
	while (current != nullptr)
	{
		current = current->p_left;
		cout << current->data <<endl;
	}
	while (current != nullptr)
	{
		current = current->p_right;
		cout << current->data << endl;
	}
}

void BinaryTree::at(int index)
{
}

void BinaryTree::clear()
{
}

void BinaryTree::insert(int data)
{
	if (SIZE == 0)
	{
		p_root = new Node(data);
		
	}
	else
	{
		Node* current = this->p_root;
		bool _sfrf=true; //start from root flag
		while (_sfrf)
		{
			if (current->data > data)
			{
				if (current->p_left != nullptr)
				{
					current = current->p_left;
				}
				else
				{
					current->p_left = new Node(data);
					_sfrf = false;
				}
			}
			if (current->data < data)
			{
				if (current->p_right != nullptr)
				{
					current = current->p_right;
				}
				else
				{
					current->p_right = new Node(data);
					_sfrf = false;
				}
			}
			if (current->data > data)
			{
				current->p_left = new Node(data);
			}
			if (current->data < data)
			{
				current->p_right = new Node(data);
			}
		}
	}
	SIZE++;
}

int* BinaryTree::toArray()
{
	return nullptr;
}

int BinaryTree::get_size()
{
	return SIZE;
}

int main()
{

	BinaryTree tree;
	tree.insert(10);
	tree.insert(11);
	tree.insert(9);
	tree.insert(130);
	tree.insert(50);
	tree.insert(30);
	tree.insert(100);

	cout << 1;


	return 0;
}