#pragma once
template <typename T>
class Stack
{
public:
	Stack();
	~Stack();

	//methods in stack
	T at_top();
	T get();
	T withdraw();
	void push(T data);
	void pop();
	void remove();
	void clear();
	int get_size() { return SIZE; };



private:
	//atteched class mean ever element in stack
	template <typename T>
	class Node
	{
	public:
		T data;
		Node* p_next;

		//constructor
		Node(T data = T(), Node* p_next = nullptr)
		{
			this->data = data;
			this->p_next = p_next;
		}
	};

	int SIZE;
	Node<T>* top;
};

