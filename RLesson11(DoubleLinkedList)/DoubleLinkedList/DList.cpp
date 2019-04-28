#include <iostream>
#include "DList.h"

using namespace std;

template <typename T>
DList<T>::DList()
{
	SIZE = 0;
	head = nullptr;
	tail = nullptr;
}

template <typename T>
DList<T>::~DList()
{
	clear();
}

template<typename T>
void DList<T>::push_back(T data)
{
	if (SIZE == 0)
	{
		tail = new Node<T>(data);
	}
	else
	{
		Node<T>* temp = tail;
		tail = new Node<T>(data, nullptr, tail);
		if (temp != nullptr)
		{
			temp->p_next = tail;
			link_head_tail();
		}
	}
	
	SIZE++;
}

template<typename T>
void DList<T>::push_front(T data)
{
	if (SIZE == 0)
	{
		head = new Node<T>(data);
	}
	else
	{
		Node<T>* temp = head;
		head = new Node<T>(data, head, nullptr);
		if (temp != nullptr)
		{
			temp->p_prev = head;
			link_head_tail();
		}
	}
	SIZE++;
}

template<typename T>
void DList<T>::insert(T data, int index)
{
}




template<typename T>
void DList<T>::pop_back()
{
	Node<T>* temp = tail;
	tail = tail->p_prev;
	delete temp;
	SIZE--;
}

template<typename T>
void DList<T>::pop_front()
{
	Node<T>* temp = head;
	head = head->p_next;
	delete temp;
	SIZE--;
}

template<typename T>
void DList<T>::remove_at(int index)
{
}

template<typename T>
void DList<T>::clear()
{
}

template<typename T>
T& DList<T>::operator[](const int index)
{
	// TODO: вставьте здесь оператор return
}

template<typename T>
void DList<T>::link_head_tail()
{
	Node<T>* current = head;
	Node<T>* temp = tail;
	while (current->p_next != nullptr)
	{
		current = current->p_next;
	}
	while (temp->p_prev != nullptr)
	{
		temp = temp->p_prev;
	}
	current->p_next = temp;
	temp->p_prev = current;
}


int main()
{
	DList<int> list;


	list.push_front(9);
	list.push_back(1);
	list.push_front(5);


	cout << "fdf";

	return 0;
}