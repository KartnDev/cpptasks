#pragma once
template <typename T>
class Queue
{
public:
	Queue();
	~Queue();

	// methods
	void clear();
	void push(T data);
	void remove();
	T withdraw();
	T get_first_in();
	T get_last_in();
private:
	template <typename T>
	class Node
	{
	public:
		Node p_next;
		Node p_prev;
		T data;


		Node(T data = T(),Node* p_next = nullptr,Node* p_prev = nullptr) 
		{
			this->data = data;
			this->p_next = p_next;
			this->p_prev = p_prev;
		}
	};

	Node* p_first;
	Node* p_last;
	int SIZE;
};

