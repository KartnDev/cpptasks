#include <iostream>
#include <conio.h>
#include <string>
#include <ctime>

using namespace std;

// ���������� ������������ ������(��� � STL)
template<class T>
class List
{
public:
	List(); // ����������� � ��������� ����� (�����������)
	~List(); // ���������� ---||---
	void display_data();
	void push_back(T data); // ������� ���������� �������� ����� (�����)
	void push_front(T data);
	void insert(T data, int index);
	void pop_back();
	void pop_front(); // ������� �������� ��������� ��������(�������)
	void remove_at(int index);
	void clear(); 
	int getsize() { return SIZE; } //������(��������) ����������� ������
	//����������� �������� [] ��� ����, ����� ����� ���� ������� ��� ������
	// ���������� ��������� � main.cpp
	T& operator[](const int index);

private:

	// ����� (��������) ���� 
	// ���� - �������� ������ (��� ������), �� �� ���� ������� ��� ������
	// ����� ���������, ����� ���� ����������� ������� ����� ��� ������ 
	template<class T> // typename?????????
	class Node
	{
	public:
		Node *p_next;
		T data;

		//		����������� ����: 
		// ��� �������� � ����������� ���� �� ������ �� ������� ����������� ��(�� ��������� ������)
		// ��� ��������� �� ����. ���� ����� ����� ����-������
		// ������������ ��� ������ (����) ����� �� ������� :
		// ���� ����� �� ������ ����������� �� ����������
		// ���� �� ����������� ��� ������, �� ��������� ��������� �������� ������������ ����
		// ��� ��� �������� �� ��������� ������(�������� ������������ ������) � ���������� �����
		Node(T data = T(), Node *p_next = nullptr)
		{
			this->data = data;
			this->p_next = p_next;
		}
	};
	int SIZE; // ����� ������
	Node<T> *head; // �������� ���� ������
};
template <class T>
List<T>::List()
{
	SIZE = 0;
	head = nullptr;
}

template <class T>
List<T>::~List()
{
	clear();
}

template<class T>
void List<T>::display_data()
{
	Node<T>* current = this->head;

	cout << current->data << endl;

	while (current->p_next != nullptr)
	{
		current = current->p_next;
		cout << current->data << endl;
	} 
	//cout << current->data << endl;
}

// ���� ������� ���������� � ����� ������ 
template<class T>
void List<T>::push_back(T data)
{
	if (head == nullptr)
	{
		head = new Node<T>(data);
	}
	else
	{
		Node<T> *current = this->head;

		while (current -> p_next != nullptr)
		{
			current = current-> p_next;
		}
		current->p_next = new Node<T>(data);
	}
	SIZE++;
}

template<class T>
void List<T>::push_front(T data)
{
	head = new Node<T>(data, head);
	SIZE++;
}

template<class T>
void List<T>::insert(T data, int index)
{
	if (index == 0)
	{
		push_front(data);
	}
	else
	{
		Node<T>* p_prev = this->head;

		for (int i = 0; i < index - 1; i++)
		{
			p_prev = p_prev->p_next;
		}

		Node<T>* new_node = new Node<T>(data, p_prev->p_next);

		p_prev->p_next = new_node;

		SIZE++;
	}
}

template<class T>
void List<T>::pop_back()
{
	remove_at(SIZE - 1);
}

template<class T>
void List<T>::pop_front()
{	 //��������� �������� ���� �� ��������� ����, � ������(������ ��������) 
	 //���������� � ��������� ���������� temp 
	Node<T> *temp = head;
	head = head->p_next;
	delete temp;
	SIZE--;
}

template<class T>
void List<T>::remove_at(int index)
{
	if (index == 0)
	{
		pop_front();
	}
	else
	{
		Node<T>* p_prev = this->head;
		for (int i = 0; i < index - 1; i++)
		{
			p_prev = p_prev->p_next;
		}

		Node<T>* p_removed = p_prev -> p_next;

		p_prev->p_next = p_removed -> p_next;

		delete p_removed;
		SIZE--;
	}


}

template<class T>
void List<T>::clear()
{
	while ((bool)SIZE) // size > 0
	{
		pop_front();
	}

}

template<class T>
T & List<T>::operator[](const int index)
{
	int counter = 0;
	Node<T> *p_current = this->head;

	while(p_current != nullptr)
	{
		if (counter == index)
		{
			return p_current -> data;
		}
		p_current = p_current->p_next;

		counter++;
	}
}


int main()
{
	setlocale(LC_ALL, "ru");

	

	List<int> list;

	list.push_back(5);
	list.push_front(7);
	list.push_back(100);
	list.display_data();
	list.head;
	cout << endl;
	list.insert(77, 2);
	list.display_data();

	system("pause");
	return EXIT_SUCCESS;
}