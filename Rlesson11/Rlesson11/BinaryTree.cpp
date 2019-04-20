#include "BinaryTree.h"
#include <iostream>
#include <xtree>

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

}

void BinaryTree::at(int index)
{
}

void BinaryTree::clear()
{
}

void BinaryTree::insert(int key)
{
	if (SIZE == 0)
	{
		p_root = new Node(key);
		
	}
	else
	{
		Node* current = this->p_root;
		while (true)
		{
			if (current->key > key)
			{
				if (current->p_left != nullptr)
				{
					current = current->p_left;
				}
				else
				{
					break;
				}
			}
			if (current->key < key)
			{
				if (current->p_right != nullptr)
				{
					current = current->p_right;
				}
				else
				{
					break;
				}
			}
		}
		if (current->key > key)
		{
			current->p_left = new Node(key);
		}
		else if (current->key < key)
		{
			current->p_right = new Node(key);
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
	tree.insert(50);
	tree.insert(13);
	tree.insert(5);
	tree.insert(1);
	cout << 1;


	return 0;
}