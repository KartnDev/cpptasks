#include <iostream>

using namespace std;


struct Node {
	int value;
	Node* left;
	Node* right;
};

class BinaryTree {
public:
	BinaryTree();
	~BinaryTree();

	void insert(int key);
	Node* search(int key);
	void destroy_tree();
	void inorder_print();
	void postorder_print();
	void preorder_print();
	int get_size() { return SIZE; };



private:

	void destroy_tree(Node* leaf);
	void insert(int key, Node* leaf);
	Node* search(int key, Node* leaf);
	void inorder_print(Node* leaf);
	void postorder_print(Node* leaf);
	void preorder_print(Node* leaf);

	Node* root;
	int SIZE;
};


BinaryTree::BinaryTree() {
	SIZE = 0;
	root = nullptr;
}

BinaryTree::~BinaryTree() {
	destroy_tree();
}

void BinaryTree::destroy_tree(Node* leaf) {
	if (leaf != nullptr) {
		destroy_tree(leaf->left);
		destroy_tree(leaf->right);
		delete leaf;
	}
}

void BinaryTree::insert(int key, Node* leaf) {

	if (key < leaf->value) {
		if (leaf->left != nullptr) {
			insert(key, leaf->left);
		}
		else {
			leaf->left = new Node;
			leaf->left->value = key;
			leaf->left->left = nullptr;
			leaf->left->right = nullptr;
		}
	}
	else if (key >= leaf->value) {
		if (leaf->right != nullptr) {
			insert(key, leaf->right);
		}
		else {
			leaf->right = new Node;
			leaf->right->value = key;
			leaf->right->right = nullptr;
			leaf->right->left = nullptr;
		}
	}

}

void BinaryTree::insert(int key) {
	if (root != nullptr) {
		insert(key, root);
	}
	else {
		root = new Node;
		root->value = key;
		root->left = nullptr;
		root->right = nullptr;
	}
	SIZE++;
}

Node* BinaryTree::search(int key, Node* leaf) {
	if (leaf != nullptr) {
		if (key == leaf->value) {
			return leaf;
		}
		if (key < leaf->value) {
			return search(key, leaf->left);
		}
		else {
			return search(key, leaf->right);
		}
	}
	else {
		return nullptr;
	}
}

Node* BinaryTree::search(int key) {
	return search(key, root);
}

void BinaryTree::destroy_tree() {
	destroy_tree(root);
}

void BinaryTree::inorder_print() {
	inorder_print(root);
	cout << "\n";
}

void BinaryTree::inorder_print(Node* leaf) {
	if (leaf != nullptr) {
		inorder_print(leaf->left);
		cout << leaf->value << ",";
		inorder_print(leaf->right);
	}
}

void BinaryTree::postorder_print() {
	postorder_print(root);
	cout << "\n";
}

void BinaryTree::postorder_print(Node* leaf) {
	if (leaf != nullptr) {
		inorder_print(leaf->left);
		inorder_print(leaf->right);
		cout << leaf->value << ",";
	}
}

void BinaryTree::preorder_print() {
	preorder_print(root);
	cout << "\n";
}

void BinaryTree::preorder_print(Node* leaf) {
	if (leaf != nullptr) {
		cout << leaf->value << ",";
		inorder_print(leaf->left);
		inorder_print(leaf->right);
	}
}

int main() {


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

	tree->preorder_print();
	tree->inorder_print();
	tree->postorder_print();

	delete tree;

	return 0;
}