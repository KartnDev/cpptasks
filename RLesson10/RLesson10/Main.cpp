#include <iostream>
#include <conio.h>
#include <string>

using namespace std;

// ���������� ������������ ������(��� � STL)
template<class T>
class List
{
public:
	List(); // ����������� � ��������� ����� (�����������)
	~List(); // ���������� ---||---

	void push_back(T data); // ������� ���������� �������� ����� (�����)

	int getsize() { return size; } //������(��������) ����������� ������

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
	int size; // ����� ������
	Node<T> *head; // �������� ���� ������
};
template <class T>
List<T>::List()
{
	size = 0;
	head = nullptr;
}

template <class T>
List<T>::~List()
{

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
	size++;
}

template<class T>
T & List<T>::operator[](const int index)
{
	int counter = 0;
	Node<T> *current = this->head;

	while(current != nullptr)
	{
		if (counter == index)
		{
			return current -> data;
		}
		current = current->p_next;

		counter++;
	}
}


int main()
{
	setlocale(LC_ALL, "ru");

	List<int> lst;

	for (int i = 0; i < 10; i++)
	{
		lst.push_back(i*i);
	}

	for (int i = 0; i < 10; i++)
	{
		cout << lst[i] << endl;
	}

	_getch();
	return EXIT_SUCCESS;
}