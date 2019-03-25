#include <iostream>
#include <conio.h>
#include <string>

using namespace std;

// реализация односвязного списка(как в STL)
template<class T>
class List
{
public:
	List(); // конструктор с вынесеным телом (реализацией)
	~List(); // деструктор ---||---

	void push_back(T data); // функция добавления элемента назад (листа)

	int getsize() { return size; } //геттер(получить) размерности списка

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
	int size; // длина списка
	Node<T> *head; // головной член списка
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