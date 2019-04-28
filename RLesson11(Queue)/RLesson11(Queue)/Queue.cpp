#include "Queue.h"


template<typename T>
Queue<T>::Queue()
{
	p_first = nullptr;
	p_last = nullptr;
	SIZE = 0;
}

template<typename T>
Queue<T>::~Queue()
{
	clear();
}

template<typename T>
void Queue<T>::clear()
{
}

template<typename T>
void Queue<T>::push(T data)
{
	p_first = new Node<T>(data, p_first);
}

template<typename T>
void Queue<T>::remove()
{
	delete p_last;
}

template<typename T>
T Queue<T>::withdraw()
{
	return T();
}

template<typename T>
T Queue<T>::get_first_in()
{
	return T();
}

template<typename T>
T Queue<T>::get_last_in()
{
	return T();
}
