#include <iostream>
#define COUNT 10
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
	void preorder_print(BinaryTree tree);
	int maxDepth();
	void print2DUtil(int space);
	int get_size() { return SIZE; };



private:

	Node* search(int key, Node* leaf);
	int maxDepth(Node* node);
	void destroy_tree(Node* leaf);
	void insert(int key, Node* leaf);
	void inorder_print(Node* leaf);
	void postorder_print(Node* leaf);
	void print2DUtil(Node* root, int space);
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
		postorder_print(leaf->p_left);
		postorder_print(leaf->p_right);
		cout << leaf->value;
	}
	cout << "\n";
}

void BinaryTree::preorder_print() 
{
	preorder_print(*this);
	cout << "\n";
}

void BinaryTree::preorder_print(BinaryTree tree) 
{
	Node* leaf = tree.p_root;
	if (leaf != nullptr) 
	{
		inorder_print(leaf->p_left);
		inorder_print(leaf->p_right);

		if (leaf->p_right == nullptr && leaf->p_left == nullptr)
		{
			cout << leaf->value <<" ";
			delete leaf;
		}
		cout << "\n";
	}
}
int BinaryTree::maxDepth(Node* leaf)
{
	if (leaf == NULL)
		return 0;
	else
	{
		/* compute the depth of each subtree */
		int lDepth = maxDepth(leaf->p_left);
		int rDepth = maxDepth(leaf->p_right);

		/* use the larger one */
		if (lDepth > rDepth)
			return(lDepth + 1);
		else return(rDepth + 1);
	}
}
int BinaryTree::maxDepth()
{
	int a = maxDepth(p_root);
	cout << a;
	return a;
}

void BinaryTree::print2DUtil(int space)
{
	print2DUtil(p_root, space);
}

void BinaryTree::print2DUtil(Node* leaf, int space)
{
	if (leaf == nullptr)
		return;

	// Increase distance between levels  
	space += COUNT;

	// Process right child first  
	print2DUtil(leaf->p_right, space);

	// Print current node after space  
	// count  
	cout << endl;
	for (int i = COUNT; i < space; i++)
		cout << " ";
	cout << leaf->value << "\n";

	// Process left child  
	print2DUtil(leaf->p_left, space);
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

	tree->print2DUtil(1);
	delete tree;

	return 0;
}