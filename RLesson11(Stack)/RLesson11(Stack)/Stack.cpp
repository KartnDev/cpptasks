#include "Stack.h"
#include <iostream>

template<typename T>
Stack<T>::Stack()
{
	top = nullptr;
	SIZE = 0;
}

template<typename T>
Stack<T>::~Stack()
{
	clear();
}

template<typename T>
T Stack<T>::at_top()
{
	return top->data;
}

template<typename T>
T Stack<T>::get()
{
	return top->data;
}

template<typename T>
T Stack<T>::withdraw()
{
	T temp = top->data;
	pop();
	return temp;
}

template<typename T>
void Stack<T>::push(T data)
{
	top = new Node<T>(data, top);
	SIZE++;
}

template<typename T>
void Stack<T>::pop()
{
	Node<T>* temp = top; 
	top = temp->p_next;
	delete temp;
	SIZE--;
}

template<typename T>
void Stack<T>::remove()
{
	pop();
}

template<typename T>
void Stack<T>::clear()
{
	while ((bool)SIZE)
	{
		pop();
	}
}


int main()
{
	Stack<int> stack;
	stack.push(10);
	stack.push(11);
	stack.push(4343);
	stack.push(120);
	stack.push(1);

	std::cout << stack.get_size() << " - Size of stack elements\n";
	for (int i=0 ; i < 5; i++)
	{
		std::cout <<"withdraw stack, element ="<<"[" <<i << "] ="<< stack.withdraw() << "\n";
	}

	return 0;
}