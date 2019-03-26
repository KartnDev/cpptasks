#include <iostream>
#include <conio.h>
#include <string>
#include <ctime>

using namespace std;

// реализация односвязного списка(как в STL)
template<class T>
class List
{
public:
	List(); // конструктор с вынесеным телом (реализацией)
	~List(); // деструктор ---||---
	void display_data();
	void push_back(T data); // функция добавления элемента назад (листа)
	void push_front(T data);
	void insert(T data, int index);
	void pop_back();
	void pop_front(); // функция удаления головного элемента(первого)
	void remove_at(int index);
	void clear(); 
	int getsize() { return SIZE; } //геттер(получить) размерности списка
	//перегружаем оператор [] для того, чтобы можно было листать наш список
	// реализация находится в main.cpp
	T& operator[](const int index);

private:

	// класс (вложеный) нода 
	// нода - примитив списка (его объект), то из чего состоит сам список
	// класс шаблонный, чтобы была возможность хранить любой тип данных 
	template<class T> // typename?????????
	class Node
	{
	public:
		Node *p_next;
		T data;

		//		КОНСТРУКТОР НОДЫ: 
		// при передачи в конструктор ноды мы должны по дефолту обозначитьь их(во избежание мусора)
		// так указатель на след. ноду будет иметь нулл-ссылку
		// передаваемый тип данных (дата) будет по дефолту :
		// если класс то вызван конструктор по умолчанияю
		// если же примитивный тип данных, то присвоено дефолтное значение примитивного типа
		// все это делается во избежания мусора(ненужных неправильных данных) в неуказаных полях
		Node(T data = T(), Node *p_next = nullptr)
		{
			this->data = data;
			this->p_next = p_next;
		}
	};
	int SIZE; // длина списка
	Node<T> *head; // головной член списка
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

// тело функции добавления в конец списка 
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
{	 //переносим головную ноду на следующую ноду, а данную(бывшую головную) 
	 //записываем в временную переменную temp 
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